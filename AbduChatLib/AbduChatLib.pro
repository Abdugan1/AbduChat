QT -= gui
QT += sql
TEMPLATE = lib
TARGET = abduchatlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    contactstable.cpp \
    database_names.cpp \
    message.cpp \
    messagestableclient.cpp \
    messagestableserver.cpp \
    request_and_reply_constants.cpp \
    serverlogstable.cpp \
    sqldatabase.cpp \
    user.cpp \
    userstable.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    chat.h \
    connect_to_database.h \
    contactstable.h \
    database_names.h \
    datastream.h \
    message.h \
    messagestableclient.h \
    messagestableserver.h \
    request_and_reply_constants.h \
    serverlogstable.h \
    sqldatabase.h \
    user.h \
    userstable.h
