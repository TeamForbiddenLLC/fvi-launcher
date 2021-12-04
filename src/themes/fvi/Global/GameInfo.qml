// gameOS theme
// Copyright (C) 2018-2020 Seth Powell 
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

import QtQuick 2.0
import QtQuick.Layouts 1.11
import "qrc:/qmlutils" as PegasusUtils

Item {
id: infocontainer

    property var gameData: currentGame

    // Game title
    Text {
    id: gametitle
        
        text: gameData ? gameData.title : ""
        
        anchors {
            top:    parent.top;
            left:   parent.left;
            right:  parent.right
        }
        
        color: theme.text
        font.family: titleFont.name
        font.pixelSize: vpx(44)
        font.bold: true
        horizontalAlignment: Text.AlignHLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    // Meta data
    Item {
    id: metarow

        height: vpx(50)
        anchors {
            top: gametitle.bottom; 
            left: parent.left
            right: parent.right
        }

        // Developer box
        Text {
        id: developertitle

            width: contentWidth
            height: parent.height
            anchors { left: parent.left; }
            verticalAlignment: Text.AlignVCenter
            text: game.developertitle
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            font.bold: true
		color: if (game.tier === "0") return theme.accent
      else if (game.tier === "1") return theme.accent1
      else if (game.tier === "2") return theme.accent2
      else if (game.tier === "3") return theme.accent3
      else return theme.accent
        }

        Text {
        id: developertext
            
            width: contentWidth
            height: parent.height
            anchors { left: developertitle.right; leftMargin: vpx(5) }
            verticalAlignment: Text.AlignVCenter
            text: game.item === "1" ? game.who : game.developer
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            color: theme.text
        }

        Rectangle {
        id: divider1
            width: vpx(2)
            anchors {
                left: developertext.right; leftMargin: (25)
                top: parent.top; topMargin: vpx(10)
                bottom: parent.bottom; bottomMargin: vpx(10)
            }
            opacity: 0.2
        }

        // Version box
        Text {
        id: versiontitle

            width: contentWidth
            height: parent.height
            anchors { left: divider1.right; leftMargin: vpx(25) }
            verticalAlignment: Text.AlignVCenter
            text: game.versiontitle
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            font.bold: true
		color: if (game.tier === "0") return theme.accent
      else if (game.tier === "1") return theme.accent1
      else if (game.tier === "2") return theme.accent2
      else if (game.tier === "3") return theme.accent3
      else return theme.accent
        }

        Text {
        id: versiontext

            width: contentWidth
            height: parent.height
            anchors { left: versiontitle.right; leftMargin: vpx(5) }
            verticalAlignment: Text.AlignVCenter
            text: game.item === "1" ? game.artist : game.version
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            color: theme.text
        }

        Rectangle {
        id: divider2
            width: vpx(2)
			visible: game.item === "0"
            anchors {
                left: versiontext.right; leftMargin: (25)
                top: parent.top; topMargin: vpx(10)
                bottom: parent.bottom; bottomMargin: vpx(10)
            }
            opacity: 0.2
        }

        // Genre box
        Text {
        id: genretitle

            width: contentWidth
            height: parent.height
			visible: game.item === "0"
            anchors { left: divider2.right; leftMargin: vpx(25) }
            verticalAlignment: Text.AlignVCenter
            text: "Genre: "
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            font.bold: true
            color: theme.accent
        }

        Text {
        id: genretext

            anchors { 
                left: genretitle.right; leftMargin: vpx(5)
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            verticalAlignment: Text.AlignVCenter
			visible: game.item === "0"
            text: gameData ? gameData.genre : ""
            font.pixelSize: vpx(16)
            font.family: subtitleFont.name
            elide: Text.ElideRight
            color: theme.text
        }
    }

    // Description
    PegasusUtils.AutoScroll
    {
    id: gameDescription
    
        anchors {
            left: parent.left; 
            right: parent.right;
            top: metarow.bottom
            bottom: parent.bottom;
        }

        Text {
            width: parent.width
            text: gameData && (gameData.summary || gameData.description) ? gameData.description + gameData.thankyou || gameData.summary : "No description available"
            font.pixelSize: vpx(16)
            font.family: bodyFont.name
            color: theme.text
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
        }
    }
    
}
