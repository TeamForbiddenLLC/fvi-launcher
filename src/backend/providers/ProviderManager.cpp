// Pegasus Frontend
// Copyright (C) 2017-2019  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include "ProviderManager.h"

#include "AppSettings.h"
#include "LocaleUtils.h"
#include "SearchContext.h"
#include "model/gaming/Collection.h"
#include "model/gaming/Game.h"
#include "utils/HashMap.h"
#include "utils/StdHelpers.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <unordered_set>

using ProviderPtr = providers::Provider*;


namespace {
std::vector<ProviderPtr> enabled_providers()
{
    std::vector<ProviderPtr> out;
    for (const auto& provider : AppSettings::providers) {
        if (provider->enabled())
            out.emplace_back(provider.get());
    }
    return out;
}

void postprocess_list_results(providers::SearchContext& sctx)
{
    QElapsedTimer timer;
    timer.start();

    sctx.finalize_lists();

    qInfo().noquote() << tr_log("Game list post-processing took %1ms").arg(timer.elapsed());
}

void run_list_providers(providers::SearchContext& ctx, const std::vector<ProviderPtr>& providers)
{
    QElapsedTimer timer;
    timer.start();

    for (const ProviderPtr& ptr : providers) {
        if (!(ptr->flags() & providers::PROVIDES_GAMES))
            continue;

        ptr->findLists(ctx);
        qInfo().noquote() << tr_log("%1: finished game searching in %2ms")
            .arg(ptr->name(), QString::number(timer.restart()));
    }
}

void run_asset_providers(providers::SearchContext& sctx, const std::vector<ProviderPtr>& providers)
{
    QElapsedTimer timer;
    timer.start();
    for (const auto& provider : providers) {
        if (!(provider->flags() & providers::PROVIDES_ASSETS))
            continue;

        provider->findStaticData(sctx);
        qInfo().noquote() << tr_log("%1: finished asset searching in %2ms")
            .arg(provider->name(), QString::number(timer.restart()));
    }
}

HashMap<QString, model::GameFile*> build_path_map(const QVector<model::Game*>& games)
{
    // prepare
    size_t gamefile_cnt = 0; // TODO: map-reduce
    for (const model::Game* const q_game : games)
        gamefile_cnt += q_game->filesConst().size();

    // build
    HashMap<QString, model::GameFile*> result;
    result.reserve(gamefile_cnt);
    for (const model::Game* const q_game : games) {
        for (model::GameFile* const q_gamefile : q_game->filesConst()) {

            QString path = q_gamefile->fileinfo().canonicalFilePath();
            if (Q_LIKELY(!path.isEmpty()))
                result.emplace(std::move(path), q_gamefile);
        }
    }
    return result;
}

std::tuple<QVector<model::Collection*>, QVector<model::Game*>>
prepare_output(providers::SearchContext& sctx, QThread* const target_thread)
{
    QVector<model::Collection*> collections;
    QVector<model::Game*> games;
    std::tie(collections, games) = sctx.consume();

    for (model::Collection* const coll : qAsConst(collections))
        coll->moveToThread(target_thread);
    for (model::Game* const game : qAsConst(games))
        game->moveToThread(target_thread);

    return std::make_tuple(std::move(collections), std::move(games));
}
} // namespace


ProviderManager::ProviderManager(QObject* parent)
    : QObject(parent)
{
    for (const auto& provider : AppSettings::providers) {
        connect(provider.get(), &providers::Provider::gameCountChanged,
                this, &ProviderManager::gameCountChanged);
    }
}

void ProviderManager::startStaticSearch(
    QVector<model::Collection*>& out_collections,
    QVector<model::Game*>& out_games)
{
    Q_ASSERT(!m_future.isRunning());

    m_future = QtConcurrent::run([this, &out_collections, &out_games]{
        providers::SearchContext ctx;

        QElapsedTimer timer;
        timer.start();

        const std::vector<ProviderPtr> providers = enabled_providers();
        for (const auto& provider : providers)
            provider->load();

        run_list_providers(ctx, providers);
        postprocess_list_results(ctx); // TODO: C++17
        emit firstPhaseComplete(timer.restart());

        run_asset_providers(ctx, providers);
        emit secondPhaseComplete(timer.restart());

        QVector<model::Collection*> collections;
        QVector<model::Game*> games;
        std::tie(collections, games) = prepare_output(ctx, this->thread());

        std::swap(collections, out_collections);
        std::swap(games, out_games);
        emit staticDataReady();
    });
}

void ProviderManager::startDynamicSearch(const QVector<model::Game*>& games,
                                         const QVector<model::Collection*>& collections)
{
    Q_ASSERT(!m_future.isRunning());

    m_future = QtConcurrent::run([this, &games, &collections]{
        QElapsedTimer timer;
        timer.start();

        const HashMap<QString, model::GameFile*> path_map = build_path_map(games);
        for (const auto& provider : AppSettings::providers)
            provider->findDynamicData(collections, games, path_map);

        emit dynamicDataReady(timer.elapsed());
    });
}

void ProviderManager::onGameFavoriteChanged(const QVector<model::Game*>& all_games)
{
    if (m_future.isRunning())
        return;

    for (const auto& provider : AppSettings::providers)
        provider->onGameFavoriteChanged(all_games);
}

void ProviderManager::onGameWhitelistChanged(const QVector<model::Game*>& all_games)
{
    if (m_future.isRunning())
        return;

    for (const auto& provider : AppSettings::providers)
        provider->onGameWhitelistChanged(all_games);
}

void ProviderManager::onGameLaunched(model::GameFile* const game)
{
    if (m_future.isRunning())
        return;

    for (const auto& provider : AppSettings::providers)
        provider->onGameLaunched(game);
}

void ProviderManager::onGameFinished(model::GameFile* const game)
{
    if (m_future.isRunning())
        return;

    for (const auto& provider : AppSettings::providers)
        provider->onGameFinished(game);
}
