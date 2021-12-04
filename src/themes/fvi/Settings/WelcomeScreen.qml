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
import QtGraphicalEffects 1.0
import QtMultimedia 5.9
import QtQuick.Layouts 1.11
import SortFilterProxyModel 0.2
import QtQml.Models 2.10
import "../Global"
import "../GridView"
import "../Lists"
import "../utils.js" as Utils

FocusScope {
id: root

    property var game: currentGame
    focus: true
	
    	Image {
    id: screenshot

        anchors.fill: parent
        asynchronous: true
        fillMode: Image.PreserveAspectCrop
		source:  "http://forbidden.gg/assets/media/placeholder/100/Signature.png"
        smooth: true
        Behavior on opacity { NumberAnimation { duration: 500 } }
		visible: true
	
		}
	

        Video {
                
        id: videocomponent

            anchors.fill: parent
			source:  game.welcome
            fillMode: VideoOutput.PreserveAspectCrop
            muted: false
            autoPlay: true
		    visible: true            
        
        }
	
    // Clear logo
    Image {
    id: logo

        width: root.width - vpx(70) - globalMargin
        height: ((root.width - globalMargin * 2) / 6.0) + vpx(60)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        sourceSize: Qt.size(parent.width, parent.height)
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }
	

    DropShadow {
    id: logoshadow

        anchors.fill: logo
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 12
        color: "#000000"
        source: logo
        opacity: 1
    }

    Item {
    id: container

        width: launchText.width + vpx(50)
        height: launchText.height + vpx(50)

        property real centerOffset: logo.paintedHeight/2
        
        anchors {
            top: logo.verticalCenter; topMargin: centerOffset + vpx(250)
            horizontalCenter: logo.horizontalCenter
        }
        
        //color: theme.secondary

        Rectangle {
        id: regborder

            anchors.fill: parent
            color: "black"
            border.width: vpx(1)
            border.color: "white"
            opacity: 0.2
            radius: height/2
        }

        Text {
        id: launchText

            text: "Press any key to return"
            width: contentWidth
            height: contentHeight
            font.family: titleFont.name
            font.pixelSize: vpx(24)
            color: theme.text
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // Helpbar buttons
    ListModel {
        id: launchGameHelpModel

        ListElement {
            name: "Back"
            button: "cancel"
        }
    }
    
    onFocusChanged: { if (focus) currentHelpbarModel = launchGameHelpModel; }

    // Input handling
    Keys.onPressed: {

        // Back
        if (api.keys.isCancel(event) && !event.isAutoRepeat) {
            event.accepted = true;
            previousScreen();
        } else {
            previousScreen();
        }
    }

    // Mouse/touch functionality
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            previousScreen();
        }
    }
}