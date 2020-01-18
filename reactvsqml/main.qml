/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/


import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import backend 1.0

ApplicationWindow {
    id: root
    width: 500
    height: 400
    visible: true
    title: "Qml Vs React - Fabrice Lainard Programming"

    ColumnLayout {

        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 100;


        TextField {
            height: 50

            text: backend.userName
            placeholderText: qsTr("User name")

            onTextChanged: backend.userName = text
        }
        Button {
            text: "Add element"
            onClicked: backend.addListElement( backend.userName)
        }

        ListView {
            height: 300
            Layout.fillWidth: true

          clip: true
            ScrollBar.vertical: ScrollBar {}
            spacing: 5
            model: backend.list
            delegate: Rectangle {
                height: 25
                width: 200
                color: "lightgray"
                Text { text: modelData; anchors.centerIn: parent }
            }
        }
    }
}
