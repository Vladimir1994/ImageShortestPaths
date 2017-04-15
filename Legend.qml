import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

Window {
    width: 300
    height: 130
    maximumHeight: 130
    maximumWidth: 300
    minimumHeight: 130
    minimumWidth: 300
    property int lineWidth: 150

    onClosing: {
        legendButton.legendOpend = false
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 3

        Row {
            spacing: lineWidth - boxOne.width
            CheckBox {
                id: boxOne
                text: qsTr("metric one")
                onCheckedChanged: ImageProvider.setPathEnabled(0, checked)
            }
            Rectangle {
                width: 15
                height: 15
                color: boxOne.checked ? ImageProvider.pathOneColor : "lightgray"

                MouseArea {
                    id: ma1
                    anchors.fill: parent
                    onClicked: ImageProvider.changePathColor(0)
                    enabled: boxOne.checked
                }
            }
        }

        Row {
            spacing: lineWidth - boxTwo.width
            CheckBox {
                id: boxTwo
                text: qsTr("metric two")
                onCheckedChanged: ImageProvider.setPathEnabled(1, checked)
            }
            Rectangle {
                width: 15
                height: 15
                color: boxTwo.checked ? ImageProvider.pathTwoColor : "lightgray"
                MouseArea {
                    anchors.fill: parent
                    onClicked: ImageProvider.changePathColor(1)
                    enabled: boxTwo.checked
                }
            }
        }

        Row {
            spacing: lineWidth - boxThree.width
            CheckBox {
                id: boxThree
                text: qsTr("metric three")
                onCheckedChanged: ImageProvider.setPathEnabled(2, checked)
            }
            Rectangle {
                width: 15
                height: 15
                color: boxThree.checked ? ImageProvider.pathThreeColor
                                        : "lightgray"
                MouseArea {
                    anchors.fill: parent
                    onClicked: ImageProvider.changePathColor(2)
                    enabled: boxThree.checked
                }
            }
        }

        Row {
            spacing: lineWidth - boxFour.width
            CheckBox {
                id: boxFour
                text: qsTr("metric four")
                onCheckedChanged: ImageProvider.setPathEnabled(3, checked)
            }
            Rectangle {
                width: 15
                height: 15
                color: boxFour.checked ? ImageProvider.pathFourColor
                                       : "lightgray"
                MouseArea {
                    anchors.fill: parent
                    onClicked: ImageProvider.changePathColor(3)
                    enabled: boxFour.checked
                }
            }
        }

        Row {
            x: 21
            spacing: lineWidth - spText.width - x
            Label {
                id: spText
                text: qsTr("start point")
            }

            Rectangle {
                width: 15
                height: 15
                color: ImageProvider.startPointColor
                MouseArea {
                    anchors.fill: parent
                    onClicked: ImageProvider.changeStartPointColor()
                }
            }
        }
    }
}

