#include "excitation.h"
#include "ui_excitation.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QButtonGroup>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QString>
#include <QTextStream>
#include <fstream>
#include "functions.h"




excitation::excitation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::excitation)
{
    ui->setupUi(this);

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                    0,1000.000,3); 

    // eccentric_mass : Lineedit type and to control i/p doubleValidator
    ui->ecc_mass_le->setValidator(doubleValidator);  
    // eccentric_radius : Lineedit type and to control i/p doubleValidator
    ui->ecc_radius_le->setValidator(doubleValidator);  


    connect(ui->excitation_ok,
        SIGNAL(clicked()),
        SLOT(excitationCalculate())
    );
    connect(ui->excitation_back,
        SIGNAL(clicked()),
        SLOT(excitationBack())
    );
}

void excitation::excitationCalculate()
{
    double eccentric_mass,eccentric_radius,eccentricity;
    exc ex;
    ui->ecc_mass_le->selectAll();
    ui->ecc_radius_le->selectAll();
    eccentric_mass = ui->ecc_mass_le->text().toDouble();
    eccentric_radius = ui->ecc_radius_le->text().toDouble();
    if ((eccentric_mass==0)||(eccentric_radius==0))
    {
        QMessageBox::information(this, 
            "Invalid Input", 
            "Enter non-zero values!"
        );
    }
    else
    {
        eccentricity = ex.ecc(eccentric_mass,eccentric_radius);
        ofstream exen("dva_exen.txt");
        if(exen.is_open())
        {
            exen << "ecc " <<eccentricity<<endl;
            exen << "eccentric_mass " <<eccentric_mass<<endl;
            exen << "eccentric_radius " <<eccentric_radius<<endl;
            exen.close();
        }
        this->close();
    }
}


void excitation::excitationBack()
{
    // Close the excitation Widget
    this->close();  
}


excitation::~excitation()
{
    delete ui;
}




