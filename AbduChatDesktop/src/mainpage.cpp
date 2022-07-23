#include "mainpage.h"
#include "ui_mainpage.h"
#include "chatdelegate.h"

#include <AbduChatLib/sqldatabaseclient.h>
#include <AbduChatLib/chatsviewtable.h>

#include <QListView>
#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QSplitter(parent)
    , ui_(new UiMainPage)
{
    ui_->setupUi(this);
}
