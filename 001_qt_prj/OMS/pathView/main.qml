import QtQuick 2.6
//import QtQuick.Window 2.2

Rectangle {
    visible: true
    //width: 640
    //height: 480
    width:1100
    height:900
    //title: qsTr("Hello World")

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }
    ListModel{
        id:model
        ListElement{url:"qrc:/pathView/images/timg0.jpg"}
        ListElement{url:"qrc:/pathView/images/timg1.jpg"}
        ListElement{url:"qrc:/pathView/images/timg2.jpg"}
        ListElement{url:"qrc:/pathView/images/timg3.jpg"}
        ListElement{url:"qrc:/pathView/images/timg4.jpg"}
    }
    CoverFlow{
        anchors.fill:parent
        model:model
    }
}
