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


#pragma once

#include "Provider.h"

#include <QObject>
#include <QFuture>
#include <memory>
#include <vector>

namespace model { class Collection; }
namespace model { class Game; }


class ProviderManager : public QObject {
    Q_OBJECT

public:
    explicit ProviderManager(QObject* parent);

    void startStaticSearch(QVector<model::Collection*>&, QVector<model::Game*>&);
    void startDynamicSearch(const QVector<model::Game*>&, const QVector<model::Collection*>&);

    void onGameLaunched(model::GameFile* const);
    void onGameFinished(model::GameFile* const);
    void onGameFavoriteChanged(const QVector<model::Game*>&);
    void onGameWhitelistChanged(const QVector<model::Game*>&);    

signals:
    void gameCountChanged(int);
    void singleProviderFinished();

    void firstPhaseComplete(qint64);
    void secondPhaseComplete(qint64);
    void staticDataReady();
    void dynamicDataReady(qint64);

private:
    QFuture<void> m_future;
};
