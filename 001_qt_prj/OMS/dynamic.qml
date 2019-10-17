import QtQuick 2.6

Rectangle {
     id: page
     width: 200; height: 40
     color: "lightgray"

     Text {
         id: helloText
         text: "Hello world!"
         y: 30
         //anchors.horizontalCenter: page.horizontalCenter
         //font.pointSize: 24; font.bold: true
     }
 }
