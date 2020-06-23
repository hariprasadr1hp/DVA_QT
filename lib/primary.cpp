#include "primary.h"
#include "ui_primary.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QPaintEvent>
#include <QButtonGroup>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <fstream>
#include "functions.h"


primary::primary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::primary)
{
    ui->setupUi(this);
    connect(ui->sectionSelect_pb,
        SIGNAL(clicked()),
        SLOT(sectionSelect_selection())
    );

    // To control i/p double type variable: User can enter only numbers 
    // between 0 and 1000 and decimal up to 3 decimal points
    QDoubleValidator* doubleValidator = new QDoubleValidator(
                                                        0,1000.000,3); 

    // Beam Length : Lineedit type and to control i/p doubleValidator
    ui->beam_length_le->setValidator(doubleValidator);  
    // youngs modulus : Lineedit type and to control i/p doubleValidator
    ui->youngs_mod_le->setValidator(doubleValidator);   
    // material density : Lineedit type and to control i/p doubleValidator
    ui->mat_rho_le->setValidator(doubleValidator);      


    connect(ui->Material_select_pb,
        SIGNAL(clicked()),
        SLOT(materialSelect_selection())
    );

    connect(ui->primary_ok,
        SIGNAL(clicked()),
        SLOT(primaryCalculate())
    );
    connect(ui->primary_back,
        SIGNAL(clicked()),
        SLOT(primaryBack())
    );
    ui->youngs_mod_le->setEnabled(false);
    ui->mat_rho_le->setEnabled(false);
}

/*********************************** CROSS SECTION SELECTION *******************************************************/

void primary::sectionSelect_selection()
{
    if(ui->solidCircle_rb->isChecked())
    {
    opensolcirWidget();
    // Connection to solid_circle window from primary window
    display();
    }
    else if(ui->hollowCircle_rb->isChecked())
    {
        openholcirWidget();
        // Connection to hollow_circle window from primary window
        display();
    }
    else if(ui->rectangle_rb->isChecked())
    {
        openrecWidget();
        // Connection to rectangle window from primary window
        display();
    }
    else if(ui->square_rb->isChecked())
    {
        opensqrWidget();
        // Connection to square window from primary window
        display();
    }
    else if(ui->iSection_rb->isChecked())
    {
        openiseWidget();
        // Connection to i_section window from primary window
        display();
    }
    else
    {
        QMessageBox::information(this,
            "Error",
            "Please select one of the cross-sections"
        );
    }
}

//* create instance of solid_circle widget and set it up

void primary::opensolcirWidget()

{
    sc2 = new solcir;   // open widget
    // set its position on the screen
    sc2->move(750,200); 
    //destroys the signal when the widget is closed!
    sc2->setAttribute(Qt::WA_DeleteOnClose, true);  
    sc2->show();    // show widget
    prim_buttonDisabler(); // Disable primary window Buttons
    connect( sc2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT(prim_buttonEnabler())
    );// if solid_circle window is closed, then restore primary Window
}

//* create instance of hollow_circle widget and set it up

void primary::openholcirWidget()

{
    hc2 = new holcir;   // open widget
    hc2->move(750,200); // set its position on the screen
    hc2->setAttribute(Qt::WA_DeleteOnClose, true);  //destroys the signal when the widget is closed!
    hc2->show();    // show widget
    prim_buttonDisabler(); // Disable primary window Buttons
    connect( hc2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT(prim_buttonEnabler())
    );// if hollow_circle window is closed, then restore primary Window
}

//* create instance of rectangle widget and set it up

void primary::openrecWidget()

{
    rc2 = new rec;  // open widget
    rc2->move(750,200); // set its position on the screen
    rc2->setAttribute(Qt::WA_DeleteOnClose, true);  // destroys the signal when the widget is closed!
    rc2->show();    // show widget
    prim_buttonDisabler(); // Disable primary window Buttons
    connect( rc2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT(prim_buttonEnabler()) 
    );// if rectangle window is closed, then restore primary Window
}

//* create instance of square widget and set it up

void primary::opensqrWidget()

