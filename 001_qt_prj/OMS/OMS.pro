#-------------------------------------------------
#
# Project created by QtCreator 2018-04-25T11:22:18
#
#-------------------------------------------------

QT       += core gui widgets quickwidgets serialport script
QT += qml sql
RC_ICONS = company.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OMS
TEMPLATE = app

CONFIG  += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    tool/sthread.cpp \
    cParamCCS.cpp \
    cPumpControl.cpp \
    cPublicCCS.cpp \
    sMainWindow.cpp \
    sSystem.cpp \
    sMethod.cpp \
    sSystem/sAutoTuning.cpp \
    sSystem/sManualTuning.cpp \
    sDataAcquisiton.cpp \
    sDataAnalysis.cpp \
    sChartWidget.cpp \
    LibWidget/sMyButton.cpp \
    LibWidget/sInputdialog.cpp \
    sTvplot.cpp \
    sCommandUSB.cpp \
    sCommandUSB/cMidWareUSB.cpp \
    sCommandUSB/cCommunicationCMD.cpp \
    LibProcessing/Processing/Centroid.cpp \
    LibProcessing/Processing/CFWHM.cpp \
    LibProcessing/Maths/cMathLCTR.cpp \
    LibProcessing/Maths/MatrixNumeric.cpp \
    LibProcessing/Maths/sgfilter.cpp \
    LibProcessing/MiscUtilities/RegistryHandler.cpp \
    Algorithm/FrameAverage.cpp \
    LibProcessing/Processing/CNoiseSplineBaseline.cpp \
    LibProcessing/Processing/CSignalArea.cpp \
    LibProcessing/Processing/CSmoothingFilter.cpp \
    cDataProcess.cpp \
    LibWidget/sFileDir.cpp \
    LibWidget/sFileWidget.cpp \
    sSystemState.cpp \
    MassAxisAdjust.cpp \
    cLoadDataFile.cpp \
    FileListWidget.cpp \
    AllScan.cpp \
    SIM.cpp \
    DoubleSlider.cpp \
    Login.cpp \
    keyBoard/MyKeyBoard.cpp \
    frmnum.cpp \
    HighPre.cpp \
    Temperature.cpp \
    QSwitchButton.cpp \
    massinput.cpp \
    SaveFile.cpp \
    sChartChildren/sChartXIC.cpp \
    sChartChildren/sManagerXIC.cpp \
    sSystem/MyControl.cpp \
    sSystem/sWidgetCalibration.cpp \
    sSystem/sWidgetTargetChart.cpp \
    msMethed/cMethod.cpp \
    LibProcessing/Maths/PolyFit.cpp \
    sSystem/ControlDemo.cpp \
    mylineedit.cpp \
    OneSlider.cpp \
    LibWidget/ListWidget/ListItem.cpp \
    LibWidget/ListWidget/sTICList.cpp \
    LibWidget/ListWidget/ColorSelectTool.cpp \
    myGroupBox.cpp \
    sControlSSC.cpp \
    sPwmCCS.cpp \
    tool/SerialPort.cpp \
    tool/Algorithm.cpp

HEADERS  += \
    tool/ssafedata.h \
    tool/sthread.h \
    share/sdata.h \
    cParamCCS.h \
    cPumpControl.h \
    cPublicCCS.h \
    sMainWindow.h \
    sSystem.h \
    sMethod.h \
    sSystem/sAutoTuning.h \
    sSystem/sManualTuning.h \
    sDataAcquisiton.h \
    sDataAnalysis.h \
    sChartWidget.h \
    LibWidget/sMyButton.h \
    LibWidget/sInputdialog.h \
    sTvplot.h \
    sCommandUSB.h \
    sCommandUSB/cMidWareUSB.h \
    sCommandUSB/cCommunicationCMD.h \
    LibProcessing/cProcessing.h \
    LibProcessing/Processing/Centroid.h \
    LibProcessing/Processing/CFWHM.h \
    LibProcessing/Maths/cMathLCTR.h \
    LibProcessing/Maths/MatrixNumeric.h \
    LibProcessing/Maths/sgfilter.h \
    LibProcessing/Maths/structLCTR.h \
    LibProcessing/MiscUtilities/RegistryHandler.h \
    Algorithm/FrameAverage.h \
    LibProcessing/Processing/CNoiseSplineBaseline.h \
    LibProcessing/Processing/CSignalArea.h \
    LibProcessing/Processing/CSmoothingFilter.h \
    cDataProcess.h \
    LibWidget/sFileDir.h \
    LibWidget/sFileWidget.h \
    sSystemState.h \
    frmnum.h \
    MassAxisAdjust.h \
    cLoadDataFile.h \
    FileListWidget.h \
    AllScan.h \
    SIM.h \
    DoubleSlider.h \
    enum.h \
    Login.h \
    keyBoard/MyKeyBoard.h \
    HighPre.h \
    Temperature.h \
    QSwitchButton.h \
    massinput.h \
    SaveFile.h \
    sSystem/MyControl.h \
    cconfigoms.h \
    sChartChildren/sChartXIC.h \
    sChartChildren/sManagerXIC.h \
    sSystem/sWidgetCalibration.h \
    sSystem/sWidgetTargetChart.h \
    msMethed/cMethod.h \
    msMethed/mathMethod.h \
    msMethed/MsParams.h \
    LibProcessing/Maths/PolyFit.h \
    sSystem/ControlDemo.h \
    myLineEdit.h \
    OneSlider.h \
    LibWidget/ListWidget/ListItem.h \
    LibWidget/ListWidget/sTICList.h \
    LibProcessing/Maths/zxMath.h \
    LibWidget/ListWidget/ColorSelectTool.h \
    myGroupBox.h \
    sControlSSC.h \
    sPwmCCS.h \
    tool/SerialPort.h \
    tool/Algorithm.h

FORMS    += \
    sMainWindow.ui \
    sSystem.ui \
    sMethod.ui \
    sSystem/sAutoTuning.ui \
    sSystem/sManualTuning.ui \
    sDataAcquisiton.ui \
    sDataAnalysis.ui \
    LibWidget/sFileDir.ui \
    LibWidget/sFileWidget.ui \
    sSystemState.ui \
    frmnum.ui \
    MassAxisAdjust.ui \
    AllScan.ui \
    SIM.ui \
    Login.ui \
    keyBoard/MyKeyBoard.ui \
    HighPre.ui \
    Temperature.ui \
    massinput.ui \
    SaveFile.ui \
    sSystem/MyControl.ui \
    sChartChildren/sChartXIC.ui \
    sChartChildren/sManagerXIC.ui \
    sSystem/sWidgetCalibration.ui \
    sSystem/sWidgetTargetChart.ui \
    sSystem/ControlDemo.ui \
    LibWidget/ListWidget/ListItem.ui \
    LibWidget/ListWidget/sTICList.ui \
    sControlSSC.ui

INCLUDEPATH += $$PWD/LibProcessing

win32 {
LIBS += -L$$PWD/libusb/ -llibusb-1.0
INCLUDEPATH += $$PWD/libusb
DEPENDPATH += $$PWD/libusb
}

win32:include ( C:/Qwt-6.1.1-svn/features/qwt.prf )
unix:INCLUDEPATH += /usr/local/qwt-6.1.2/include
unix:LIBS += -L/usr/local/qwt-6.1.2/lib -lqwt
win32:include($$PWD\gsl\gsl.pri)

DISTFILES += \
    msMethed/PTMSCONFIG.ini \
    gsl/gsl.pri

RESOURCES += \
    qml.qrc \
    pixmap.qrc \
    icons.qrc \
    LibWidget/ListWidget/resource.qrc
