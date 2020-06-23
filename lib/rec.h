#ifndef REC_H
#define REC_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui
{
    class rec;
}

class rec : public QDialog
{
    Q_OBJECT

    public:
        explicit rec(QWidget *parent = 0);
        ~rec();

    public slots:
        void recCalculate();
        void recExit();

    private:
        Ui::rec *ui;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // REC_H
