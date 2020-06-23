#include "dva.h"
#include "ui_dva.h"
#include <QtCore>
#include <QtGui>
#include <QTimerEvent>
#include <QButtonGroup>
#include <QPaintEvent>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <math.h>
#include <iostream>
#include "functions.h"
#include "qcustomplot.h"

using namespace std;

int prim_set=0,sec_set=0,exc_set=0,rpm;
double def_stat=0,freq_ratio=0,mass_ratio=0,exc_freq=0,prim_freq=0,sec_freq=0,prim_amp=0,prim_amp_wo=0,sec_amp=0;


dva::dva(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::dva)
{
    ui->setupUi(this);
    connect( ui->continue_primary, 
        SIGNAL(clicked()),
        this,
        SLOT(openprimaryWidget())
    );
    // Connection to primary window from dva window
    connect( ui->continue_excitation, 
        SIGNAL(clicked()),
        this,
        SLOT(openexcitationWidget())
    );
    // Connection to excitation window from dva window
    connect( ui->continue_secondary, 
        SIGNAL(clicked()),
        this,
        SLOT(opensecondaryWidget())
    );
    // Connection to secondary window from dva window
    connect( ui->primary_done, 
        SIGNAL(clicked()),
        this,
        SLOT(primaryValues_set())
    );
    // setting up the primary parameters
    connect( ui->exc_done, 
        SIGNAL(clicked()),
        this,
        SLOT(excitationValues_set())
    );
    // setting up the excitation parameters
    connect( ui->secondary_done, 
        SIGNAL(clicked()),
        this,
        SLOT(secondaryValues_set())
    );
    // setting up the secondary parameters
    connect( ui->run_pb, 
        SIGNAL(clicked()),
        this,
        SLOT(simulate())
    );
    // running the parameters
    connect(ui->rpm_sb,
        (SIGNAL(valueChanged(int))),
        ui->rpm_slider,
        SLOT(setValue(int))
    );
    connect(ui->rpm_slider,(
        SIGNAL(valueChanged(int))),
        ui->rpm_sb,
        SLOT(setValue(int))
    );
    // Connection to help Widget
    connect( ui->help_pb, 
        SIGNAL(clicked()), 
        this, 
        SLOT(openhelpWidget()) 
    ); 
    connect( ui->back_dva_pb, 
        SIGNAL(clicked()), 
        this, 
        SLOT(back_main()) 
    ); // Connection to mainwindow

    ui->key_pa->setStyleSheet("QTextBrowser{ background: transparent;}");
    ui->key_paw->setStyleSheet("QTextBrowser{ background: transparent;}");
    ui->key_sa->setStyleSheet("QTextBrowser{ background: transparent;}");
    ui->val_te->setStyleSheet("QTextBrowser{ background: transparent;}");

}

/**************************** PAINT EVENT **************************************************/

void dva::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPolygon poly1;
    poly1 << QPoint(0,0);
    poly1 << QPoint(550,0);
    poly1 << QPoint(550,729);
    poly1 << QPoint(0,729);
    QBrush fillbrush1(Qt::transparent);//,Qt::DiagCrossPattern);
    QPainterPath path1;
    path1.addPolygon(poly1);
    painter.fillPath(path1,fillbrush1);
    QPolygon poly2;
    poly2 << QPoint(550,0);
    poly2 << QPoint(1212,0);
    poly2 << QPoint(1212,729);
    poly2 << QPoint(550,729);
    QBrush fillbrush2(Qt::transparent);//,Qt::DiagCrossPattern);
    QPainterPath path2;
    path2.addPolygon(poly2);
    painter.fillPath(path2,fillbrush2);
}


/********************************** CREATING WIDGETS *************************************************************/

//* create instance of primary widget and set it up

void dva::openprimaryWidget()

