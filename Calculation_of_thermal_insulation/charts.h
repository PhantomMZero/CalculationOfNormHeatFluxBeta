#ifndef CHARTS_H
#define CHARTS_H

#include <QWidget>
#include <QString>
#include <QtCharts>
#include "exponentialfitting.h"
#include "linearregression.h"

namespace Ui {
class Charts;
}

class Charts : public QWidget
{
    Q_OBJECT

public:
    explicit Charts(std::map<double, double> DataForCharts, double tInside, double predictedLambda, QString Formula, int TypeOfCalc, QWidget *parent = nullptr);
    ~Charts();

private:
    Ui::Charts *ui;
};

#endif // CHARTS_H
