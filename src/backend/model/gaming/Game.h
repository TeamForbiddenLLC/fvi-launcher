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

#include "Assets.h"
#include "GameFile.h"
#include "utils/MoveOnly.h"
#include "model/gaming/Collection.h"

#include "QtQmlTricks/QQmlObjectListModel.h"
#include <QObject>
#include <unordered_set>

namespace model { class Collection; }


namespace model {
struct GameData {
    explicit GameData(QString);

    QString title;
    QString sort_by;
    QString summary;
    QString description;

    QStringList developers;
    QStringList publishers;
    QStringList genres;
    QStringList websites;
    QStringList sources;
    QStringList versions;
    QStringList items;
    QStringList tiers;	
    QStringList twitters;
    QStringList facebooks;
    QStringList instagrams;
    QStringList snapchats;
    QStringList pinterests;
    QStringList youtubes;
    QStringList tiktoks;
    QStringList discords;
    QStringList twitchs;
    QStringList externalvideos; 
    QStringList startups;
    QStringList signatures;
    QStringList vanitys;
    QStringList versiontitles;
    QStringList developertitles; 	
    QStringList thankyous;	
	QStringList whos;
    QStringList artists;
	QStringList welcomes;
    QStringList tags;

    short player_count = 1;
    float rating = 0.0;
    QDate release_date;

    struct PlayStats {
        int play_count = 0;
        int play_time = 0;
        QDateTime last_played;
    } playstats;

    bool is_favorite = false;
    bool is_whitelist = false;

    struct LaunchParams {
        QString launch_cmd;
        QString launch_workdir;
        QString relative_basedir; // TODO: check if needed
    } launch_params;
};


class Game : public QObject {
    Q_OBJECT

public:
#define GETTER(type, name, field) \
    type name() const { return m_data.field; }

    GETTER(const QString&, title, title)
    GETTER(const QString&, sortBy, sort_by)
    GETTER(const QString&, summary, summary)
    GETTER(const QString&, description, description)
    GETTER(const QDate&, releaseDate, release_date)
    GETTER(int, playerCount, player_count)
    GETTER(float, rating, rating)

    GETTER(const QStringList&, developerListConst, developers)
    GETTER(const QStringList&, publisherListConst, publishers)
    GETTER(const QStringList&, genreListConst, genres)
    GETTER(const QStringList&, websiteListConst, websites)
    GETTER(const QStringList&, sourceListConst, sources)
    GETTER(const QStringList&, versionListConst, versions)
    GETTER(const QStringList&, itemListConst, items)
    GETTER(const QStringList&, tierListConst, tiers)	
    GETTER(const QStringList&, twitterListConst, twitters)
    GETTER(const QStringList&, facebookListConst, facebooks)
    GETTER(const QStringList&, instagramListConst, instagrams)
    GETTER(const QStringList&, snapchatListConst, snapchats)
    GETTER(const QStringList&, pinterestListConst, pinterests)
    GETTER(const QStringList&, youtubeListConst, youtubes)
    GETTER(const QStringList&, tiktokListConst, tiktoks)                               
    GETTER(const QStringList&, discordListConst, discords)   
    GETTER(const QStringList&, twitchListConst, twitchs)
    GETTER(const QStringList&, externalvideoListConst, externalvideos)
    GETTER(const QStringList&, startupListConst, startups)
    GETTER(const QStringList&, signatureListConst, signatures)	
    GETTER(const QStringList&, vanityListConst, vanitys)	
    GETTER(const QStringList&, thankyouListConst, thankyous)	
    GETTER(const QStringList&, versiontitleListConst, versiontitles)
    GETTER(const QStringList&, developertitleListConst, developertitles)	
    GETTER(const QStringList&, whoListConst, whos)   
    GETTER(const QStringList&, artistListConst, artists)  
    GETTER(const QStringList&, welcomeListConst, welcomes)  	
    GETTER(const QStringList&, tagListConst, tags)

    GETTER(int, releaseYear, release_date.year())
    GETTER(int, releaseMonth, release_date.month())
    GETTER(int, releaseDay, release_date.day())

    GETTER(int, playCount, playstats.play_count)
    GETTER(int, playTime, playstats.play_time)
    GETTER(const QDateTime&, lastPlayed, playstats.last_played)
    GETTER(bool, isFavorite, is_favorite)
    GETTER(bool, isWhitelist, is_whitelist)