{
    p2 = new primary;   // open primary widget
    p2->move(350,200);  // set its position on the screen
    // this line is necessary to really receive the destroyed signal when the widget
    //is closed!
    p2->setAttribute(Qt::WA_DeleteOnClose, true);   //deletes the primary widget when closed
    p2->show(); // show widget
    dva_buttonDisabler(); // Disable dva window Buttons
    // if primary window is closed, then restore dva Window
    connect( p2, SIGNAL(destroyed()), this, SLOT(dva_buttonEnabler()) );
}

//* create instance of excitation widget and set it up

void dva::openexcitationWidget()

{
    e2 = new excitation;    // open  excitation widget
    e2->move(350,200);  // set its position on the screen
    e2->setAttribute(Qt::WA_DeleteOnClose, true);   //deletes the excitation widget when closed
    e2->show(); // show widget
    dva_buttonDisabler(); // Disable dva window Buttons
    // if excitation window is closed, then restore dva Window
    connect( e2, SIGNAL(destroyed()), this, SLOT(dva_buttonEnabler()) );
}

//* create instance of secondary widget and set it up

void dva::opensecondaryWidget()

{    
    s2 = new secondary; // open secondary widget
    s2->move(350,200);  // set its position on the screen
    s2->setAttribute(Qt::WA_DeleteOnClose, true); //deletes the secondary widget when closed
    s2->show(); // show widget
    dva_buttonDisabler(); // Disable dva window Buttons
    // if secondary window is closed, then restore dva Window
    connect( s2, SIGNAL(destroyed()), this, SLOT(dva_buttonEnabler()) );
}

/*************************************SET VALUES****************************************************************/
//setting the parameters to run the program
void dva::primaryValues_set()
{
    int i;
    double d;
    string s;
    ifstream cs("dva_prima.txt");
    while(cs >> s >> d)
    {
        if((s=="prim_mass"||"prim_stiff")||(s=="prim_freq")||(s=="moi")||(s=="csa")||(s=="E")||(s=="rho")||(s=="length")){i=1;}
        else{i=0;}
    }
    if(i==1)
    {
        QMessageBox::information(this,"Done!", "Primary parameters set! Enter the other parameters,if not.");
        prim_set = 1;
    }
    else
    {
        QMessageBox::information(this, "Insufficient Data", "Enter the parameters before pressing 'Done'");
        prim_set = 0;
    }
}

void dva::excitationValues_set()
{
    int i;
    double d;
    string s;
    ifstream cs("dva_exen.txt");
    while(cs >> s >> d)
    {
        if((s=="ecc")||(s=="eccentric_mass")||(s=="eccentric_radius")){i=1;}
        else{i=0;}
    }
    if(i==1)
    {
        QMessageBox::information(this, "Done!", "Excitation parameters set! Enter the other parameters,if not.");
        exc_set = 1;
    }
    else
    {
        QMessageBox::information(this, "Insufficient Data", "Enter the parameters before pressing 'Done'");
        exc_set = 0;
    }
}

void dva::secondaryValues_set()
{
    int i;
    double d;
    string s;
    ifstream cs("dva_seco.txt");
    while(cs >> s >> d)
    {
        if((s=="sec_mass")||(s=="sec_stiff")||(s=="sec_freq")||(s=="mass_ratio")||(s=="freq_ratio")){i=1;}
        else{i=0;}
    }
    if(i==1)
    {
        QMessageBox::information(this, "Done!", "Secondary parameters set! Enter the other parameters,if not.");
        sec_set = 1;

    }
    else
    {
        QMessageBox::information(this, "Insufficient Data", "Enter the parameters before pressing 'Done'");
        sec_set = 0;

    }
}

/*************************************SIMULATE****************************************************************/

