#ifndef FINDLAMBDA_H
#define FINDLAMBDA_H

#include "lamdadialog.h"
#include "linearregression.h"
#include "charts.h"
#include "exponentialfitting.h"
#include "normheatfluxdensity.h"
#include <QDebug>
#include <QWidget>

namespace Ui {
class FindLambda;
}

class FindLambda : public QWidget
{
    Q_OBJECT

public:
    NormHeatFluxDensity *ForLink;
    explicit FindLambda(double tInside1, NormHeatFluxDensity *NormHeatFluxDensityObj, QWidget *parent = nullptr);
    ~FindLambda();

private slots:
    void on_AddRowButton_clicked();

    void on_DeleteRowButton_clicked();

    void on_CalculateButton_clicked();

    void on_ChartButton_clicked();

    void on_BackButton_clicked();

    void on_AcceptButton_clicked();

private:
    double predictedLambda;
    QString Formula;
    double tInside;
    std::map<double,double> TableData;
    Ui::FindLambda *ui;
};

#endif // FINDLAMBDA_H
