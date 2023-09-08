#include "normheatfluxdensity.h"
#include "ui_normheatfluxdensity.h"
#include "Functions.h"
#include "SourceData.h"
#include "lamdadialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QKeyEvent>



NormHeatFluxDensity::NormHeatFluxDensity(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NormHeatFluxDensity)
{
    ui->setupUi(this);
    QRegularExpression rx("[0-9.,]*");
    QRegularExpression rxwithminus("[0-9.,-]*");

    ui->tInsideLineEdit->setValidator(new QRegularExpressionValidator (rxwithminus,this));
    ui->tOutsideLineEdit->setValidator(new QRegularExpressionValidator (rxwithminus,this));
    ui->DNLineEdit->setValidator(new QRegularExpressionValidator (rx,this));
    ui->DPipeSurfaceLineEdit->setValidator(new QRegularExpressionValidator (rx,this));
}

NormHeatFluxDensity::~NormHeatFluxDensity()
{
    delete ui;
}

// Не готово
//void NormHeatFluxDensity::on_pushButton_clicked()
//{
//    double lambda = ui->LambdaLineEdit->text().toDouble();
//    double tOutside = ui->tOutsideLineEdit->text().toDouble();
//    double tInside = ui->tInsideLineEdit->text().toDouble();
//    QString CalculRes = QString::number(DIzulN1ForSurface(lambda, tOutside, tInside, KCoefficient, , ));
//    ui->CalculatedDIz->setText(CalculRes);
//}


void NormHeatFluxDensity::on_LambdaButton_clicked()
{
    tInside=ui->tInsideLineEdit->text().toDouble();
    // if бесканальная прокладка, то берем коэффициент еще
    LamdaDialog* LamdaDialogWindow=new LamdaDialog(tInside, this);
    LamdaDialogWindow->show();
}



