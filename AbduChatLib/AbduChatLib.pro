QT -= gui
QT += sql
TEMPLATE = lib
TARGET = abduchatlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    chatstable.cpp \
    chatsviewtable.cpp \
    database_names.cpp \
    message.cpp \
    messagestable.cpp \
    request_and_reply_constants.cpp \
    serverlogstable.cpp \
    sqldatabase.cpp \
    sqldatabaseclient.cpp \
    sqldatabaseserver.cpp \
    sqltablemodel.cpp \
    user.cpp \
    usersservertable.cpp \
    userstable.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    chat.h \
    chatstable.h \
    chatsviewtable.h \
    database_names.h \
    datastream.h \
    message.h \
    messagestable.h \
    request_and_reply_constants.h \
    serverlogstable.h \
    sqldatabase.h \
    sqldatabaseclient.h \
    sqldatabaseserver.h \
    sqltablemodel.h \
    user.h \
    usersservertable.h \
    userstable.h
