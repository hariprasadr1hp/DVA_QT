#include "secondary.h"
#include "ui_secondary.h"

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


secondary::secondary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondary)
{
    ui->setupUi(this);

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                    0.0001,0.4500,5); 

    // Beam Length : Lineedit type and to control i/p doubleValidator
    ui->mass_ratio_le->setValidator(doubleValidator);  

    connect(ui->secondary_ok,
        SIGNAL(clicked()),
        SLOT(secondaryCalculate())
    );
    connect(ui->secondary_back,
        SIGNAL(clicked()),
        SLOT(secondaryBack())
    );
}

void secondary::secondaryCalculate()
{
    double d,mass_ratio,freq_ratio,freq_ratio_1;
    double prim_mass,prim_freq,sec_mass,sec_stiff,sec_freq;
    string s;
    sec se;
    ui->mass_ratio_le->selectAll();
    mass_ratio = ui->mass_ratio_le->text().toDouble();
    if ((mass_ratio==0)||(mass_ratio>=0.4))
    {
        QMessageBox::information(this, 
            "Invalid Input", 
            "Enter a value between 0 and 0.4"
        );
    }
    else
    {
        ifstream secon("dva_prima.txt");
        while(secon >> s >> d)
        {
            if(s=="prim_mass"){prim_mass = d;}
            if(s=="prim_freq"){prim_freq = d;}
        }

        sec_mass = se.sec_mass(prim_mass,mass_ratio);
        freq_ratio_1 = se.freq_ratio_1(mass_ratio);
        freq_ratio = se.freq_ratio(freq_ratio_1);
        sec_freq = se.sec_freq(prim_freq,freq_ratio);
        sec_stiff = se.sec_stiff(sec_freq,sec_mass);
        ofstream seco("dva_seco.txt");
        if(seco.is_open())
        {
            seco << "sec_mass " <<sec_mass<<endl;
            seco << "sec_stiff " <<sec_stiff<<endl;
            seco << "sec_freq " <<sec_freq<<endl;
            seco << "mass_ratio " <<mass_ratio<<endl;
            seco << "freq_ratio " <<freq_ratio<<endl;
            seco.close();
        }
        this->close();
    }
}



void secondary::secondaryBack()
{
    // Close the secondary Widget
    this->close();  
}


secondary::~secondary()
{
    delete ui;
}