void NormHeatFluxDensity::on_CountButton_clicked()//Основная функция
{

    if(!ui->DNLineEdit->text().isEmpty() && !ui->DPipeSurfaceLineEdit->text().isEmpty() && !ui->tInsideLineEdit->text().isEmpty() && !ui->tOutsideLineEdit->text().isEmpty() && lambda!=0){
    // !!!!!!!!! Не реализовано для плоских поверхностей !!!!!!!!!!

    double DN; //DN
    double DSurfacePipe; //Наружний диаметр
    double tOutside;//Температура окружающего воздуха
    double tAverage;//Средняя температура ти
    double K1;//Коэффициент дополнительных потерь
    double K2;//Коэффициент района строительства
    double K3;//Коэффициент увлажнения
    double B;//Величина В
    double R;//Коэффициент Rн
    double q;//Плотность теплового потока
    double deltaIz;//Расчетная толщина изоляции
    int deltaIzAccepted;//Принятая толщина изоляции
    double tAv; //Подсчет средней температуры


    /*Замена запятой на точку для корректной работы--------------------*/
    QString DNWithComma=ui->DNLineEdit->text();
    QString DPipeSurfacePipeWithComma=ui->DPipeSurfaceLineEdit->text();
    QString tInsideWithComma=ui->tInsideLineEdit->text();
    QString tOutsideWithComma=ui->tOutsideLineEdit->text();


    DNWithComma.replace("," , ".");
    DPipeSurfacePipeWithComma.replace("," , ".");
    tInsideWithComma.replace("," , ".");
    tOutsideWithComma.replace("," , ".");
    /*-----------------------------------------------------------------*/


    DN=DNWithComma.toDouble();
    DSurfacePipe=DPipeSurfacePipeWithComma.toDouble();
    tInside=tInsideWithComma.toDouble();
    tOutside=tOutsideWithComma.toDouble();
    K1=K1Take(ui->PillarBox->currentIndex(),DN);
    K2=K2Take(ui->DistrictBox->currentIndex(),ui->LocationBox->currentIndex());
    K3=K3Take(ui->MaterialBox->currentIndex(),ui->WetBox->currentIndex());

    ui->CoefK1Label->setText(QString::number(K1));
    ui->CoefK2Label->setText(QString::number(K2));
    ui->CoefK3Label->setText(QString::number(K3));

    /*Подсчет средней температуры----------------------------------*/
    if (ui->SeasonBox->currentIndex()==0){
        //В зимнее время
        tAv=(tInside+40)/2;
        ui->tAverageLabel->setText(QString::number(tAv));
    }
    else {
        //В летнее время
        tAv=tInside/2;
        ui->tAverageLabel->setText(QString::number(tAv));
    }
    /*------------------------------------------------------------------*/


    /*  Поиск R---------------------------------------------------------*/
    if (ui->LocationBox->currentIndex()==0){
        R=GetR(ROutside,DN,tInside);
        QString doubleText=QString::number(R,'f',2);
        ui->CoefRLabel->setText(doubleText);
    }

    if (ui->LocationBox->currentIndex()==1&&ui->EmissionBox->currentIndex()==0){
        R=GetR(RInsideLowCoef,DN,tInside);
        QString doubleText=QString::number(R,'f',2);
        ui->CoefRLabel->setText(doubleText);
    }

    if (ui->LocationBox->currentIndex()==1&&ui->EmissionBox->currentIndex()==1){
        R=GetR(RInsideHighCoef,DN,tInside);
        QString doubleText=QString::number(R,'f',2);
        ui->CoefRLabel->setText(doubleText);
    }
    /*----------------------------------------------------------------------*/



    /*----------------Ищем тепловой поток q-------------------------*/
    //Условия для отбора q из таблицы 2
    if (ui->LocationBox->currentIndex()==0&&ui->HoursBox->currentIndex()==0&&tInside>0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table2Sp,DN,tInside,LocBox);

           // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else{
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table2Sp,1500,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }

    }

    //Условия для отбора q из таблицы 3
    if (ui->LocationBox->currentIndex()==0&&ui->HoursBox->currentIndex()==1&&tInside>0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table3Sp,DN,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else{
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table3Sp,1500,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }

    }


    //Условия для отбора q из таблицы 4
    if (ui->LocationBox->currentIndex()==1&&ui->HoursBox->currentIndex()==0&&tInside>0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table4Sp,DN,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else {
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table4Sp,1500,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }

    }

    //Условия для отбора q из таблицы 5
    if (ui->LocationBox->currentIndex()==1&&ui->HoursBox->currentIndex()==1&&tInside>0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table5Sp,DN,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else{
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesPosTemp(Table5Sp,1500,tInside,LocBox);

            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }

    }

    //Условия для отбора q из таблицы 6
    if (ui->LocationBox->currentIndex()==0&&tInside<=0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesNegTemp(Table6Sp,DN,tInside,LocBox);
            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else{
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesNegTemp(Table6Sp,600,tInside,LocBox);
            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }

    }


    if (ui->LocationBox->currentIndex()==1&&tInside<=0 && ui->qManualLineEdit->text().isEmpty()){
        if (ui->PipeOrSurfaceBox->currentIndex()==0){
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesNegTemp(Table7Sp,DN,tInside,LocBox);
            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
        else{
            int LocBox=ui->LocationBox->currentIndex();
            q=LinearInterpolationForPipesNegTemp(Table7Sp,600,tInside,LocBox);
            // ui->CoefQLabel->setText(QString::number(q),);
            QString doubleText=QString::number(q,'f',2);
            ui->CoefQLabel->setText(doubleText);
        }
    }

    if (!ui->qManualLineEdit->text().isEmpty()){

        q=ui->qManualLineEdit->text().toDouble();

    }

    /*-----------------------------------------------------------------*/

    B=BForPipelinesFormula(lambda, tOutside, tInside, K1, q, R);
    ui->CoefBLabel->setText(QString::number(B,'f',2));


    deltaIz=DIzulN1ForPipelines(B, DSurfacePipe);
    ui->CalculatedDIz->setText(QString::number(deltaIz,'f',2));

    deltaIzAccepted=acceptedDiz(deltaIz);
    ui->DIzAcceptedLineEdit->setText(QString::number(deltaIzAccepted));

    }
    else{
    QMessageBox::warning(this, "Ошибка","Заполните все поля и введите лямбду");
    }

}



void NormHeatFluxDensity::on_BackButton_clicked(){
    MainWindow* MainWindowWindow=new MainWindow();
    MainWindowWindow->show();
    hide();
}


void NormHeatFluxDensity::keyPressEvent(QKeyEvent *e){
    if (e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return){
    on_CountButton_clicked();
    }
}