    GETTER(const QString&, launchCmd, launch_params.launch_cmd)
    GETTER(const QString&, launchWorkdir, launch_params.launch_workdir)
    GETTER(const QString&, launchCmdBasedir, launch_params.relative_basedir)
#undef GETTER


#define SETTER(type, name, field) \
    Game& set##name(type val) { m_data.field = std::move(val); return *this; }

    SETTER(QString, Title, title)
    SETTER(QString, SortBy, sort_by)
    SETTER(QString, Summary, summary)
    SETTER(QString, Description, description)
    SETTER(QDate, ReleaseDate, release_date)
    SETTER(int, PlayerCount, player_count)
    SETTER(float, Rating, rating)

    SETTER(QString, LaunchCmd, launch_params.launch_cmd)
    SETTER(QString, LaunchWorkdir, launch_params.launch_workdir)
    SETTER(QString, LaunchCmdBasedir, launch_params.relative_basedir)

    Game& setFavorite(bool val);
    Game& setWhitelist(bool val);
#undef SETTER


#define STRLIST(singular, field) \
    QString singular##Str() const; \
    QStringList& singular##List() { return m_data.field; } \
    Q_PROPERTY(QString singular READ singular##Str CONSTANT) \
    Q_PROPERTY(QStringList singular##List READ singular##ListConst CONSTANT)

    STRLIST(developer, developers)
    STRLIST(publisher, publishers)
    STRLIST(genre, genres)
    STRLIST(website, websites)
    STRLIST(source, sources)
    STRLIST(version, versions)
    STRLIST(tier, tiers)	
    STRLIST(item, items)
    STRLIST(twitter, twitters)
    STRLIST(facebook, facebooks)
    STRLIST(instagram, instagrams)
    STRLIST(snapchat, snapchats)
    STRLIST(pinterest, pinterests)
    STRLIST(youtube, youtubes)
    STRLIST(tiktok, tiktoks)
    STRLIST(discord, discords)
    STRLIST(twitch, twitchs)
    STRLIST(versiontitle, versiontitles)
    STRLIST(developertitle, developertitles)	
    STRLIST(externalvideo, externalvideos) 
    STRLIST(startup, startups) 
    STRLIST(signature, signatures) 	
    STRLIST(vanity, vanitys) 	
    STRLIST(thankyou, thankyous)	
    STRLIST(who, whos)
    STRLIST(artist, artists) 
    STRLIST(welcome, welcomes) 	
    STRLIST(tag, tags)
#undef GEN


    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString sortTitle READ sortBy CONSTANT)
    Q_PROPERTY(QString sortBy READ sortBy CONSTANT)
    Q_PROPERTY(QString summary READ summary CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QDate release READ releaseDate CONSTANT)
    Q_PROPERTY(int players READ playerCount CONSTANT)
    Q_PROPERTY(float rating READ rating CONSTANT)

    Q_PROPERTY(int releaseYear READ releaseYear CONSTANT)
    Q_PROPERTY(int releaseMonth READ releaseMonth CONSTANT)
    Q_PROPERTY(int releaseDay READ releaseDay CONSTANT)

    Q_PROPERTY(int playCount READ playCount NOTIFY playStatsChanged)
    Q_PROPERTY(int playTime READ playTime NOTIFY playStatsChanged)
    Q_PROPERTY(QDateTime lastPlayed READ lastPlayed NOTIFY playStatsChanged)
    Q_PROPERTY(bool favorite READ isFavorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(bool whitelist READ isWhitelist WRITE setWhitelist NOTIFY whitelistChanged)    


    Assets& assets() const { return *m_assets; }
    Assets* assetsPtr() const { return m_assets; }
    Q_PROPERTY(model::Assets* assets READ assetsPtr CONSTANT)

    Game& setFiles(std::vector<model::GameFile*>&&);
    Game& setCollections(std::vector<model::Collection*>&&);
    const QVector<model::GameFile*>& filesConst() const { Q_ASSERT(!m_files->isEmpty()); return m_files->asList(); }
    const QVector<model::Collection*>& collectionsConst() const { Q_ASSERT(!m_collections->isEmpty()); return m_collections->asList(); }
    QML_OBJMODEL_PROPERTY(model::GameFile, files)
    QML_OBJMODEL_PROPERTY(model::Collection, collections)

private:
    GameData m_data;
    Assets* const m_assets;

signals:
    void launchFileSelectorRequested();
    void favoriteChanged();
    void whitelistChanged();
    void playStatsChanged();

private slots:
    void onEntryPlayStatsChanged();


public:
    explicit Game(QString name, QObject* parent = nullptr);

    Q_INVOKABLE void launch();

    void finalize();
};


bool sort_games(const model::Game* const, const model::Game* const);
} // namespace model
