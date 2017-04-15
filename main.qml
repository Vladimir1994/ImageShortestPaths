import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Image shortest paths")

    property variant legendWindow;

    ScrollView  {
        anchors.fill: parent
        anchors.margins: 5
        Image {
            id: im
            source: "image://ImageProvider/im"

            property bool selectingStartPoint: false
            MouseArea {
                id: imMa
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                cursorShape: im.selectingStartPoint ? Qt.CrossCursor
                                                    : Qt.ArrowCursor
                enabled: im.selectingStartPoint
                onClicked: {
                    if (mouse.button & Qt.LeftButton)
                        ImageProvider.setStartPoint(mouseX, mouseY)
                    else
                        im.selectingStartPoint = false
                }
            }
        }
    }

    Rectangle {
        id: waitRect
        anchors.fill: parent
        visible: ImageProvider.algorithmInProcess
        color: "black"
        opacity: 0.8
        BusyIndicator {
            anchors.centerIn: parent
            running: waitRect.visible
        }
        MouseArea {
            anchors.fill: parent
        }
    }

    Connections {
        target: ImageProvider
        onImageChanged: {
            im.source = "image://ImageProvider/im?" + Math.random()
        }
    }

    Timer {
        id: unblocker
        interval: 10
        onTriggered: {
            ImageProvider.computePaths()
        }
    }


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open image")
                onTriggered: openFileDialog.open();
            }
            MenuItem {
                text: qsTr("&Save image")
                onTriggered: saveFileDialog.open();
                enabled: ImageProvider.imageExists
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("Tools")

            MenuItem {
                text: qsTr("&Select start point")
                onTriggered: {
                    im.selectingStartPoint = true
                }
                enabled: !im.selectingStartPoint && ImageProvider.imageExists
            }
            MenuItem {
                text: qsTr("&Compute shortest paths")
                onTriggered: {
                    ImageProvider.algorithmInProcess = true
                    unblocker.start()
                }
                enabled: ImageProvider.startPointSelected
            }
            MenuItem {
                text: qsTr("&Clear results")
                onTriggered: ImageProvider.clearResults();
                enabled: ImageProvider.imageExists
            }
            MenuItem {
                id: legendButton
                property bool legendOpend: false
                text: qsTr("&Open legend")
                enabled: !legendOpend
                onTriggered: {
                    if (legendOpend)
                        return
                    var component = Qt.createComponent("Legend.qml");
                    legendWindow = component.createObject(mainWindow);
                    legendWindow.show();
                    legendOpend = true
                }
            }
        }
    }

    FileDialog {
        id: openFileDialog
        title: "Please select an image"
        folder: shortcuts.home
        nameFilters: ["Image files (*.jpg *.png)"]

        onAccepted: {
            if (!ImageProvider.loadImage(openFileDialog.fileUrl))
                loadMessageDialog.open()
            close()
        }
        onRejected: {
            close()
        }
    }

    FileDialog {
        id: saveFileDialog
        title: "Please select a folder"
        folder: shortcuts.home
        selectExisting: false
        nameFilters: ["Image files (*.jpg *.png)"]

        onAccepted: {
            if (!ImageProvider.saveImage(saveFileDialog.fileUrl))
                saveMessageDialog.open()
            close()
        }
        onRejected: {
            close()
        }
    }

    MessageDialog {
        id: saveMessageDialog
        title: "Error"
        text: "Unable to save this file."
        onAccepted: {
            close()
        }
    }

    MessageDialog {
        id: loadMessageDialog
        title: "Error"
        text: "Unable to load this file."
        onAccepted: {
            close()
        }
    }
}

