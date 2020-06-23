#ifndef HOLCIR_H
#define HOLCIR_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui
{
    class holcir;
}

class holcir : public QDialog
{
    Q_OBJECT

    public:
        explicit holcir(QWidget *parent = 0);
        ~holcir();

    public slots:
        void holcirCalculate();
        void holcirExit();

    private:
        Ui::holcir *ui;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // HOLCIR_H
