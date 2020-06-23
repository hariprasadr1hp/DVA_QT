#include "ise.h"
#include "ui_ise.h"

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


ise::ise(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ise)

{
    ui->setupUi(this);
    connect( ui->i_section_ok, 
        SIGNAL(clicked()), 
        this, 
        SLOT(iseCalculate()) 
    );
    // Confirming the values, connection to primary window

    connect( ui->i_section_back, 
        SIGNAL(clicked()), 
        this, 
        SLOT(iseExit()) 
    );
    // Without confirming the values, connection to primary window

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(0,1000.000,3); 
    
    //top_flange_breadth,top_flange_depth,web_breadth,
    //web_depth,bottom_flange_breadth,bottom_flange_depth,
    //Lineedit type and to control i/p doubleValidator
    
    ui->tfb_isect_le->setValidator(doubleValidator);  
    ui->tfd_isect_le->setValidator(doubleValidator);
    ui->wb_isect_le->setValidator(doubleValidator); 
    ui->wd_isect_le->setValidator(doubleValidator); 
    ui->bfb_isect_le->setValidator(doubleValidator);
    ui->bfd_isect_le->setValidator(doubleValidator);

}

void ise::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPolygon poly;              //make i_section
    poly << QPoint(200,150);
    poly << QPoint(400,150);
    poly << QPoint(400,170);
    poly << QPoint(315,170);
    poly << QPoint(315,320);
    poly << QPoint(375,320);
    poly << QPoint(375,350);
    poly << QPoint(225,350);
    poly << QPoint(225,320);
    poly << QPoint(285,320);
    poly << QPoint(285,170);
    poly << QPoint(200,170);
    //make a pen
    QPen linepen;               
    linepen.setWidth(6);
    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    //make a brush
    QBrush fillbrush(Qt::blue,Qt::DiagCrossPattern);    
    QPainterPath path;
    //draw i_section
    path.addPolygon(poly);
    painter.drawPolygon(poly);  
    painter.fillPath(path,fillbrush);
}

void ise::iseCalculate()
{
    double top_flange_breadth,top_flange_depth,web_breadth;
    double web_depth,bottom_flange_breadth,bottom_flange_depth;
    double moi,csa;
    isection is;
    //Entered dimensions by the user
    ui->tfb_isect_le->selectAll();
    ui->tfd_isect_le->selectAll();
    ui->wb_isect_le->selectAll();
    ui->wd_isect_le->selectAll();
    ui->bfb_isect_le->selectAll();
    ui->bfd_isect_le->selectAll();
    //converting the string to double
    top_flange_breadth = ui->tfb_isect_le->text().toDouble();
    top_flange_depth = ui->tfd_isect_le->text().toDouble();
    web_breadth = ui->wb_isect_le->text().toDouble();
    web_depth = ui->wd_isect_le->text().toDouble();
    bottom_flange_breadth = ui->bfb_isect_le->text().toDouble();
    bottom_flange_depth = ui->bfd_isect_le->text().toDouble();
    //Validation of input(whether non-zero integers are entered)
    if ((top_flange_breadth==0)||(top_flange_depth==0)||(web_breadth==0)||(web_depth==0)||(bottom_flange_breadth==0)||(bottom_flange_depth==0)||(top_flange_breadth>=1000)||(top_flange_depth>=1000)||(web_breadth>=1000)||(web_depth>=1000)||(bottom_flange_breadth>=1000)||(bottom_flange_depth>=1000))
    {
        QMessageBox::information(this, "Invalid Input", "Enter a positive integer less than 1000!");
    }
    else if ((top_flange_breadth<=web_breadth)||(bottom_flange_breadth<=web_breadth))
    {
        QMessageBox::information(this, "Invalid Input", "Enter valid parameters!");
    }
    else
    {
        //calculating moment of inertia and cross-sectional area
        moi = is.moi(top_flange_breadth,top_flange_depth,web_breadth,web_depth,bottom_flange_breadth,bottom_flange_depth);
        csa = is.csa(top_flange_breadth,top_flange_depth,web_breadth,web_depth,bottom_flange_breadth,bottom_flange_depth);
        ofstream moicsa("dva_moicsa.txt");
        //copying the moi and csa values to a file
        if(moicsa.is_open())
        {
            moicsa << "moi " <<moi<<endl;
            moicsa << "csa " <<csa<<endl;
            moicsa.close();
        }
        this->close();
    }
}


void ise::iseExit()
    {
        this->close();  // Close the i_section Widget
    }


ise::~ise()
{
    delete ui;
}
