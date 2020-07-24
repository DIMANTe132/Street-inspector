import QtQuick 2.12
import QtQuick.Window 2.12
import QtPositioning 5.12
import QtLocation 5.12
import QtQuick.Controls 2.12

Window {
    id: win
    visible: true
    property int idcount: 0

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
        }
        zoomLevel: 30

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var coord = map.toCoordinate(Qt.point(mouse.x,mouse.y))
                window.newreport(coord.latitude, coord.longitude)
            }
        }

        MapItemView {
            id: mapItemView
            model: listmodel
            delegate: MapQuickItem {
                coordinate {
                    latitude: lat
                    longitude: longi
                }
                sourceItem: Image {
                    id: image
                    source: "qrc:/icon-map.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            window.showreport(lat, longi)
                        }
                    }
                }
                anchorPoint.x: image.width / 2
                anchorPoint.y: image.height

            }
        }

        BorderImage {
            id: borderImage
            x: 8
            y: 8
            width: 100
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 8
            source: "reload.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    win.close()
                    window.createMarks()
                }
            }
        }

        Connections {
            target: window
            onAddElement: {
                listmodel.append({lat : latitude, longi: longitude});
            }
        }

        PositionSource {
            onPositionChanged: {
                map.center = position.coordinate
            }
        }

        ListModel {
            id: listmodel
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:6;anchors_height:20;anchors_width:20;anchors_x:310;anchors_y:230}
D{i:3;anchors_x:529}
}
##^##*/
