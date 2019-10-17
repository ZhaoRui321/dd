import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.3
import Qt.labs.folderlistmodel 2.1
//import an.qt.FileIO 1.0
import Qt.labs.settings 1.0
import test.filecontent 1.0
//import QtQuick.VirtualKeyboard 2.2


Rectangle {
    anchors.fill: parent;
    id: setting;
    color: "lightblue";
    property alias slidertext: slidertext
    property alias slider: slider
    z: 3;
    width: 640;

    property var sl : Math.floor(rangeSlider.first.value)*10;
    property var sh : Math.floor(rangeSlider.second.value)*10;
    property var ss:  slider.value



    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        width: 640

        ToolSeparator {
            id: toolSeparator9
            Layout.fillHeight: true
            opacity: 0
        }

        RowLayout {
            id: rowLayout1
            width: 800
            spacing: 15
            Layout.fillHeight: true
            Layout.fillWidth: true


            ToolSeparator {
                id: toolSeparator10
                opacity: 0
            }

            Text {        //质量范围
                id: massfiled
                width: 80
                height: 20
                text: qsTr("质量范围")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.fillHeight: false
                Layout.fillWidth: false
                font.bold: true
                font.pixelSize: 30
            }
            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100


                RowLayout {
                    id: rowLayout3
                    width: 100
                    height: 100
                    Layout.fillHeight: true
                    Layout.fillWidth: true


                    TextField {
                        id: lefttext;
                        width: 50
                        height: 30
                        text:  Math.floor(rangeSlider.first.value)*10;
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignLeft
                        background: Rectangle{
                            anchors.fill: parent;
                            color: "lightblue";
                        }
                        //        onPressed:
                        //            vkb.visible = true;
                        onFocusChanged:
                            rangeSlider.first.value = Number(text)/10;
                        validator: DoubleValidator{
                            //id: intval;
                            decimals: 0;
                            bottom: 0;
                            top: 1500;
                            notation:DoubleValidator.StandardNotation
                        }
                    }
                    ToolSeparator {
                        id: toolSeparator
                        opacity: 0
                        Layout.fillHeight: false
                        Layout.fillWidth: true
                    }

                    TextField {
                        id: righttext;
                        //x: rangeSlider.second.position*rangeSlider.width+rangeSlider.x;
                        width: 50
                        height: 30
                        text:  Math.floor(rangeSlider.second.value)*10;
                        Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                        horizontalAlignment: Text.AlignRight
                        font.pixelSize: 18
                        background: Rectangle{
                            anchors.fill: parent;
                            color: "lightblue";
                        }
                        //        onPressed:
                        //            vkb.visible = true;
                        onFocusChanged:
                            rangeSlider.second.value = Number(text)/10;
                        validator: DoubleValidator{
                            id: intval;
                            decimals: 0;
                            bottom: 0;
                            top: 1500;
                            notation:DoubleValidator.StandardNotation
                        }
                    }
                }

                RangeSlider {          //质量范围
                    id: rangeSlider
                    width: 500
                    height: 40
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    clip: false
                    font.capitalization: Font.AllUppercase
                    wheelEnabled: true
                    stepSize: 1
                    to: 150
                    from: 0
                    first.value: 10
                    second.value: 100;
                }


            }

            ToolSeparator {
                id: toolSeparator6
                opacity: 0
            }

        }

        RowLayout {
            id: rowLayout2
            width: 640
            spacing: 15
            Layout.fillHeight: true
            Layout.fillWidth: true

            ToolSeparator {
                id: toolSeparator11
                opacity: 0
            }

            Text {        //扫描速度
                id: speed
                width: 80
                height: 20
                text: qsTr("扫描速度")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.fillHeight: false
                Layout.fillWidth: false
                font.bold: true
                font.pixelSize: 30
            }

            ColumnLayout {
                id: columnLayout2
                width: 100
                height: 100

                RowLayout {
                    id: rowLayout4
                    width: 100
                    height: 100



                    ToolSeparator {
                        id: toolSeparator2
                        opacity: 0
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: slidertext;
                        background: Rectangle{
                            anchors.fill: parent;
                            color: "lightblue";
                        }
                        width: 60
                        height: 30
                        text: slider.value
                        font.pixelSize: 18
                        //        onPressed:
                        //            vkb.visible = true;
                        onFocusChanged:
                            slider.value = Number(text);
                        validator: DoubleValidator{
                            //id: intval1;
                            decimals: 0;
                            bottom: 0;
                            top: 5000;
                            notation:DoubleValidator.StandardNotation
                        }
                    }
                    ToolSeparator {
                        id: toolSeparator1
                        opacity: 0
                        Layout.fillWidth: true
                    }
                }

                Slider {           //扫描速度
                    id: slider
                    width: 500
                    height: 20
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    stepSize: 100
                    to: 5000
                    value: 2000;
                }

            }

            ToolSeparator {
                id: toolSeparator7
                opacity: 0
            }


        }

        ToolSeparator {
            id: toolSeparator8
            opacity: 0
            visible: true
            Layout.fillHeight: true
        }

        RowLayout {
            id: rowLayout
            width: 640
            spacing: 25
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            ToolSeparator {
                id: toolSeparator5
                opacity: 0
                visible: true
            }

            Button {
                id: usermodel
                width: 150
                height: 60
                text: qsTr("自定义")
                Layout.fillHeight: false
                Layout.fillWidth: true
                highlighted: true;

                onClicked: {
                    setting.userModle();
                    usermodel.highlighted = true;
                    smallmodel.highlighted = false;
                    bigmodel.highlighted = false;
                }
            }

            Button {
                id: smallmodel
                width: 150
                height: 60
                text: qsTr("小分子模式")
                Layout.fillHeight: false
                Layout.fillWidth: true

                onClicked: {
                    setting.smallMassModel();
                    usermodel.highlighted = false;
                    smallmodel.highlighted = true;
                    bigmodel.highlighted = false;
                }
            }

            Button {
                id: bigmodel
                width: 150
                height: 60
                text: qsTr("大分子模式")
                Layout.fillHeight: false
                Layout.fillWidth: true

                onClicked: {
                    setting.bigMassModel();
                    usermodel.highlighted = false;
                    smallmodel.highlighted = false;
                    bigmodel.highlighted = true;
                }
            }

            ToolSeparator {
                id: toolSeparator4
                opacity: 0
                visible: true
            }

        }

        ToolSeparator {
            id: toolSeparator3
            opacity: 0
            visible: true
            Layout.fillHeight: true
        }

    }
    function bigMassModel() {
        lefttext.enabled = true;
        righttext.enabled = true;
        slidertext.enabled = true;
        rangeSlider.enabled = true;
        slider.enabled = true;
        rangeSlider.first.value = 50;
        rangeSlider.second.value = 120;
        slider.value = 2000;
        rangeSlider.enabled = false;
        slider.enabled = false;
        lefttext.enabled = false;
        righttext.enabled = false;
        slidertext.enabled = false;
    }

    function smallMassModel() {
        lefttext.enabled = true;
        righttext.enabled = true;
        slidertext.enabled = true;
        rangeSlider.enabled = true;
        slider.enabled = true;
        rangeSlider.first.value = 10;
        rangeSlider.second.value = 80;
        slider.value = 3000;
        rangeSlider.enabled = false;
        slider.enabled = false;
        lefttext.enabled = false;
        righttext.enabled = false;
        slidertext.enabled = false;
    }

    function userModle() {
        lefttext.enabled = true;
        righttext.enabled = true;
        slidertext.enabled = true;
        rangeSlider.enabled = true;
        slider.enabled = true;
    }

}
