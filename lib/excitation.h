#ifndef EXCITATION_H
#define EXCITATION_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui
{
    class excitation;
}

class excitation : public QDialog
{
    Q_OBJECT

    public:
        explicit excitation(QWidget *parent = 0);
        ~excitation();

    private:
        Ui::excitation *ui;

    private slots:
        void excitationCalculate();
        void excitationBack();
};

#endif // EXCITATION_H
