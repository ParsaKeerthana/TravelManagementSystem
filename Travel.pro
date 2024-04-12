QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QT += core gui sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    addpackage.cpp \
    findpackage.cpp \
    findtourist.cpp \
    registertourist.cpp

HEADERS += \
    databasemanager.h \
    mainwindow.h \
    databaseheader.h \
    addpackage.h \
    findpackage.h \
    findtourist.h \
    registertourist.h

FORMS += \
    mainwindow.ui \
    addpackage.ui \
    findpackage.ui \
    findtourist.ui \
    registertourist.ui

TRANSLATIONS += \
    Travel_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
