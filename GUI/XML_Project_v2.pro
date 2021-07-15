QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    XML_Compression.cpp \
    XML_JSON.cpp \
    XML_Minify.cpp \
    XML_Parser.cpp \
    XML_Pretify.cpp \
    fixdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    XML_Compression.h \
    XML_JSON.h \
    XML_Minify.h \
    XML_Parser.h \
    XML_Pretify.h \
    fixdialog.h \
    main.h \
    mainwindow.h

FORMS += \
    fixdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