void dva::simulate()
{
    double d,prim_stiff,ecc,exc_force;
    int rpm;
    string s;
    res rs;
    exc fr;
    if((prim_set!=1)||(exc_set!=1)||(sec_set!=1))
    {
       QMessageBox::information(this, "Insufficient Data", "Enter the parameters before pressing 'Run'");
    }
    else
    {
        ifstream pm("dva_prima.txt");
        ifstream ex("dva_exen.txt");
        ifstream sc("dva_seco.txt");
        while(pm >> s >> d)
        {
            if(s=="prim_stiff"){prim_stiff = d;}
            if(s=="prim_freq"){prim_freq = d;}
        }
        while(ex >> s >> d)
        {
            if(s=="ecc"){ecc = d;}
        }
        while(sc >> s >> d)
        {
            if(s=="mass_ratio"){mass_ratio = d;}
            if(s=="freq_ratio"){freq_ratio = d;}
            if(s=="sec_freq"){sec_freq = d;}
        }

        cout<<"prim_stiff "<<prim_stiff<<endl;
        ui->rpm_sb->setRange(0,1000);
        ui->rpm_slider->setRange(0,1000);

        //ui->rpm_sb->setRange(0,((60*prim_freq)/(2*M_PI)));
        //ui->rpm_slider->setRange(0,((60*prim_freq)/(2*M_PI)));


        //ui->rpm_sb->setValue(10);                     // Assigning Default value for spinnner & Slider
        //ui->rpm_slider->setValue(10);

        rpm = ui->rpm_slider->value();

        cout<<"rpm "<<rpm<<endl;
        exc_freq = fr.exc_freq(rpm);
        cout<<"exc_freq "<<exc_freq<<endl;
        exc_force = fr.force(ecc,exc_freq);
        cout<<"exc_force "<<exc_force<<endl;
        cout<<"prim_stiff"<<prim_stiff<<endl;
        def_stat = rs.def_stat(exc_force,prim_stiff);
        cout<<"def_stat "<<def_stat<<endl;

        prim_amp = rs.prim_amp(def_stat,freq_ratio,mass_ratio,exc_freq,prim_freq);
        prim_amp_wo = rs.prim_amp_wo(def_stat,freq_ratio,prim_freq);
        sec_amp = rs.sec_amp(def_stat,freq_ratio,mass_ratio,exc_freq,prim_freq);
        cout<<"prim_amp "<<prim_amp<<endl;
        cout<<"prim_amp_wo "<<prim_amp_wo<<endl;
        cout<<"sec_amp "<<sec_amp<<endl;
        ofstream re("dva_results.txt");
        if(re.is_open())
        {
            re << "rpm " <<rpm<<endl;
            re << "exc_freq " <<exc_freq<<endl;
            re << "exc_force " <<exc_force<<endl;
            re << "def_stat " <<def_stat<<endl;
            re << "prim_amp " <<prim_amp<<endl;
            re << "sec_amp " <<sec_amp<<endl;
            re.close();
        }

        ui->mr_ln->display(mass_ratio);
        ui->mr_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->fr_ln->display(freq_ratio);
        ui->fr_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->pf_ln->display(prim_freq);
        ui->pf_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->sf_ln->display(sec_freq);
        ui->sf_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->ef_ln->display(exc_freq);
        ui->ef_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->ds_ln->display(def_stat);
        ui->ds_ln->setStyleSheet("QLCDNumber { color: white; background-color: black }");
        ui->pa_ln->display(prim_amp);
        ui->pa_ln->setStyleSheet("QLCDNumber { color: white; background-color: blue }");
        ui->paw_ln->display(prim_amp_wo);
        ui->paw_ln->setStyleSheet("QLCDNumber { color: white; background-color: red }");
        ui->sa_ln->display(sec_amp);
        ui->sa_ln->setStyleSheet("QLCDNumber { color: white; background-color: green }");

        disp_time_graph(ui->disp_time_plot);
        vel_time_graph(ui->vel_time_plot);
        acc_time_graph(ui->acc_time_plot);
    }
}

/***************************** DISPLACEMENT-TIME GRAPHS *********************************************************************/

