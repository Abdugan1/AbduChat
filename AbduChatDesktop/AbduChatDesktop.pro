QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../
LIBS += -L../AbduChatLib -labduchatlib

INCLUDEPATH += ../AbduChatClient/src
LIBS += -L../AbduChatClient -labduchatclient


HEADERS += \
    src/chatdelegate.h \
    src/chatsview.h \
    src/connectionerrorpage.h \
    src/constants.h \
    src/conversationheader.h \
    src/conversationview.h \
    src/conversationwidget.h \
    src/label.h \
    src/lineedit.h \
    src/loginpage.h \
    src/mainpage.h \
    src/mainwindow.h \
    src/messagedelegate.h \
    src/messagelineedit.h \
    src/pushbutton.h \
    src/sidepanel.h \
    src/slidingstackedwidget.h \
    src/ui_connectionerrorpage.h \
    src/ui_conversationwidget.h \
    src/ui_loginpage.h \
    src/ui_mainpage.h \
    src/ui_sidepanel.h

SOURCES += \
        src/chatdelegate.cpp \
        src/chatsview.cpp \
        src/connectionerrorpage.cpp \
        src/constants.cpp \
        src/conversationheader.cpp \
        src/conversationview.cpp \
        src/conversationwidget.cpp \
        src/label.cpp \
        src/lineedit.cpp \
        src/loginpage.cpp \
        src/main.cpp \
        src/mainpage.cpp \
        src/mainwindow.cpp \
        src/messagedelegate.cpp \
        src/messagelineedit.cpp \
        src/pushbutton.cpp \
        src/sidepanel.cpp \
        src/slidingstackedwidget.cpp \
        src/ui_connectionerrorpage.cpp \
        src/ui_conversationwidget.cpp \
        src/ui_loginpage.cpp \
        src/ui_mainpage.cpp \
        src/ui_sidepanel.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    resources/fonts.qrc \
    resources/images.qrc \
    resources/qss.qrc
