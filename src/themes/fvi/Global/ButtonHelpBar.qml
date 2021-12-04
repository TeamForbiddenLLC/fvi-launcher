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

Item {
id: root

    Component {
        id: buttonhelpDelegate
        Row {
            spacing: 10
            Image {
                source: "http://forbidden.gg/assets/media/theme/keyboard/" + processButtonArt(button).toLowerCase() + ".png"
                width: vpx(36)
                height: vpx(36)
                asynchronous: true
            }
            Text { 
                text: name
				style: Text.Raised;
				styleColor: "black"
                font.family: subtitleFont.name
                font.pixelSize: vpx(16)
                color: theme.text
                height: parent.height
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: currentHelpbarModel
        delegate: buttonhelpDelegate
        orientation: ListView.Horizontal
        layoutDirection: Qt.RightToLeft
        spacing: vpx(20)
    }

    visible: currentHelpbarModel ? true : false

    // Processes the button and will display the correct art based on the button mappings set in Pegasus
    // Necessary as we can't use script in the ListModel
    function processButtonArt(button) {
        var buttonModel;
        switch (button) {
            case "accept":
			buttonModel = api.keys.accept[0].name();
            break;
            case "cancel":
			buttonModel = api.keys.cancel[0].name();
            break;
            case "filters":
			buttonModel = api.keys.filters[0].name();
            break;
            case "details":
			buttonModel = api.keys.details[0].name();
            break;
            case "nextPage":
			buttonModel = api.keys.nextPage[0].name();
            break;
            case "prevPage":
			buttonModel = api.keys.prevPage[0].name();
            break;
            case "pageUp":
			buttonModel = api.keys.pageUp[0].name();
            break;
            case "pageDown":
		     	buttonModel = api.keys.pageDown[0].name();
                break;
            default:
            buttonModel = api.keys.accept[0].name();
		}

            var buttonValue = buttonModel;
            return buttonValue;
           
  
    }
    
}
