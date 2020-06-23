#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <fstream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->continue_dva, 
        SIGNAL(clicked()), 
        this, 
        SLOT(opendvaWidget()) 
    );
    // Connection to dva from main Window
    connect( ui->exitProgram, 
        SIGNAL(clicked()), 
        this, 
        SLOT(mainExit()) 
    );
    // Connection to Exit from main Window
}


//* create instance of dva widget and set it up

void MainWindow::opendvaWidget()
{
    // open widget
    w2 = new dva;
    // set its position on the screen
    w2->move(350,200);
    // this line is necessary to really receive the destroyed signal
    // when the widget is closed!
    w2->setAttribute(Qt::WA_DeleteOnClose, true);
    // show widget
    w2->show();
    ;
    ui->continue_dva->setDisabled(true); // Disable mainwindow Button
    ui->exitProgram->setDisabled(true); // Prevent undesirable closing of main window

    // if dva is closed, then restore main Window
    connect( w2, 
        SIGNAL(destroyed()), 
        this, 
        SLOT( buttonEnabler()) 
    );
}

void MainWindow::mainExit()
{
    remove("dva_moicsa.txt");
    remove("dva_prima.txt");
    remove("dva_erho.txt");
    remove("dva_exen.txt");
    remove("dva_seco.txt");
    remove("dva_all.txt");
    remove("dva_results.txt");
    this->close();  // Close the Main Widget
}

void MainWindow::buttonEnabler()
{
    ui->continue_dva->setDisabled(false);
    ui->exitProgram->setDisabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}
