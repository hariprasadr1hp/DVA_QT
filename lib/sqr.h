#ifndef SQR_H
#define SQR_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui
{
    class sqr;
}

class sqr : public QDialog
{
    Q_OBJECT

    public:
        explicit sqr(QWidget *parent = 0);
        ~sqr();

    public slots:
        void sqrCalculate();
        void sqrExit();

    private:
        Ui::sqr *ui;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // SQR_H
