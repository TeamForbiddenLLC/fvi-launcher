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


#include "Game.h"


namespace {
QString joined_list(const QStringList& list) { return list.join(QLatin1String(", ")); }
} // namespace


namespace model {
GameData::GameData(QString new_title)
    : title(std::move(new_title))
    , sort_by(title)
{}


Game::Game(QString name, QObject* parent)
    : QObject(parent)
    , m_files(new QQmlObjectListModel<model::GameFile>(this))
    , m_collections(new QQmlObjectListModel<model::Collection>(this))
    , m_data(std::move(name))
    , m_assets(new model::Assets(this))
{}

QString Game::developerStr() const { return joined_list(m_data.developers); }
QString Game::publisherStr() const { return joined_list(m_data.publishers); }
QString Game::genreStr() const { return joined_list(m_data.genres); }
QString Game::websiteStr() const { return joined_list(m_data.websites); }
QString Game::sourceStr() const { return joined_list(m_data.sources); }
QString Game::versionStr() const { return joined_list(m_data.versions); }
QString Game::itemStr() const { return joined_list(m_data.items); }
QString Game::tierStr() const { return joined_list(m_data.tiers); }
QString Game::twitterStr() const { return joined_list(m_data.twitters); }
QString Game::facebookStr() const { return joined_list(m_data.facebooks); }
QString Game::instagramStr() const { return joined_list(m_data.instagrams); }
QString Game::snapchatStr() const { return joined_list(m_data.snapchats); }
QString Game::pinterestStr() const { return joined_list(m_data.pinterests); }
QString Game::youtubeStr() const { return joined_list(m_data.youtubes); }
QString Game::tiktokStr() const { return joined_list(m_data.tiktoks); }
QString Game::discordStr() const { return joined_list(m_data.discords); }
QString Game::twitchStr() const { return joined_list(m_data.twitchs); }
QString Game::externalvideoStr() const { return joined_list(m_data.externalvideos); }
QString Game::versiontitleStr() const { return joined_list(m_data.versiontitles); }
QString Game::developertitleStr() const { return joined_list(m_data.developertitles); }
QString Game::startupStr() const { return joined_list(m_data.startups); }
QString Game::signatureStr() const { return joined_list(m_data.signatures); }
QString Game::vanityStr() const { return joined_list(m_data.vanitys); }
QString Game::thankyouStr() const { return joined_list(m_data.thankyous); }
QString Game::whoStr() const { return joined_list(m_data.whos); }
QString Game::artistStr() const { return joined_list(m_data.artists); }
QString Game::welcomeStr() const { return joined_list(m_data.welcomes); }
QString Game::tagStr() const { return joined_list(m_data.tags); }

Game& Game::setFavorite(bool new_val)
{
    m_data.is_favorite = new_val;
    emit favoriteChanged();
    return *this;
}

Game& Game::setWhitelist(bool new_val)
{
    m_data.is_whitelist = new_val;
    emit whitelistChanged();
    return *this;
}

void Game::onEntryPlayStatsChanged()
{
    m_data.playstats.play_count = std::accumulate(filesConst().cbegin(), filesConst().cend(), 0,
        [](int sum, const model::GameFile* const gamefile){
            return sum + gamefile->playCount();
        });
    m_data.playstats.play_time = std::accumulate(filesConst().cbegin(), filesConst().cend(), 0,
        [](qint64 sum, const model::GameFile* const gamefile){
            return sum + gamefile->playTime();
        });
    m_data.playstats.last_played = std::accumulate(filesConst().cbegin(), filesConst().cend(), QDateTime(),
        [](const QDateTime& current_max, const model::GameFile* const gamefile){
            return std::max(current_max, gamefile->lastPlayed());
        });

    emit playStatsChanged();
}

void Game::launch()
{
    Q_ASSERT(m_files->count() > 0);

    if (m_files->count() == 1)
        m_files->first()->launch();
    else
        emit launchFileSelectorRequested();
}

Game& Game::setFiles(std::vector<model::GameFile*>&& files)
{
    for (model::GameFile* const gamefile : files) {
        connect(gamefile, &model::GameFile::playStatsChanged,
                this, &model::Game::onEntryPlayStatsChanged);
    }

    std::sort(files.begin(), files.end(), model::sort_gamefiles);

    QVector<model::GameFile*> modelvec;
    modelvec.reserve(files.size());
    std::move(files.begin(), files.end(), std::back_inserter(modelvec));

    m_files->append(std::move(modelvec));
    return *this;
}

Game& Game::setCollections(std::vector<model::Collection*>&& collections)
{
    std::sort(collections.begin(), collections.end(), model::sort_collections);

    QVector<model::Collection*> modelvec;
    modelvec.reserve(collections.size());
    std::move(collections.begin(), collections.end(), std::back_inserter(modelvec));

    m_collections->append(std::move(modelvec));
    return *this;
}

bool sort_games(const model::Game* const a, const model::Game* const b) {
   return QString::localeAwareCompare(a->sortBy(), b->sortBy()) < 0;
}
} // namespace model