{

    sq2 = new sqr;  // open widget
    sq2->move(750,200); // set its position on the screen
    sq2->setAttribute(Qt::WA_DeleteOnClose, true); //destroy the signal when the widget is closed!
    sq2->show();    // show widget
    prim_buttonDisabler(); // Disable primary window Buttons
    connect( sq2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT(prim_buttonEnabler()) 
    );// if square window is closed, then restore primary Window
}

//* create instance of i_section widget and set it up

void primary::openiseWidget()

{
    is2 = new ise;  // open widget
    is2->move(750,200); // set its position on the screen
    is2->setAttribute(Qt::WA_DeleteOnClose, true);  //destroys the signal when the widget is closed!
    is2->show();    // show widget
    prim_buttonDisabler(); // Disable primary window Buttons
    connect( is2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT(prim_buttonEnabler())
    );// if i_section window is closed, then restore primary Window
}
/********************************** DISPLAY *********************************************************/
void primary::display()
{
    double d,moi,csa;
    string s;
    ifstream cs("dva_moicsa.txt");
    while(cs >> s >> d)
    {
        if(s=="moi"){moi = d;}
        if(s=="csa"){csa = d;}
    }
    ui->moi_ln->display(moi);
    ui->moi_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
    ui->csa_ln->display(csa);
    ui->csa_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
}

/********************************** MATERIAL SELECTION *********************************************************/

void primary::materialSelect_selection()
{
    if(ui->aluminium_rb->isChecked())
    {
        double E,rho;
        E = 69;
        rho = 2800;

        ui->E_ln->display(E);
        ui->E_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->rho_ln->display(rho);
        ui->rho_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->youngs_mod_le->setEnabled(false);
        ui->mat_rho_le->setEnabled(false);
        ofstream erho("dva_erho.txt");
        if(erho.is_open())
        {
            erho << "E " <<E<<endl;
            erho << "rho " <<rho<<endl;
            erho.close();
        }
    }
    else if(ui->steel_rb->isChecked())
    {
        double E,rho;
        E = 210;
        rho = 8050;
        ui->E_ln->display(E);
        ui->E_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->rho_ln->display(rho);
        ui->rho_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->youngs_mod_le->setEnabled(false);
        ui->mat_rho_le->setEnabled(false);
        ofstream erho("dva_erho.txt");
        if(erho.is_open())
        {
            erho << "E " <<E<<endl;
            erho << "rho " <<rho<<endl;
            erho.close();
        }
    }
    else if(ui->castiron_rb->isChecked())
    {
        double E,rho;
        E = 130;
        rho = 6800;
        ui->E_ln->display(E);
        ui->E_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->rho_ln->display(rho);
        ui->rho_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->youngs_mod_le->setEnabled(false);
        ui->mat_rho_le->setEnabled(false);
        ofstream erho("dva_erho.txt");
        if(erho.is_open())
        {
            erho << "E " <<E<<endl;
            erho << "rho " <<rho<<endl;
            erho.close();
        }
    }
    else if(ui->other_material_rb->isChecked())
    {
        double E,rho;
        ui->youngs_mod_le->setEnabled(true);
        ui->mat_rho_le->setEnabled(true);
        ui->youngs_mod_le->selectAll();
        ui->mat_rho_le->selectAll();
        E = ui->youngs_mod_le->text().toDouble();
        rho = ui->mat_rho_le->text().toDouble();
        if ((E==0)||(rho==0))
        {
            QMessageBox::information(this, "Invalid Input", "Enter non-zero values!");
        }
        else if ((rho>=21500)||(rho<=1750))
        {
            QMessageBox::information(this, "Invalid Input", "Enter 'Rho' value between 1750 to 21500");
        }
        else if ((E>=670)||(E<=130))
        {
            QMessageBox::information(this, "Invalid Input", "Enter 'E' value between 130 to 670");
        }
        else
        {
            ofstream erho("dva_erho.txt");
            if(erho.is_open())
            {
                erho << "E " <<E<<endl;
                erho << "rho " <<rho<<endl;
                ui->E_ln->display(E);
                ui->E_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
                ui->rho_ln->display(rho);
                ui->rho_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
                erho.close();
            }
        }
    }
    else
    {
        QMessageBox::information(this,
            "Error",
            "Please select one of the materials"
        );
    }
}


