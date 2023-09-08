#include "findlambda.h"
#include "ui_findlambda.h"
#include "ui_normheatfluxdensity.h"
#include <QString>




FindLambda::FindLambda(double tInside1, NormHeatFluxDensity *NormHeatFluxDensityObj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindLambda)
{
    tInside=tInside1;
    ForLink=NormHeatFluxDensityObj;
    ui->setupUi(this);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"Введите °C", "Введите λ"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0,new QTableWidgetItem(""));
    ui->tableWidget->setItem(0, 1,new QTableWidgetItem(""));
    ui->tableWidget->setItem(0, 2,new QTableWidgetItem(""));

}

FindLambda::~FindLambda()
{
    delete ui;
}

void FindLambda::on_AddRowButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}


void FindLambda::on_DeleteRowButton_clicked()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            if (!ui->tableWidget->item(row, col)) { // Check if the cell is empty
                QTableWidgetItem *emptyItem = new QTableWidgetItem(' ');
                ui->tableWidget->setItem(row, col, emptyItem);
            }
        }
    }

    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    QList<int> rowsToRemove;
    // Iterate over the selected items and remove the rows they belong to
    for(QTableWidgetItem* item : selectedItems) {
        int row = item->row();
        if (!rowsToRemove.contains(row)) {
            rowsToRemove.append(row);
        }
    }


    std::sort(rowsToRemove.begin(), rowsToRemove.end(), std::greater<int>());

    for (int row : rowsToRemove) {
        ui->tableWidget->removeRow(row);
    }
}


void FindLambda::on_CalculateButton_clicked()
{


    if (ui->TypeOfCalculation->currentIndex()==0){
        if (!TableData.empty()){
            for (auto it=TableData.begin();it!=TableData.end();it++){
                TableData.erase(it);
            }
        }
        //Была ошибка в UI соответственно в ui findlambda слева температура, справа ламбда
        //В DataCharts first это лямбда, second это температура
        for (int row=0; row < ui->tableWidget->rowCount(); row++){
            TableData.insert(std::make_pair(ui->tableWidget->item(row, 1)->text().replace("," , ".").toDouble(),ui->tableWidget->item(row, 0)->text().replace("," , ".").toDouble()));
        }
        ExponentialFitting EFit;
        predictedLambda=EFit.predict(TableData,tInside);
        ui->LambdaLabel->setText(QString::number(predictedLambda,'f',2));
        Formula=EFit.PrintBestFittingLine();

    }

    if (ui->TypeOfCalculation->currentIndex()==1){
        if (!TableData.empty()){
            for (auto it=TableData.begin();it!=TableData.end();it++){
                TableData.erase(it);
            }
        }

        for (int row=0; row < ui->tableWidget->rowCount(); row++){
            TableData.insert(std::make_pair(ui->tableWidget->item(row, 0)->text().replace("," , ".").toDouble(),ui->tableWidget->item(row, 1)->text().replace("," , ".").toDouble()));
        }
        LinearRegression lFit;
        lFit.takeInput(TableData);
        predictedLambda=lFit.predict(tInside);
        ui->LambdaLabel->setText(QString::number(predictedLambda,'f',2));
        qDebug()<<lFit.errorSquare();
        Formula=lFit.PrintBestFittingLine();
    }

}


void FindLambda::on_ChartButton_clicked()
{
    on_CalculateButton_clicked();
    Charts* ChartsWindow=new Charts(TableData, tInside, predictedLambda, Formula, ui->TypeOfCalculation->currentIndex());
    ChartsWindow->show();

}


void FindLambda::on_BackButton_clicked()
{
    LamdaDialog* LambdaDialogWindow=new LamdaDialog(tInside,ForLink);
    LambdaDialogWindow->show();
    hide();
}


void FindLambda::on_AcceptButton_clicked()
{
    ForLink->lambda=predictedLambda;
    ForLink->ui->LambdaAcceptedLabel->setText(QString::number(predictedLambda));
    hide();
}

