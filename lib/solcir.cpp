#include "solcir.h"
#include "ui_solcir.h"

#include <QtCore>
#include <QtGui>
#include <QPaintEvent>
#include <QMessageBox>
#include <QErrorMessage>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <string>
#include <fstream>
#include "functions.h"


solcir::solcir(QWidget *parent) : QDialog(parent), ui(new Ui::solcir)
{
    ui->setupUi(this);
    connect( ui->solid_circle_ok, 
        SIGNAL(clicked()), 
        this, 
        SLOT(solcirCalculate()) 
    );
    // Confirming the values, connection to primary window

    connect( ui->solid_circle_back, 
        SIGNAL(clicked()), 
        this, 
        SLOT(solcirExit()) 
    );
    // Without confirming the values, connection to primary window

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                        0,1000.000,3); 

    //  Diameter_solid : Lineedit type and to control i/p doubleValidator
    ui->dia_solidcircle_le->setValidator(doubleValidator);  
}

void solcir::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rec(100,100,200,200);
    QPen framepen(Qt::red);
    framepen.setWidth(6);
    painter.setPen(framepen);
    //QBrush brush(Qt::blue,Qt::DiagCrossPattern);
    painter.drawEllipse(rec);
}

void solcir::solcirCalculate()
{
    double dia_solidcircle,moi,csa;
    solid_circle sc;    
    ui->dia_solidcircle_le->selectAll();
    dia_solidcircle = ui->dia_solidcircle_le->text().toDouble();
    if ((dia_solidcircle==0)||(dia_solidcircle>=1000))
    {
        QMessageBox::information(this, 
                "Invalid Input", 
                "Enter a positive integer less than 1000!"
        );
    }
    else
    {
        moi = sc.moi(dia_solidcircle);
        csa = sc.csa(dia_solidcircle);
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

void solcir::solcirExit()
{
    this->close();  // Close the solid_circle Widget
}

solcir::~solcir()
{
    delete ui;
}
