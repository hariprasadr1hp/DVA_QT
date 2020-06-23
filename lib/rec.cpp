#include "rec.h"
#include "ui_rec.h"

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


rec::rec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rec)

{
    ui->setupUi(this);
    connect( ui->rectangle_ok, 
        SIGNAL(clicked()), 
        this, 
        SLOT(recCalculate()) 
    );
    // Confirming the values, connection to primary window

    connect( ui->rectangle_back, 
        SIGNAL(clicked()), 
        this, 
        SLOT(recExit()) 
    );
    // Without confirming the values, connection to primary window

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                            0,1000.000,3); 
    // breadth : Lineedit type and to control i/p doubleValidator
    ui->breadth_rect_le->setValidator(doubleValidator); 
    // depth : Lineedit type and to control i/p doubleValidator 
    ui->depth_rect_le->setValidator(doubleValidator);   

}

void rec::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //make rectangle
    QPolygon poly;
    poly << QPoint(200,100);
    poly << QPoint(400,100);
    poly << QPoint(400,500);
    poly << QPoint(200,500);
    //make a pen
    QPen linepen;
    linepen.setWidth(6);
    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    //make a brush
    QBrush fillbrush(Qt::blue,Qt::DiagCrossPattern);
    QPainterPath path;
    path.addPolygon(poly);
    //draw rectangle
    painter.drawPolygon(poly);
    painter.fillPath(path,fillbrush);
}

void rec::recCalculate()
{
    double breadth,depth,moi,csa;
    rectangle rc;
    ui->breadth_rect_le->selectAll();
    ui->depth_rect_le->selectAll();
    breadth = ui->breadth_rect_le->text().toDouble();
    depth = ui->depth_rect_le->text().toDouble();
    if ((breadth==0)||(depth==0)||(breadth>=1000)||(depth>=1000))
    {
        QMessageBox::information(this, 
            "Invalid Input", 
            "Enter a positive integer less than 1000!"
        );
    }
    else
    {
        moi = rc.moi(breadth,depth);
        csa = rc.csa(breadth,depth);
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

void rec::recExit()
{
    // Close the rectangle Widget
    this->close();  
}


rec::~rec()
{
    delete ui;
}
