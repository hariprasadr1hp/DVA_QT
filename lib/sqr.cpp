#include "sqr.h"
#include "ui_sqr.h"

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


sqr::sqr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sqr)

{
    ui->setupUi(this);
    connect( ui->square_ok, SIGNAL(clicked()), this, SLOT(sqrCalculate()) );
    // Confirming the values, connection to primary window

    connect( ui->square_back, SIGNAL(clicked()), this, SLOT(sqrExit()) );
    // Without confirming the values, connection to primary window

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                        0,1000.000,3); 

    //  Diameter_solid : Lineedit type and to control i/p doubleValidator
    ui->side_square_le->setValidator(doubleValidator);  
}

void sqr::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //make square
    QPolygon poly;
    poly << QPoint(200,100);
    poly << QPoint(400,100);
    poly << QPoint(400,300);
    poly << QPoint(200,300);
    //make a pen
    QPen linepen;
    linepen.setWidth(6);
    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    //make a brush
    QBrush fillbrush(Qt::blue,Qt::DiagCrossPattern);
    QPainterPath path;
    path.addPolygon(poly);
    //draw square
    painter.drawPolygon(poly);
    painter.fillPath(path,fillbrush);
}


void sqr::sqrCalculate()
{
    double side_square,moi,csa;
    square sq;
    ui->side_square_le->selectAll();
    side_square = ui->side_square_le->text().toDouble();
    if ((side_square==0)||(side_square>=1000))
    {
        QMessageBox::information(this, 
            "Invalid Input", 
            "Enter a positive integer less than 1000!"
        );
    }
    else
    {
        moi = sq.moi(side_square);
        csa = sq.csa(side_square);
        ofstream moicsa("moicsa.txt");
        if(moicsa.is_open())
        {
            moicsa << "moi " <<moi<<endl;
            moicsa << "csa " <<csa<<endl;
            moicsa.close();
        }
        this->close();
    }
}

void sqr::sqrExit()
{
    // Close the square Widget
    this->close();  
}

sqr::~sqr()
{
    delete ui;
}
