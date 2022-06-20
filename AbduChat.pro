TEMPLATE = subdirs

SUBDIRS += \
    AbduChatLib \
    AbduChatServer

AbduChatClient.subdirs = AbduChatClient/
AbduChatLib.subdirs = AbduChatLib/
AbduChatServer.subdirs = AbduChatServer/

AbduChatClient.depends = AbduChatLib
AbduChatServer.depends = AbduChatLib
