#include "lamdadialog.h"
#include "findlambda.h"
#include "ui_lamdadialog.h"
#include "ui_normheatfluxdensity.h"

LamdaDialog::LamdaDialog(double tInside, NormHeatFluxDensity *obj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LamdaDialog)
{
    ui->setupUi(this);
    tInside1=tInside;
    ForLink=obj;

    QRegularExpression rx("[0-9.,]*");
    ui->lineEdit->setValidator(new QRegularExpressionValidator (rx,this));
}

LamdaDialog::~LamdaDialog()
{
    delete ui;
}

void LamdaDialog::on_FindLambdaButton_clicked()
{
    FindLambda* FindLambdaWindow=new FindLambda(tInside1, ForLink);
    FindLambdaWindow->show();
    hide();
}


void LamdaDialog::on_AcceptButton_clicked()
{
    QString acceptedLamda=ui->lineEdit->text();
    acceptedLamda.replace(",", ".");
    ForLink->lambda=acceptedLamda.toDouble();
    ForLink->ui->LambdaAcceptedLabel->setText(acceptedLamda);
    hide();
}


void LamdaDialog::on_BackButton_clicked()
{
    hide();
}

