#ifndef ISE_H
#define ISE_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui
{
    class ise;
}

class ise : public QDialog
{
    Q_OBJECT

    public:
        explicit ise(QWidget *parent = 0);
        ~ise();

    public slots:
        void iseCalculate();    //for calculating moment of inertia and cross-sectional area of an i-section
        void iseExit();         //to close the i-section window

    private:
        Ui::ise *ui;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // ISE_H
