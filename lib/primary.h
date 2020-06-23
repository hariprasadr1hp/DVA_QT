#ifndef PRIMARY_H
#define PRIMARY_H

#include "solcir.h"
#include "holcir.h"
#include "rec.h"
#include "sqr.h"
#include "ise.h"

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui

{
    class primary;
}

class primary : public QDialog

{
    Q_OBJECT

    public:
        explicit primary(QWidget *parent = 0);
        ~primary();

    public slots:
        //* create instance of solid_circle widget and set it up
        void opensolcirWidget();
        //* create instance of hollow_circle widget and set it up
        void openholcirWidget();
        //* create instance of rectangle widget and set it up
        void openrecWidget();
        //* create instance of square widget and set it up
        void opensqrWidget();
        //* create instance of i_section widget and set it up
        void openiseWidget();
        //* create instance of secondary widget and set it up
        // Enable the buttons in dva solver when 'Back' Button in primary window
        //is pressed
        void display();
        void prim_buttonEnabler();
        void prim_buttonDisabler();

    private:
        Ui::primary *ui;
        solcir *sc2; // solid_circle Widget
        holcir *hc2; // hollow_circle Widget
        rec *rc2; // rectangle Widget
        sqr *sq2; // square Widget
        ise *is2; // i_section Widget

    protected:


    private slots:
        void sectionSelect_selection();
        void materialSelect_selection();
        //void showMat_prop();
        void primaryCalculate();
        void primaryBack();



};

#endif // PRIMARY_H
