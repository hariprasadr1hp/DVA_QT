#ifndef SOLCIR_H
#define SOLCIR_H

#include <QDialog>
#include <QtGui>
#include <QtCore>


namespace Ui
{
    class solcir;
}

class solcir : public QDialog
{
    Q_OBJECT

    public:
        explicit solcir(QWidget *parent = 0);
        ~solcir();

    public slots:
        void solcirCalculate();
        void solcirExit();

    private:
        Ui::solcir *ui;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // SOLCIR_H
