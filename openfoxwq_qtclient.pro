QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets websockets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boardwidget.cpp \
    broadcastroommodel.cpp \
    getinitdatamsg.cpp \
    loginmsg.cpp \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    matchcardwidget.cpp \
    matchtab.cpp \
    modelutils.cpp \
    playermodel.cpp

HEADERS += \
    boardwidget.h \
    broadcastroommodel.h \
    getinitdatamsg.h \
    loginmsg.h \
    loginwindow.h \
    mainwindow.h \
    matchcardwidget.h \
    matchtab.h \
    modelutils.h \
    playermodel.h

FORMS += \
    boardwidget.ui \
    loginwindow.ui \
    mainwindow.ui \
    matchcardwidget.ui \
    matchtab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
