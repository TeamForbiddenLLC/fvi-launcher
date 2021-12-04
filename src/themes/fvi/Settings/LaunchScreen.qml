import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQml.Models 2.10
import QtMultimedia 5.9
import QtQuick.Layouts 1.11
import "../Global"
import "../GridView"
import "../Lists"
import "../utils.js" as Utils

FocusScope {
id: root

    property string launchcommand
    property var game: currentGame
			
    	Image {
    id: logo

		source: game.assets.logo
        smooth: true
        Behavior on opacity { NumberAnimation { duration: 500 } }
		visible: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        sourceSize: Qt.size(parent.width, parent.height)
        asynchronous: true

		}	
			
    Item {
    id: launchBar

        anchors {
            left: parent.left;
            right: parent.right;
            top: parent.top;
        }
        height: vpx(200)
        z: 100
        
        Rectangle {
            anchors {
                left: parent.left;
                right: parent.right;
                top: parent.top;
                bottom: parent.bottom;
                margins: vpx(70)
            }
            color: theme.main
            radius: height/2
            border.width: vpx(2)
            border.color: "#d9d9d9"

            TextInput {
            id: launchBarInput

                focus: true
				enabled: true
                anchors {
                    left: parent.left; leftMargin: vpx(25)
                    right: parent.right; rightMargin: vpx(25)
                    top: parent.top;
                    bottom: parent.bottom;
                    margins: vpx(10)
                }
                validator: RegExpValidator { regExp: /[0-9a-zA-Z]+/ }
                verticalAlignment: Text.AlignVCenter
                color: theme.text
                font.family: bodyFont.name
                font.pixelSize: vpx(24)
                maximumLength: 200
                onTextChanged: { 
                launchcommand = launchBarInput.text.toLowerCase();
                api.memory.set('LaunchOptions.' + game.title, launchcommand);
                }

            }

            Text {
            id: inputDefault

                focus: true
                anchors {
                    left: parent.left; leftMargin: vpx(25)
                    right: parent.right; rightMargin: vpx(25)
                    top: parent.top;
                    bottom: parent.bottom;
                    margins: vpx(10)
                }
                text: "No " + game.title + " launch options found. When finished press Escape."			
				horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: theme.text
                opacity: launchBarInput.length > 0 ? 0 : 0.3
                Behavior on opacity { NumberAnimation { duration: 50 } }
                font.family: bodyFont.name
                font.pixelSize: vpx(24)
            }

            Rectangle {
            id: highlightborder

                anchors.fill: parent
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: "#eb8c8a" }
                    GradientStop { position: 1.0; color: "#8bb7e4" }
                }
                visible: false
            }

            Rectangle {
            id: highlightbordermask

                anchors.fill: parent
                color: "transparent"
                radius: height/2
                border.width: vpx(2)
                border.color: "white"
                visible: false
            }

            OpacityMask {
                anchors.fill: highlightborder
                source: highlightborder
                maskSource: highlightbordermask
                opacity: launchBarInput.focus
                Behavior on opacity { NumberAnimation { duration: 50 } }
            }
        }
        
    }	
	
                // List specific input
                Keys.onPressed: {                    
                    // Back
                    if (api.keys.isCancel(event) && !event.isAutoRepeat) {
                        event.accepted = true;
                        sfxBack.play();
                        previousScreen();
                    }
				}
				
   // Helpbar buttons
    ListModel {
        id: launchHelpModel

        ListElement {
            name: "Back"
            button: "cancel"
        }
    }
    
    onFocusChanged: { if (focus) currentHelpbarModel = launchHelpModel; }
	
}
