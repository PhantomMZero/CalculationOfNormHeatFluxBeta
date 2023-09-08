#ifndef CHECKHEAT_H
#define CHECKHEAT_H

#include <QWidget>

namespace Ui {
class CheckHeat;
}

class CheckHeat : public QWidget
{
    Q_OBJECT

public:
    explicit CheckHeat(QWidget *parent = nullptr);
    ~CheckHeat();

private:
    Ui::CheckHeat *ui;
};

#endif // CHECKHEAT_H