/***********************************PRIMARY SYSTEM CALCULATION***************************************************/

void primary::primaryCalculate()
{
    double d,moi,csa,E,rho,length,prim_mass,prim_stiff,prim_freq;
    int i=0,j=0;
    string s;
    ui->beam_length_le->selectAll();
    length = ui->beam_length_le->text().toDouble();
    if ((length<=0)||(length>=500))
    {
        QMessageBox::information(this, 
            "Invalid Input", 
            "Enter a non-zero positive integer below 500!"
        );
    }
    else
    {
        ifstream cs("dva_moicsa.txt");
        ifstream ms("dva_erho.txt");
        while(cs >> s >> d)
        {
            if(s=="moi"){moi = d;i=1;}
            if(s=="csa"){csa = d;i=1;}
        }
        while(ms >> s >> d)
        {
            if(s=="E"){E = d;j = 1;}
            if(s=="rho"){rho = d;j = 1;}
        }
        if(i!=1){
            QMessageBox::information(this, 
                "Insufficient Data", 
                "Select a cross-section"
            );
        }
        else if(j!=1){
            QMessageBox::information(this, 
                "Insufficient Data", 
                "Define a material"
            );
        }
        else
        {
            prim pri;
            prim_mass = pri.prim_mass(length,csa,rho);
            prim_stiff = pri.prim_stiff(E,moi,length);
            prim_freq = pri.prim_freq(prim_stiff,prim_mass);
            ofstream prima("dva_prima.txt");
            if(prima.is_open())
            {
                prima << "prim_mass " <<prim_mass<<endl;
                prima << "prim_stiff " <<prim_stiff<<endl;
                prima << "prim_freq " <<prim_freq<<endl;
                prima << "moi " <<moi<<endl;
                prima << "csa " <<csa<<endl;
                prima << "E " <<E<<endl;
                prima << "rho " <<rho<<endl;
                prima << "length " <<length<<endl;
                prima.close();
                cout<<"prima.txt opened"<<endl;
            }
            else{cout<<"prima.txt not opened"<<endl;}
            this->close();
        }
    }
}

/***************************************************************************************************************/

void primary::primaryBack()
{
    this->close();  // Close the primary Widget
}

/************************************** BUTTON ENABLER *******************************************/

void primary::prim_buttonEnabler()

{
    ui->sectionSelect_pb->setDisabled(false);
    ui->solidCircle_rb->setDisabled(false);
    ui->hollowCircle_rb->setDisabled(false);
    ui->rectangle_rb->setDisabled(false);
    ui->square_rb->setDisabled(false);
    ui->iSection_rb->setDisabled(false);
    ui->aluminium_rb->setDisabled(false);
    ui->steel_rb->setDisabled(false);
    ui->castiron_rb->setDisabled(false);
    ui->other_material_rb->setDisabled(false);
    //ui->youngs_mod_le->setDisabled(false);
    //ui->mat_rho_le->setDisabled(false);
    ui->Material_select_pb->setDisabled(false);
    ui->beam_length_le->setDisabled(false);
    ui->primary_ok->setDisabled(false);
    ui->primary_back->setDisabled(false);
}

/************************************** BUTTON DISABLER *************************************************/
void primary::prim_buttonDisabler()

{
    ui->sectionSelect_pb->setDisabled(true);
    ui->solidCircle_rb->setDisabled(true);
    ui->hollowCircle_rb->setDisabled(true);
    ui->rectangle_rb->setDisabled(true);
    ui->square_rb->setDisabled(true);
    ui->iSection_rb->setDisabled(true);
    ui->aluminium_rb->setDisabled(true);
    ui->steel_rb->setDisabled(true);
    ui->castiron_rb->setDisabled(true);
    ui->other_material_rb->setDisabled(true);
    ui->youngs_mod_le->setDisabled(true);
    ui->mat_rho_le->setDisabled(true);
    ui->Material_select_pb->setDisabled(true);
    ui->beam_length_le->setDisabled(true);
    ui->primary_ok->setDisabled(true);
    ui->primary_back->setDisabled(true);
}
/********************************************************************************************************/
primary::~primary()
{
    delete ui;
}


