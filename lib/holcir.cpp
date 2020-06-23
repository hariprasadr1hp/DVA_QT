#include "holcir.h"
#include "ui_holcir.h"

#include <QtCore>
#include <QtGui>
#include <QPaintEvent>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QString>
#include <QTextStream>
#include <fstream>
#include "functions.h"


holcir::holcir(QWidget *parent) : QDialog(parent), ui(new Ui::holcir)

{
    ui->setupUi(this);
    connect( ui->hollow_circle_ok, 
        SIGNAL(clicked()), 
        this, 
        SLOT(holcirCalculate()) 
    );
    // Confirming the values, connection to primary window

    connect( ui->hollow_circle_back, 
        SIGNAL(clicked()), 
        this, 
        SLOT(holcirExit()) 
    );
    // Without confirming the values, connection to primary window

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                        0,1000.000,3); 

     // outer_dia : Lineedit type and to control i/p doubleValidator
    ui->outerdia_hollowcircle_le->setValidator(doubleValidator); 
    // inner_dia : Lineedit type and to control i/p doubleValidator
    ui->innerdia_hollowcircle_le->setValidator(doubleValidator);   
}

void holcir::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rec1(100,100,400,400);
    QRect rec2(200,200,200,200);
    QPen framepen(Qt::red);
    framepen.setWidth(6);
    painter.setPen(framepen);
    //QBrush brush(Qt::blue,Qt::DiagCrossPattern);
    painter.drawEllipse(rec2);
    painter.drawEllipse(rec1);
}

void holcir::holcirCalculate()
{
    double outer_dia,inner_dia,moi,csa;
    hollow_circle hc;
    ui->outerdia_hollowcircle_le->selectAll();
    ui->innerdia_hollowcircle_le->selectAll();
    outer_dia = ui->outerdia_hollowcircle_le->text().toDouble();
    inner_dia = ui->innerdia_hollowcircle_le->text().toDouble();
    if ((outer_dia==0)||(inner_dia==0)||(outer_dia>=1000)||(inner_dia>=1000))
    {
        QMessageBox::information(
            this, 
            "Invalid Input", "Enter a positive integer less than 1000!"
        );
    }
    else if (inner_dia>=(0.9*outer_dia))
    {
        QMessageBox::information(this, 
            "Invalid Input", "Inner Diameter should be lesser than \\
            the nine-tenth of the outer one!");
    }
    else
    {
        moi = hc.moi(outer_dia,inner_dia);
        csa = hc.csa(outer_dia,inner_dia);
        ofstream moicsa("dva_moicsa.txt");
        if(moicsa.is_open())
        {
            moicsa << "moi " <<moi<<endl;
            moicsa << "csa " <<csa<<endl;
            moicsa.close();
        }
        this->close();
    }
}

void holcir::holcirExit()
{
    this->close(); 
}

holcir::~holcir()
{
    delete ui;
}
