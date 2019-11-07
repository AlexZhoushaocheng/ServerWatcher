import QtQuick 2.4
import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import ServerWatcher.Model 1.0

Item {
    id: element
    Rectangle {
        id: background
        color: "#7c8489"
        anchors.fill: parent

        Rectangle { //顶部操作区
            id: operatorPanel
            height: 55
            color: "#f5b977"
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            Button {
                id: button
                x: 368
                y: 8
                text: qsTr("+")
            }
        }

        Component{
            id:listViewDelegate
            Rectangle{
                id:itemBg
                height: 40
                width: parent.width
                color: model.state === 2 ? "#5579ed" : "red"

                Text {
                    id: name
                    text: qsTr(model.alias)
                }
            }
        }

        ListView {//服务显示列表
            id: tableView
            anchors.bottom: stackView.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: operatorPanel.bottom
            delegate: listViewDelegate
            model: ServerListModel
        }

        StackView{ //
            id:stackView
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 260
        }
    }
}
