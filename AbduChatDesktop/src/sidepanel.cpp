#include "sidepanel.h"
#include "ui_sidepanel.h"

SidePanel::SidePanel(QWidget *parent)
    : QWidget(parent)
    , ui_(new UiSidePanel)
{
    ui_->setupUi(this);
}
