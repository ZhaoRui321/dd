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

Rectangle{
    id: smethod;
    anchors.fill: parent;
    color: "#89cff0";
    signal sended(string sl,string sh,string ss,string mn);
    signal loaded(string sl,string sh,string ss);

    Component.onCompleted: {
        listView.loadfile();

        console.log("加载完成...");
        listView.currentIndex = 0;
        listView.settingRef();
    }

    FileContentItem {
        id: content
        datapath: "../OMS/setting/methodSetting/";        // default is craft.obj
        property bool ready: false
        Component.onCompleted: {
            ready = true;
            //GLcode.readFile = processContent;
        }

//        function processContent(process, source) {
//            while( !ready ) {
//                ;
//            }

//            if( source !== undefined ) {
//                filename = source;
//            }
//            console.time('Read file: "' + source + '"');
//            //process(getContent());
//            console.timeEnd('Read file: "' + source + '"');
//            clearContent();  // save memory
//        }
    }

    Settings {
        id: settings;
        property var  input: "unknown";
    }

    Rectangle{              //添加按钮
        id: addList;
        color: "#89cff0";
        width: parent.width*0.3;
        height: 300;
        anchors.top: parent.top;
        anchors.left: parent.left;
        //        border.width: 3;
        //        border.color: "white";
        signal add();
        z: 5;

        Canvas {
            anchors.fill: parent;
            onPaint: {
                var ctx = getContext("2d");
                ctx.fillStyle = "blue";
                ctx.lineWidth = 5;
                ctx.beginPath();
                ctx.moveTo(addList.width*0.15,addList.height*0.5);
                ctx.lineTo(addList.width*0.85,addList.height*0.5);
                ctx.moveTo(addList.width*0.5,addList.height*0.3);
                ctx.lineTo(addList.width*0.5,addList.height*0.7);
                ctx.closePath();
                ctx.stroke();
            }
        }
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                addList.add();
                listView.settingRef();
                //settings.input = listView.model;
            }
            //            onClicked: {
            //                listView.addOne();
            //            }

        }
    }

    Rectangle {             //割线
        width: addList.width;
        height: 3;
        anchors.top: addList.bottom;
        anchors.left: addList.left;
        color: "white";
        z:5;
    }


    Rectangle {              //方法列表
        width: addList.width;
        height: parent.height-300;
        anchors.top: addList.bottom;
        anchors.topMargin: 3;
        anchors.left: addList.left;
        color: "#89cff0";
        z: 1;

        Component{
            id: methodModel

            ListModel{
                //dynamicRoles: true;
//                ListElement{
//                    name: "基本配置";
//                    scanfType : 1;      //1:全扫描  2:SIM  3:MSN
//                    ionType : 1;        //1:正离子 2:负离子
//                    scanfLow : 0;
//                    scanfHigh : 1000;
//                    scanfSpeed:  2000;
//                }
            }
        }// iphoneModel is end

        //动态图标
        Component {
            id: myflickable;
            Flickable {
                id: wrapper
                width: addList.width
                height: 150
                contentHeight: 150;
                contentWidth: 375;

                Rectangle{
                    id: timetip;
                    anchors.left: parent.left;
                    height: 150;
                    width: 300;
                    color: "lightblue";

                    Text{
                        id: coll
                        text: name
                        anchors.centerIn: parent;
                        color: wrapper.ListView.isCurrentItem ? "red" : "black"
                        font.pixelSize: wrapper.ListView.isCurrentItem ? 22 : 18
                        Layout.preferredWidth: 120
                    }


                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            wrapper.ListView.view.currentIndex = index;
                            mouse.accepted = true;
                        }

                        //                        onDoubleClicked: {
                        //                            wrapper.ListView.view.model.remove(index)
                        //                            mouse.accepted = true
                        //                        }
                    }
                }

                Transition {
                    SpringAnimation{
                        property: "contentX"
                        spring: 3
                        damping: 0.1
                        epsilon: 0.25
                    }
                }

                Rectangle {
                    id: removebtn;
                    anchors.right: parent.right;
                    height: 150;
                    width: 75;
                    color: "lightgreen";
                    Text{
                        text: "删除";
                        anchors.centerIn: parent;
                        //                        color: wrapper.ListView.isCurrentItem ? "red" : "black"
                        //                        font.pixelSize: wrapper.ListView.isCurrentItem ? 22 : 18
                        //                        Layout.preferredWidth: 120
                    }

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {

                            wrapper.ListView.view.model.remove(index)
                            mouse.accepted = true
                            //settings.input = listView.model;
                        }
                    }

                }

            }
        }

        //自带左右滑动控件
        Component {
            id: myswipe;

            SwipeDelegate{
                id:delegate;
                height: 210;
                swipe.enabled: listView.currentIndex === index ? 1 : 0;
                swipe.position: listView.currentIndex === index ? 0 : 0;

                background: Rectangle {
                    id: rect;
                    color: delegate.focus ? "lightblue" : "#89cff0";
                   // color: "#89cff0";
                    width: parent.width;
                    border.width: 1;
                    border.color: "lightblue";

                    Text {
                        anchors.left: parent.left;
                        anchors.top: parent.top;
                        anchors.leftMargin: 2;
                        anchors.topMargin: 2;
                        text: "方法" + (index+1);
                        font.bold: false;
                        font.pointSize: 12;
                        color: delegate.focus ? "white" : "black";
                    }

                    TextEdit {
                        id: itemname
                        anchors.centerIn: parent;
                        text: name;
                        //text: scanfType +" "+ ionType +" "+  scanfLow + "\n" + scanfHigh +" "+ scanfSpeed
                        font.bold: true;
                        readOnly: true;
                        verticalAlignment: Text.AlignVCenter;
                        horizontalAlignment: Text.AlignHCenter;
                        font.pointSize: 18;
                        color: delegate.focus ? "white" : "black";
                        onEditingFinished: {
                            console.log(text);
                            if(text === ""){
                                text = content.getFileName();
                            }
                            content.resetfilename(text);
                            listView.model.get(index).name = text;
                            itemname.readOnly = true;
                            vkb.visible = false
                        }

                    }

                    ParallelAnimation {

                        NumberAnimation {
                            properties: "x";
                            target: rect;
                            to: 300;
                            easing.type: Easing.OutInCubic;
                        }
                        NumberAnimation {
                            properties: "opacity";
                            target: rect;
                            to: 0;
                            easing.type: Easing.OutInCubic;
                        }
                    }
                }



                width: parent.width;

                onReleased: {
                    listView.currentIndex = index;
                }

                onClicked: {
                    vkb.visible = false;
                    listView.settingRef();
                }

                onDoubleClicked: {
                    listView.settingRef();
                    listView.currentIndex = index;
                    vkb.visible = true;
                    content.setFileName(listView.model.get(index).name);
                    itemname.readOnly = false;
                    itemname.focus = true;
                }

                swipe.right: Rectangle{
                    id: swipRightRect;
                    width: parent.width*0.4;
                    height: parent.height;
                    anchors.right: parent.right;

                    MultiPointTouchArea{
                        anchors.fill: parent;
                        onReleased: {
                            listView.deletefile(index);
                            delegate.ListView.view.model.remove(index);
                            //mouse.accepted = true
                            //内存中还需删除
                        }
                    }

                    clip: true;
                    color: "lightgray";
                    Text {
                        id: textInSwipeRightRect;
                        anchors.fill: parent;
                        text: qsTr("删除");
                        font.pixelSize: parent.height*0.3;
                        verticalAlignment: Text.AlignVCenter;
                        horizontalAlignment: Text.AlignHCenter;
                        color: "red";
                    }
                }

                swipe.left: Rectangle{
                    id: swipeLeft;
                    width: parent.width;
                    height: parent.height;
                    anchors.right: parent.right;
                    clip: true;
                    z: 0;

                    Item {
                        anchors.fill: parent;
                        Rectangle {
                            anchors.left: parent.left;
                            anchors.top: parent.top;
                            anchors.bottom: parent.bottom;
                            width: parent.width*0.5;

                            MultiPointTouchArea {
                                anchors.fill: parent;
                                onReleased: {
                                    delegate.swipe.close();
                                    listView.settingSave();
                                    listView.model.move(index,0,1);
                                    //还需保存信息save()
                                }
                            }
                            clip: true;
                            color: "lightgray";
                            Text {
                                anchors.fill: parent;
                                text: qsTr("保存");
                                font.pixelSize: parent.height*0.3;
                                verticalAlignment: Text.AlignVCenter;
                                horizontalAlignment: Text.AlignHCenter;
                                color: "white";
                            }
                        }

                        Rectangle {
                            anchors.right: parent.right;
                            anchors.top: parent.top;
                            anchors.bottom: parent.bottom;

                            width: parent.width*0.5;

                            MouseArea {
                                anchors.fill: parent;
                                onReleased: {
                                    delegate.swipe.close();
                                    listView.settingSave();
                                    smethod.loaded(setting.sl,setting.sh,setting.ss);
                                    smethod.sended(setting.sl,setting.sh,setting.ss,listView.model.get(index).name);
                                    console.log("已发送....")
                                    //保存内容
                                    //执行内容
                                    //跳转窗口
                                }
                            }


                            clip: true;
                            color: "lightgreen";
                            Text {
                                anchors.fill: parent;
                                text: qsTr("执行");
                                font.pixelSize: parent.height*0.3;
                                verticalAlignment: Text.AlignVCenter;
                                horizontalAlignment: Text.AlignHCenter;
                                color: "white";
                            }
                        }

                    }
                }
            }


        }

        ListView{
            id: listView
            anchors.top: parent.top;
            anchors.left: parent.left;
            width: parent.width;
            height: parent.height;
            delegate: myswipe;
            //model: datalist;
            model: methodModel.createObject(listView)
            focus: true
            //verticalLayoutDirection: ListView.BottomToTop;

            highlight: Rectangle{
                color: "lightblue"
            }



            //          populate
            //         *  populate指定一个过度动画，在listView第一次实例化或者因为Model变化而需要创建Item时应用
            //         *  下面就是产生一个渐变效果

            //            populate: Transition{
            //                NumberAnimation{
            //                    property: "opacity"
            //                    from: 0
            //                    to: 1.0
            //                    duration: 400
            //                }
            //            }//populate Transition is end

                        add:Transition {
                            ParallelAnimation{
                                NumberAnimation{
                                    property: "opacity"
                                    from: 0
                                    to : 1.0
                                    duration: 100
                                }

                                NumberAnimation{
                                    property: "y"
                                    from: 0
                                    duration:  400
                                }
                            }
                        }// add transition is end

            //  displaced属性
            //         *  此属性用于指定通用的、由于model变化导致Item位移时的动画效果，还有removeDisplaced、moveDisplaced
            //         *  如果同时指定了displaced 和xxxDisplaced,那么xxxDisplaced生效

            displaced: Transition {
                SpringAnimation{
                    property: "y"
                    spring: 3
                    damping: 0.1
                    epsilon: 0.25
                }
            }

            remove: Transition {
                SequentialAnimation{
                    NumberAnimation{
                        property: "y"
                        to: 0
                        duration: 200
                    }

                    NumberAnimation{
                        property: "opacity"
                        to:0
                        duration: 200
                    }
                }
            }//remove Transition is end


            function add_zero(temp)
            {

                if(temp<10) return "0"+temp;

                else return temp;

            }

            function loadfile()
            {
                //console.log("加载....");
               //content.setDataPath("C:\\Users\\cms\\Desktop\\xjc\\OMS\\program\\setting\\methodSetting\\");
                content.getFileNames();
                if(content.justFile() === 0)
                    return;
                //console.log(content.getFileCount());
                for(var i = 0; i<content.getFileCount();i++){
                    content.setFileName(content.fileN(i));
                    var name = content.filename;
                    var scanftype = content.dataN(0);
                    var iontype = content.dataN(1)
                    var scanflow = content.dataN(2)
                    var scanfhigh = content.dataN(3);
                    var scanfspeed = content.dataN(4);
//                    console.log(name);
//                    console.log(scanftype);
//                    console.log(iontype);
//                    console.log(scanflow);
//                    console.log(scanfhigh);
//                    console.log(scanfspeed);

                    model.append(
                                {
                                    "name": name,
                                    "scanfType": scanftype,
                                    "ionType" : iontype,
                                    "scanfLow" : scanflow,
                                    "scanfHigh" : scanfhigh,
                                    "scanfSpeed":  scanfspeed
                                }
                                )
                     //listView.currentIndex = 0;
                     content.clearContent();
                }
            }


            function deletefile(index)
            {
                //console.log(index);
                var filename = listView.model.get(index).name;
               // console.log(filename);
                if(content.deleteContent(filename))
                    console.log("删除成功!");
                else
                    console.log("删除失败");
            }

            function addOne()
            {
                var d = new Date;
                var years = d.getFullYear();
                var month = add_zero(d.getMonth()+1);
                var days = add_zero(d.getDate());
                var hours = add_zero(d.getHours());
                var minutes = add_zero(d.getMinutes());
                var seconds=add_zero(d.getSeconds());
                var ndate = month.toString() +days.toString() +hours+minutes+seconds;
                //var ndates = years+"-"+month+"-"+days+"\n "+hours+":"+minutes+":"+seconds;

//                var scanfType = 1;
//                var ionType = 1;
//                var scanfLow = 100;
//                var scanfHigh = 1000;
//                var scanfSpeed = 2000;

                model.insert(0,
                            {
                                "name": "配置" + ndate.toString(),
                                "scanfType": 1,
                                "ionType" : 1,
                                "scanfLow" : 100,
                                "scanfHigh" : 1000,
                                "scanfSpeed":  2000
                            }
                            )
                 listView.currentIndex = 0;
                var data = "1\n1\n100\n1000\n2000\n";
                content.setFileName("配置" + ndate.toString());
                content.writeContent(data);
                content.clearContent();
                //console.log(content.getContent());
            }

            function insertOne()
            {
                model.insert(Math.round(Math.random() * model.count),
                             {
                                 "name" : "HTC One E8"
                             }
                             )
            }

            function settingRef()
            {
                switch(listView.model.get(listView.currentIndex).scanfType)
                {
                case 1:
                    rec1.color = "green";
                    rec2.color = "gray";
                    rec3.color = "gray";
                    break;
                case 2:
                    rec1.color = "gray";
                    rec2.color = "green";
                    rec3.color = "gray";
                    break;
                case 3:
                    rec1.color = "gray";
                    rec2.color = "gray";
                    rec3.color = "green";
                    break;
                }

                switch(listView.model.get(listView.currentIndex).ionType)
                {
                case 1:
                    jixing1.color = "green";
                    jixing2.color = "gray";
                    break;
                case 2:
                    jixing1.color = "gray";
                    jixing2.color = "green";
                    break;
                }

                rangeSlider.first.value = listView.model.get(listView.currentIndex).scanfLow/10;
                //console.log(rangeSlider.first.value);
                rangeSlider.second.value = listView.model.get(listView.currentIndex).scanfHigh/10;
                //console.log(rangeSlider.second.value);
                slider.value = listView.model.get(listView.currentIndex).scanfSpeed;

            }

            function settingSave()
            {
                //保存四项内容
                listView.model.setProperty(listView.currentIndex,"scanfType",setting.st);
                listView.model.setProperty(listView.currentIndex,"ionType",setting.it);
                listView.model.setProperty(listView.currentIndex,"scanfLow",setting.sl);
                listView.model.setProperty(listView.currentIndex,"scanfHigh",setting.sh);
                listView.model.setProperty(listView.currentIndex,"scanfSpeed",setting.ss)

                var data = setting.st + "\n" + setting.it + "\n" + setting.sl + "\n" + setting.sh + "\n" +setting.ss;
                content.setFileName(listView.model.get(listView.currentIndex).name);
                content.writeContent(data);
                //console.log(content.getContent());

            }

            Component.onCompleted: {
                addList.add.connect(listView.addOne)
                //addList.insert.connect(listView.insertOne)
            }
        }
    }

    Rectangle{               //割线
        anchors.left: addList.right;
        anchors.top: addList.top;
        height: parent.height;
        width: 3;
        color: "white";
        z: 5;
    }

    Rectangle {                //设置框
        id: setting;
        anchors.left: addList.right;
        anchors.leftMargin: 3;
        anchors.top: parent.top;
        height: parent.height;
        width: parent.width-addList.width-3;
        color: "lightblue";
        z: 3;
        MouseArea{
            anchors.fill: parent;
            onPressed: parent.focus = true;
        }

        property var st : ((rec1.color == "#008000") ? (1) : ((rec2.color == "#008000") ? 2 : 3));
        property var it : (jixing1.color == "#008000" ? 1 : 2)
        property var sl : Math.floor(rangeSlider.first.value)*10;
        property var sh : Math.floor(rangeSlider.second.value)*10;
        property var ss:  slider.value


        Text {
            id: workmodel
            x: 15
            y: 20
            text: qsTr("工作模式")
            font.pixelSize: 40
            font.bold: true;
        }


        Rectangle{    //全扫描
            id: rec1;
            width: 120;
            height: 60;
            anchors.top: workmodel.bottom;
            anchors.topMargin: 10;
            anchors.left: workmodel.left;
            color:  "green"

            Text {
                text: qsTr("全扫描") ;
                color: "white" ;
                anchors.centerIn: parent;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                font.bold: true;
                font.pixelSize: parent.height*0.5;
            }

            MultiPointTouchArea{
                anchors.fill: parent;
                onReleased: {
                    parent.color = "green";
                    rec2.color = "gray";
                    rec3.color = "gray";
                }
            }
        }

        Rectangle{    //SIM
            id: rec2;
            width: 120;
            height: 60;
            anchors.verticalCenter: rec1.verticalCenter;
            anchors.left: rec1.right;
            property var flage: false;
            color: "gray";

            Text {
                text:qsTr("SIM");
                color: "white";
                anchors.centerIn: parent;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                font.bold: true;
                font.pixelSize: parent.height*0.5;
            }

            MultiPointTouchArea{
                anchors.fill: parent;
                onReleased: {
                    parent.color = "green";
                    rec1.color = "gray";
                    rec3.color = "gray";
                }
            }

        }

        Rectangle{    //MSN
            id: rec3;
            width: 120;
            height: 60;
            anchors.verticalCenter: rec1.verticalCenter;
            anchors.left: rec2.right;
            property var flage: false;
            color:  "gray";

            Text {
                text:qsTr("MSN");
                color: "white";
                anchors.centerIn: parent;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                font.bold: true;
                font.pixelSize: parent.height*0.5;
            }

            MultiPointTouchArea{
                anchors.fill: parent;
                onReleased: {
                    parent.color = "green";
                    rec2.color = "gray";
                    rec1.color = "gray";
                }
            }
        }

        Text {           //离子说明
            id: iontext
            x: 700
            y: 20
            text: qsTr("粒子极性")
            font.bold: true
            font.pixelSize: 40
        }

        Rectangle{    //正离子
            id: jixing1;
            width: 120;
            height: 60;
            anchors.top: iontext.bottom;
            anchors.topMargin: 10;
            anchors.left: iontext.left;
            property var flage: false;
            color: "green" ;

            Text {
                text:qsTr("正离子");
                color: "white";
                anchors.centerIn: parent;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                font.bold: true;
                font.pixelSize: parent.height*0.5;
            }

            MultiPointTouchArea{
                anchors.fill: parent;
                onReleased: {
                    jixing1.color = "green";
                    jixing2.color = "gray";
                }
            }
        }

        Rectangle{    //负离子
            id: jixing2;
            width: 120;
            height: 60;
            anchors.verticalCenter: jixing1.verticalCenter;
            anchors.left: jixing1.right;
            property var flage: false;
            color:  "gray";

            Text {
                text:qsTr("负离子");
                color: "white";
                anchors.centerIn: parent;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
                font.bold: true;
                font.pixelSize: parent.height*0.5;
            }

            MultiPointTouchArea{
                anchors.fill: parent;
                onReleased: {
                    parent.color = "green";
                    jixing1.color = "gray";
                }
            }
        }

        Text {        //质量范围
            id: massfiled
            x: 15
            y: 240
            text: qsTr("质量范围")
            font.bold: true
            font.pixelSize: 40
        }



        Text {        //扫描速度
            id: speed
            x: 15
            y: 400
            text: qsTr("扫描速度")
            font.bold: true
            font.pixelSize: 40
        }

        RangeSlider {          //质量范围
            id: rangeSlider
            x: 200
            y: 138
            width: 750
            height: 80
            clip: true
            font.capitalization: Font.AllUppercase
            wheelEnabled: true
            anchors.verticalCenter: massfiled.verticalCenter
            stepSize: 1
            to: 150
            from: 0
            first.value: 10
            second.value: 100;
        }

        TextField {
            id: lefttext;
            anchors.bottom: rangeSlider.top;
            anchors.left: rangeSlider.left;
            //x: rangeSlider.first.position*rangeSlider.width+rangeSlider.x-width;
            width: 100
            height: 60
            font.pixelSize: 40
            horizontalAlignment: Text.AlignLeft
            text: Math.floor(rangeSlider.first.value)*10;
            background: Rectangle{
                anchors.fill: parent;
                color: "lightblue";
            }
            onPressed:
                vkb.visible = true;
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

        TextField {
            id: righttext;
            anchors.bottom: rangeSlider.top;
            anchors.right: rangeSlider.right;
            //x: rangeSlider.second.position*rangeSlider.width+rangeSlider.x;
            width: 100
            height: 60
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 40;
            text: Math.floor(rangeSlider.second.value)*10;
            background: Rectangle{
                anchors.fill: parent;
                color: "lightblue";
            }
            onPressed:
                vkb.visible = true;
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

        Slider {           //扫描速度
            id: slider
            x: 200
            y: 300
            width: 750
            anchors.verticalCenter: speed.verticalCenter
            anchors.horizontalCenter: rangeSlider.horizontalCenter
            orientation: Qt.Horizontal
            stepSize: 100
            to: 5000
            value: 2000;
        }

        TextField {
            id: slidertext;
            x: slider.position*slider.width+slider.x;
            anchors.bottom: slider.top;
            background: Rectangle{
                anchors.fill: parent;
                color: "lightblue";
            }
            width: 120
            height: 60
            font.pixelSize: 40
            text: slider.value;
            onPressed:
                vkb.visible = true;
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


//        InputPanel {
//                id: vkb
//                visible: false
//                anchors.right: setting.right
//                anchors.left: setting.left
//                anchors.bottom: setting.bottom
//                //这种集成方式下点击隐藏键盘的按钮是没有效果的，
//                //只会改变active，因此我们自己处理一下
//                onActiveChanged: {
//                    if(!active) { visible = false; }
//                }
//            }
    }
}