void dva::disp_time_graph(QCustomPlot *disp_time_plot)
{
    disp_time_plot->addGraph(); // blue line
    disp_time_plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    disp_time_plot->graph(0)->setName("Amplitude of the Primary System with Secondary system");

    disp_time_plot->addGraph(); // red line
    disp_time_plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    disp_time_plot->graph(1)->setName("Amplitude of the Primary System without Secondary system");

    disp_time_plot->addGraph(); // green line
    disp_time_plot->graph(2)->setPen(QPen(QColor(0, 255, 0)));
    disp_time_plot->graph(2)->setName("Amplitude of the Secondary System");

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    disp_time_plot->xAxis->setTicker(timeTicker);
    disp_time_plot->axisRect()->setupFullAxesBox();
    disp_time_plot->yAxis->setRange(-1.2, 1.2);

    disp_time_plot->xAxis->setLabel("time");
    disp_time_plot->yAxis->setLabel("Displacement");

    /* set plot interactions */
    disp_time_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    /* make left and bottom axes transfer their ranges to right and top axes: */
    connect(disp_time_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), disp_time_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(disp_time_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), disp_time_plot->yAxis2, SLOT(setRange(QCPRange)));

    /* setup a timer that repeatedly calls MainWindow::realtimeDataSlot: */
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot_disp()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}


void dva::realtimeDataSlot_disp()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start, in seconds
    static double lastPointKey = 0;


    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      /* add data to lines: */
      ui->disp_time_plot->graph(0)->addData(key,((qSin(key*exc_freq))*prim_amp));
      ui->disp_time_plot->graph(1)->addData(key,((qSin(key*exc_freq))*prim_amp_wo));
      ui->disp_time_plot->graph(2)->addData(key,((qSin(key*exc_freq))*sec_amp));

      /* rescale value (vertical) axis to fit the current data: */
      ui->disp_time_plot->graph(0)->rescaleValueAxis();
      ui->disp_time_plot->graph(1)->rescaleValueAxis(true);
      ui->disp_time_plot->graph(2)->rescaleValueAxis();
      lastPointKey = key;
    }

    /* make key axis range scroll with the data (at a constant range size of 8): */
    ui->disp_time_plot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->disp_time_plot->replot();
}


/***************************** VELOCITY-TIME GRAPHS *********************************************************************/

void dva::vel_time_graph(QCustomPlot *vel_time_plot)
{
    vel_time_plot->addGraph(); // blue line
    vel_time_plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    vel_time_plot->graph(0)->setName("Velocity of the Primary System with Secondary system");

    vel_time_plot->addGraph(); // red line
    vel_time_plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    vel_time_plot->graph(1)->setName("Velocity of the Primary System without Secondary system");

    vel_time_plot->addGraph(); // green line
    vel_time_plot->graph(2)->setPen(QPen(QColor(0, 255, 0)));
    vel_time_plot->graph(2)->setName("Velocity of the Secondary System");

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    vel_time_plot->xAxis->setTicker(timeTicker);
    vel_time_plot->axisRect()->setupFullAxesBox();
    vel_time_plot->yAxis->setRange(-1.2, 1.2);

    vel_time_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectAxes |
                                   QCP::iSelectLegend | QCP::iSelectPlottables);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(vel_time_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), vel_time_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(vel_time_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), vel_time_plot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot_vel()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}


void dva::realtimeDataSlot_vel()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->vel_time_plot->graph(0)->addData(key,((qSin(key*exc_freq))*prim_amp)/key);
      ui->vel_time_plot->graph(1)->addData(key,((qSin(key*exc_freq))*prim_amp_wo)/key);
      ui->vel_time_plot->graph(2)->addData(key,((qSin(key*exc_freq))*sec_amp)/key);
      // rescale value (vertical) axis to fit the current data:
      ui->vel_time_plot->graph(0)->rescaleValueAxis(true);
      ui->vel_time_plot->graph(1)->rescaleValueAxis();
      ui->vel_time_plot->graph(2)->rescaleValueAxis();
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->vel_time_plot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->vel_time_plot->replot();
}


/***************************** ACCELERATION-TIME GRAPHS *********************************************************************/

