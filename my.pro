#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T19:02:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    maincall.cpp \
    EngineAPI.cpp \
    EngineBeh.cpp \
    InputEvent.cpp \
    gesture.cpp \
    animation.cpp \
    basics.cpp \
    reimplemen.cpp

HEADERS  += widget.h \
    head.h \
    maincall.h \
    library.h \
    macro.h \
    configure.h \
    gesture.h \
    basics.h \
    globalVar.h \
    reimplemen.h \
    animation.h \
    help.h \
    game.h \
    map.h

FORMS    += widget.ui
QT += core gui

OTHER_FILES +=

QT += multimedia multimediawidgets
INSTALLS += target
QT += script
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    img.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
