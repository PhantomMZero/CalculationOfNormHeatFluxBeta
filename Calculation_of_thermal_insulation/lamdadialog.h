#ifndef LAMDADIALOG_H
#define LAMDADIALOG_H

#include "normheatfluxdensity.h"
#include <QWidget>

namespace Ui {
class LamdaDialog;
}

class LamdaDialog : public QWidget
{
    Q_OBJECT

public:
    NormHeatFluxDensity *ForLink;
    explicit LamdaDialog(double tInside, NormHeatFluxDensity *obj, QWidget *parent = nullptr);
    ~LamdaDialog();

private slots:
    void on_FindLambdaButton_clicked();

    void on_AcceptButton_clicked();

    void on_BackButton_clicked();

private:
    double tInside1;
    Ui::LamdaDialog *ui;
};

#endif // LAMDADIALOG_H
