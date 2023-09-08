#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "normheatfluxdensity.h"
#include <QComboBox>
#include <QLineEdit>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked() //При нажатии на кнопку проверяется выбранный индекс у комбобокса и на основе это отображается следующее окно
{
    switch(ui->comboBox->currentIndex()){
    case 0:
    {
        NormHeatFluxDensity* NormHeatFluxDensityWindow=new NormHeatFluxDensity;
        NormHeatFluxDensityWindow->show();
        hide();
        break;
    }
    case 1:

        break;
    case 2:

        break;
    default:
        break;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return){
        on_pushButton_clicked();
    }
}
