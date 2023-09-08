#include "checkheat.h"
#include "ui_checkheat.h"

CheckHeat::CheckHeat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckHeat)
{
    ui->setupUi(this);
}

CheckHeat::~CheckHeat()
{
    delete ui;
}
