import QtQuick 2.4
import QtQuick.Controls 2.5
import ServerWatcher.Agent 1.0

Dialog {
    width: 200
    height: 450
    property ProcessAgentInfo _agentInfo

    function show(agentInfo){
        _agentInfo = agentInfo
        open()
    }

    Rectangle{
        id:detailBg
        anchors.fill: parent

        Column{
            Row{
                Text {
                    text: qsTr("别名：")
                }

                TextArea{

                }
            }

            Row{
                Text {
                    text: qsTr("路径：")
                }

                TextArea{

                }
            }

            Row{
                Text {
                    text: qsTr("参数：")
                }

                TextArea{

                }
            }

            Row{
                Text {
                    text: qsTr("工作目录：")
                }

                TextArea{

                }
            }

        }
    }
}
