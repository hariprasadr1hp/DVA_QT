#ifndef SECONDARY_H
#define SECONDARY_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui
{
    class secondary;
}

class secondary : public QDialog
{
    Q_OBJECT

    public:
        explicit secondary(QWidget *parent = 0);
        ~secondary();

    private:
        Ui::secondary *ui;

    private slots:
        void secondaryCalculate();
        void secondaryBack();
};

#endif // SECONDARY_H