void dva::acc_time_graph(QCustomPlot *acc_time_plot)
{
    acc_time_plot->addGraph(); // blue line
    acc_time_plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    acc_time_plot->graph(0)->setName("Acceleration of the Primary System with Secondary system");

    acc_time_plot->addGraph(); // red line
    acc_time_plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    acc_time_plot->graph(1)->setName("Acceleration of the Primary System without Secondary system");

    acc_time_plot->addGraph(); // green line
    acc_time_plot->graph(2)->setPen(QPen(QColor(0, 255, 0)));
    acc_time_plot->graph(2)->setName("Acceleration of the Secondary System");

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    acc_time_plot->xAxis->setTicker(timeTicker);
    acc_time_plot->axisRect()->setupFullAxesBox();
    acc_time_plot->yAxis->setRange(-1.2, 1.2);

    acc_time_plot->xAxis->setLabel("time");
    acc_time_plot->yAxis->setLabel("Acceleration");

    acc_time_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |QCP::iSelectAxes |
                                   QCP::iSelectLegend | QCP::iSelectPlottables);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(acc_time_plot->xAxis, 
        SIGNAL(rangeChanged(QCPRange)), 
        acc_time_plot->xAxis2, 
        SLOT(setRange(QCPRange))
    );
    connect(acc_time_plot->yAxis, 
        SIGNAL(rangeChanged(QCPRange)), 
        acc_time_plot->yAxis2, 
        SLOT(setRange(QCPRange))
    );

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, 
        SIGNAL(timeout()), 
        this, 
        SLOT(realtimeDataSlot_acc())
    );
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}


void dva::realtimeDataSlot_acc()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->acc_time_plot->graph(0)->addData(key,((qSin(key*exc_freq))*prim_amp)/pow(key,2));
      ui->acc_time_plot->graph(1)->addData(key,((qSin(key*exc_freq))*prim_amp_wo)/pow(key,2));
      ui->acc_time_plot->graph(2)->addData(key,((qSin(key*exc_freq))*sec_amp)/pow(key,2));
      // rescale value (vertical) axis to fit the current data:
      ui->acc_time_plot->graph(0)->rescaleValueAxis(true,true);
      ui->acc_time_plot->graph(1)->rescaleValueAxis(true,true);
      ui->acc_time_plot->graph(2)->rescaleValueAxis(true,true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->acc_time_plot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->acc_time_plot->replot();
}


//##############################################################################################
//##############################################################################################
/************************** ENABLING BUTTONS *************************************************************/

void dva::dva_buttonEnabler()

{
    ui->continue_primary->setDisabled(false);
    ui->continue_excitation->setDisabled(false);
    ui->continue_secondary->setDisabled(false);
    ui->rpm_sb->setDisabled(false);
    ui->rpm_slider->setDisabled(false);
    ui->primary_done->setDisabled(false);
    ui->exc_done->setDisabled(false);
    ui->secondary_done->setDisabled(false);
    ui->run_pb->setDisabled(false);
}

/************************** DISABLING BUTTONS*************************************************************/

void dva::dva_buttonDisabler()

{
    ui->continue_primary->setDisabled(true);
    ui->continue_excitation->setDisabled(true);
    ui->continue_secondary->setDisabled(true);
    ui->rpm_sb->setDisabled(true);
    ui->rpm_slider->setDisabled(true);
    ui->primary_done->setDisabled(true);
    ui->exc_done->setDisabled(true);
    ui->secondary_done->setDisabled(true);
    ui->run_pb->setDisabled(true);


}
/*************************** HELP WINDOW**************************************************/
void dva::openhelpWidget()
{
    h3 = new help;// open widget
    h3->move(450,200);// set its position on the screen
    h3->setAttribute(Qt::WA_DeleteOnClose, true);// destroys the signal when the widget is closed!
    h3->show();// show widget
    // enable elements for sending
}
/*************************** BACK BUTTON ****************************************************/
void dva::back_main()
{
    this->close();  // Close the dva Widget
}


/***********************************************************************************************/
dva::~dva()

{
    delete ui;
}


