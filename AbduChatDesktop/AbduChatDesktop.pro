QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/chatlistdockwidget.h \
    src/constants.h \
    src/label.h \
    src/lineedit.h \
    src/loginpage.h \
    src/mainpage.h \
    src/mainwindow.h \
    src/pushbutton.h \
    src/ui_chatlistdockwidget.h \
    src/ui_loginpage.h \
    src/ui_mainpage.h

SOURCES += \
        src/chatlistdockwidget.cpp \
        src/constants.cpp \
        src/label.cpp \
        src/lineedit.cpp \
        src/loginpage.cpp \
        src/main.cpp \
        src/mainpage.cpp \
        src/mainwindow.cpp \
        src/pushbutton.cpp \
        src/ui_chatlistdockwidget.cpp \
        src/ui_loginpage.cpp \
        src/ui_mainpage.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    resources/fonts.qrc \
    resources/images.qrc \
    resources/qss.qrc
