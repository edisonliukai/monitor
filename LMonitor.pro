#-------------------------------------------------
#
# Project created by QtCreator 2020-08-20T12:29:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMonitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        LMonitor.cpp \
    LTopStatusBarWidget.cpp \
    LBottomMenuBarWidget.cpp \
    LContentAreaWidget.cpp \
    LMenuButtonWidget.cpp \
    LCchdWidget.cpp \
    LConfirmDialog.cpp \
    LDrawCompressedWavefrom.cpp \
    LValueText.cpp \
    spo2.cpp \
    LAppWidget.cpp \
    CustomControl/LSignalColumn/LSignalColumn.cpp \
    CustomControl/LRingIndicator/LRingIndicator.cpp \
    CustomControl/LRingChart/LRingChart.cpp \
    CustomControl/LSmoothWaveform/LSmoothWaveform.cpp \
    CustomControl/LBattery/LBattery.cpp \
    CustomControl/LThermometer/LThermometer.cpp \
    CustomControl/LBarChart/LBarChart.cpp \
    LStartAnimation.cpp \
    LMonitorApp.cpp \
    LWaveClickedDialogBase.cpp \
    LAppConfig.cpp \
    LAppForMvc.cpp


HEADERS += \
        LMonitor.h \
    LTopStatusBarWidget.h \
    LBottomMenuBarWidget.h \
    LContentAreaWidget.h \
    LMenuButtonWidget.h \
    LAppCommom.h \
    LCchdWidget.h \
    LConfirmDialog.h \
    LDrawCompressedWavefrom.h \
    LValueText.h \
    spo2.h \
    LAppWidget.h \
    CustomControl/LSignalColumn/LSignalColumn.h \
    CustomControl/LRingIndicator/LRingIndicator.h \
    CustomControl/LRingChart/LRingChart.h \
    CustomControl/LSmoothWaveform/LSmoothWaveform.h \
    CustomControl/LBattery/LBattery.h \
    CustomControl/LThermometer/LThermometer.h \
    CustomControl/LBarChart/LBarChart.h \
    LStartAnimation.h \
    LMonitorApp.h \
    LWaveClickedDialogBase.h \
    LAppConfig.h \
    LAppForMvc.h

FORMS += \
        LMonitor.ui \
    LMenuButtonWidget.ui \
    LCchdWidget.ui \
    LConfirmDialog.ui \
    LDrawCompressedWavefrom.ui \
    LStartAnimation.ui \
    LMonitorApp.ui \
    LWaveClickedDialogBase.ui

SUBDIRS += \

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    LMonitorQss.qss \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
