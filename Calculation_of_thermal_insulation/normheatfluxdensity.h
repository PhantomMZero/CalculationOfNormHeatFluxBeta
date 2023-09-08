#ifndef NORMHEATFLUXDENSITY_H
#define NORMHEATFLUXDENSITY_H

#include <QMainWindow>



namespace Ui {
class NormHeatFluxDensity;
}

class NormHeatFluxDensity : public QMainWindow
{
    Q_OBJECT


public:
    double tInside=0; //Температура среды
    double lambda=0; //Лямбда из FindLambda и Lamdadialog
    explicit NormHeatFluxDensity(QWidget *parent = nullptr);
    ~NormHeatFluxDensity();
    Ui::NormHeatFluxDensity *ui;
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:


    void on_LambdaButton_clicked();

    void on_CountButton_clicked();

    void on_BackButton_clicked();

private:

};

#endif // NORMHEATFLUXDENSITY_H
