TEMPLATE = subdirs

SUBDIRS += \
    AbduChatClient \
    AbduChatDesktop \
    AbduChatLib \
    AbduChatMobile \
    AbduChatServer

AbduChatClient.subdirs  = AbduChatClient/
AbduChatLib.subdirs     = AbduChatLib/
AbduChatServer.subdirs  = AbduChatServer/
AbduChatMobile.subdirs  = AbduChatMobile/
AbduChatDesktop.subdirs = AbduChatDesktop/

AbduChatClient.depends = AbduChatLib
AbduChatServer.depends = AbduChatLib

AbduChatMobile.depends = AbduChatClient
AbduChatMobile.depends = AbduChatLib

AbduChatDesktop.depends = AbduChatClient
AbduChatDesktop.depends = AbduChatLib
