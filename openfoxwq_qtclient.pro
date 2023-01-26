QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets websockets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardbutton.cpp \
    boardtestwindow.cpp \
    boardwidget.cpp \
    broadcastroommodel.cpp \
    enterroommsg.cpp \
    getinitdatamsg.cpp \
    leaveroommsg.cpp \
    loginmsg.cpp \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    matchcardwidget.cpp \
    matchtab.cpp \
    modelutils.cpp \
    playermodel.cpp \
    proto/broadcast.pb.cc \
    proto/common.pb.cc \
    proto/fox.pb.cc \
    proto/nav.pb.cc \
    proto/play.pb.cc \
    proto/reqOption.pb.cc \
    rank.cpp \
    stringutils.cpp \
    timecontrolwidget.cpp

HEADERS += \
    boardbutton.h \
    boardtestwindow.h \
    boardwidget.h \
    broadcastroommodel.h \
    enterroommsg.h \
    getinitdatamsg.h \
    leaveroommsg.h \
    loginmsg.h \
    loginwindow.h \
    mainwindow.h \
    matchcardwidget.h \
    matchtab.h \
    modelutils.h \
    playermodel.h \
    proto/broadcast.pb.h \
    proto/common.pb.h \
    proto/fox.pb.h \
    proto/nav.pb.h \
    proto/play.pb.h \
    proto/reqOption.pb.h \
    rank.h \
    stringutils.h \
    timecontrolwidget.h

FORMS += \
    boardtestwindow.ui \
    boardwidget.ui \
    loginwindow.ui \
    mainwindow.ui \
    matchcardwidget.ui \
    matchtab.ui \
    timecontrolwidget.ui

# How to find this in all systems?
INCLUDEPATH += /usr/local/include
LIBS += /usr/local/lib/libprotobuf.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
