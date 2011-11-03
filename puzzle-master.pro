#-------------------------------------------------
#
# Project created by QtCreator 2010-12-01T19:24:52
#
#-------------------------------------------------

QT += core gui declarative

TARGET = puzzle-master
TEMPLATE = app

VERSION = 2.0
DEFINES += HAVE_OPENGL

SOURCES += \
    main.cpp\
    puzzleitem.cpp \
    puzzleboard.cpp \
    jigsawpuzzleitem.cpp \
    jigsawpuzzleboard.cpp
#    mainwindow.cpp \
#    settingsdialog.cpp \
#    imagechooser.cpp \
#    highscoresdialog.cpp \
#    newgamedialog.cpp

HEADERS += \
    util.h \
    puzzleitem.h \
    puzzleboard.h \
    jigsawpuzzleitem.h \
    jigsawpuzzleboard.h
#    mainwindow.h \
#    newgamedialog.h \
#    settingsdialog.h \
#    imagechooser.h \
#    highscoresdialog.h

#FORMS += \
#    mainwindow.ui \
#    settingsdialog.ui \
#    imagechooser.ui \
#    highscoresdialog.ui \
#    newgamedialog.ui

RESOURCES += \
    resources.qrc \
    meegoGui.qrc

TRANSLATIONS += \
    translations/puzzle-master_hu_HU.ts

OTHER_FILES += \
    data/about.txt \
    qml/meego/AppWindow.qml \
    qml/meego/NewGamePage.qml \
    qml/meego/GamePage.qml

unix {
    INSTALLS += target iconfile desktopfile
    OTHER_FILES += data/puzzle-master.desktop

    target.path = /usr/bin
    iconfile.path = /usr/share/pixmaps
    iconfile.files = data/puzzle-master.png
    desktopfile.path = /usr/share/applications
    desktopfile.files = data/puzzle-master.desktop
}
maemo5 {
    # Maemo 5 Fremantle
    
    QT += maemo5
    DEFINES += MOBILE HAVE_QACCELEROMETER

    CONFIG += mobility
    MOBILITY += sensors

    target.path = /opt/puzzle-master
    desktopfile.path = /usr/share/applications/hildon
}
symbian {
    # Symbian
    QT -= opengl
    DEFINES += MOBILE HAVE_QACCELEROMETER
    DEFINES -= HAVE_OPENGL

    CONFIG += mobility
    MOBILITY += sensors

    ICON = data/puzzle-master-44x44.svg

    LIBS += -lcommondialogs -lplatformenv -leikcoctl -lavkon -lcone -leikcore

    TARGET.UID3 = 0xe5b4435f
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x28000
    # Max. heap size is 20 MiB
    TARGET.EPOCHEAPSIZE = 0x020000 0x20971520
}
win32 {
    # Windows desktop
    RC_FILE = puzzle-master.rc
    OTHER_FILES += puzzle-master.rc
}

