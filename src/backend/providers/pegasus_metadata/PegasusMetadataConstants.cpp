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


#include "PegasusMetadataConstants.h"


namespace providers {
namespace pegasus {
namespace parser {

Constants::Constants()
    : coll_attribs {
        { QStringLiteral("shortname"), CollAttrib::SHORT_NAME },
        { QStringLiteral("launch"), CollAttrib::LAUNCH_CMD },
        { QStringLiteral("command"), CollAttrib::LAUNCH_CMD },
        { QStringLiteral("workdir"), CollAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("cwd"), CollAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("directory"), CollAttrib::DIRECTORIES },
        { QStringLiteral("directories"), CollAttrib::DIRECTORIES },
        { QStringLiteral("extension"), CollAttrib::EXTENSIONS },
        { QStringLiteral("extensions"), CollAttrib::EXTENSIONS },
        { QStringLiteral("file"), CollAttrib::FILES },
        { QStringLiteral("files"), CollAttrib::FILES },
        { QStringLiteral("regex"), CollAttrib::REGEX },
        { QStringLiteral("ignore-extension"), CollAttrib::EXTENSIONS },
        { QStringLiteral("ignore-extensions"), CollAttrib::EXTENSIONS },
        { QStringLiteral("ignore-file"), CollAttrib::FILES },
        { QStringLiteral("ignore-files"), CollAttrib::FILES },
        { QStringLiteral("ignore-regex"), CollAttrib::REGEX },
        { QStringLiteral("summary"), CollAttrib::SHORT_DESC },
        { QStringLiteral("description"), CollAttrib::LONG_DESC },
        // sort name variations
        { QStringLiteral("sortby"), CollAttrib::SORT_BY },
        { QStringLiteral("sort_by"), CollAttrib::SORT_BY },
        { QStringLiteral("sort-by"), CollAttrib::SORT_BY },
    }
    , game_attribs {
        { QStringLiteral("file"), GameAttrib::FILES },
        { QStringLiteral("files"), GameAttrib::FILES },
        { QStringLiteral("launch"), GameAttrib::LAUNCH_CMD },
        { QStringLiteral("command"), GameAttrib::LAUNCH_CMD },
        { QStringLiteral("workdir"), GameAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("cwd"), GameAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("developer"), GameAttrib::DEVELOPERS },
        { QStringLiteral("developers"), GameAttrib::DEVELOPERS },
        { QStringLiteral("publisher"), GameAttrib::PUBLISHERS },
        { QStringLiteral("publishers"), GameAttrib::PUBLISHERS },
        { QStringLiteral("genre"), GameAttrib::GENRES },
        { QStringLiteral("genres"), GameAttrib::GENRES },
        { QStringLiteral("website"), GameAttrib::WEBSITES },
        { QStringLiteral("websites"), GameAttrib::WEBSITES },
        { QStringLiteral("source"), GameAttrib::SOURCES },
        { QStringLiteral("sources"), GameAttrib::SOURCES },
        { QStringLiteral("version"), GameAttrib::VERSIONS },
        { QStringLiteral("versions"), GameAttrib::VERSIONS },
        { QStringLiteral("item"), GameAttrib::ITEMS },
        { QStringLiteral("items"), GameAttrib::ITEMS },
        { QStringLiteral("tier"), GameAttrib::TIERS },
        { QStringLiteral("tiers"), GameAttrib::TIERS },		
        { QStringLiteral("twitter"), GameAttrib::TWITTERS },
        { QStringLiteral("twitters"), GameAttrib::TWITTERS },
        { QStringLiteral("facebook"), GameAttrib::FACEBOOKS },
        { QStringLiteral("facebooks"), GameAttrib::FACEBOOKS },
        { QStringLiteral("instagram"), GameAttrib::INSTAGRAMS },
        { QStringLiteral("instagrams"), GameAttrib::INSTAGRAMS },
        { QStringLiteral("snapchat"), GameAttrib::SNAPCHATS },
        { QStringLiteral("snapchats"), GameAttrib::SNAPCHATS },
        { QStringLiteral("pinterest"), GameAttrib::PINTERESTS },
        { QStringLiteral("pinterests"), GameAttrib::PINTERESTS },
        { QStringLiteral("youtube"), GameAttrib::YOUTUBES },
        { QStringLiteral("youtubes"), GameAttrib::YOUTUBES },
        { QStringLiteral("tiktok"), GameAttrib::TIKTOKS },
        { QStringLiteral("tiktoks"), GameAttrib::TIKTOKS },
        { QStringLiteral("discord"), GameAttrib::DISCORDS },
        { QStringLiteral("discords"), GameAttrib::DISCORDS },
        { QStringLiteral("twitch"), GameAttrib::TWITCHS },
        { QStringLiteral("twitchs"), GameAttrib::TWITCHS },
        { QStringLiteral("developertitle"), GameAttrib::DEVELOPERTITLES },
        { QStringLiteral("developertitles"), GameAttrib::DEVELOPERTITLES },
        { QStringLiteral("versiontitle"), GameAttrib::VERSIONTITLES },
        { QStringLiteral("versiontitles"), GameAttrib::VERSIONTITLES },			
        { QStringLiteral("externalvideo"), GameAttrib::EXTERNALVIDEOS },
        { QStringLiteral("externalvideos"), GameAttrib::EXTERNALVIDEOS },  
        { QStringLiteral("startup"), GameAttrib::STARTUPS },
        { QStringLiteral("startups"), GameAttrib::STARTUPS },
        { QStringLiteral("signature"), GameAttrib::SIGNATURES },
        { QStringLiteral("signatures"), GameAttrib::SIGNATURES },
        { QStringLiteral("vanity"), GameAttrib::VANITYS },
        { QStringLiteral("vanitys"), GameAttrib::VANITYS },		
        { QStringLiteral("thankyou"), GameAttrib::THANKYOUS },
        { QStringLiteral("thankyous"), GameAttrib::THANKYOUS },   		
        { QStringLiteral("who"), GameAttrib::WHOS },
        { QStringLiteral("whos"), GameAttrib::WHOS },
        { QStringLiteral("artist"), GameAttrib::ARTISTS },
        { QStringLiteral("artists"), GameAttrib::ARTISTS },	
        { QStringLiteral("welcome"), GameAttrib::WELCOMES },
        { QStringLiteral("welcomes"), GameAttrib::WELCOMES },			
        { QStringLiteral("tag"), GameAttrib::TAGS },
        { QStringLiteral("tags"), GameAttrib::TAGS },
        { QStringLiteral("players"), GameAttrib::PLAYER_COUNT },
        { QStringLiteral("summary"), GameAttrib::SHORT_DESC },
        { QStringLiteral("description"), GameAttrib::LONG_DESC },
        { QStringLiteral("release"), GameAttrib::RELEASE },
        { QStringLiteral("rating"), GameAttrib::RATING },
        // sort title variations
        { QStringLiteral("sorttitle"), GameAttrib::SORT_BY },
        { QStringLiteral("sortname"), GameAttrib::SORT_BY },
        { QStringLiteral("sort_title"), GameAttrib::SORT_BY },
        { QStringLiteral("sort_name"), GameAttrib::SORT_BY },
        { QStringLiteral("sort-title"), GameAttrib::SORT_BY },
        { QStringLiteral("sort-name"), GameAttrib::SORT_BY },
        { QStringLiteral("sortby"), GameAttrib::SORT_BY },
        { QStringLiteral("sort_by"), GameAttrib::SORT_BY },
        { QStringLiteral("sort-by"), GameAttrib::SORT_BY },
    }
    /*, gamefile_attribs {
        { QStringLiteral("name"), GameFileAttrib::TITLE },
        { QStringLiteral("title"), GameFileAttrib::TITLE },
        { QStringLiteral("launch"), GameFileAttrib::LAUNCH_CMD },
        { QStringLiteral("command"), GameFileAttrib::LAUNCH_CMD },
        { QStringLiteral("workdir"), GameFileAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("cwd"), GameFileAttrib::LAUNCH_WORKDIR },
        { QStringLiteral("summary"), GameFileAttrib::SHORT_DESC },
        { QStringLiteral("description"), GameFileAttrib::LONG_DESC },
    }*/
    , rx_asset_key(QStringLiteral(R"(^assets?\.(.+)$)"))
    , rx_count_range(QStringLiteral("^(\\d+)(-(\\d+))?$"))
    , rx_percent(QStringLiteral("^\\d+%$"))
    , rx_float(QStringLiteral("^\\d(\\.\\d+)?$"))
    , rx_date(QStringLiteral("^(\\d{4})(-(\\d{1,2}))?(-(\\d{1,2}))?$"))
    , rx_linebreak(QStringLiteral(R"((?<!\\)\\n)"))
{}

} // namespace parser
} // namespace pegasus
} // namespace providers
