#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dva.h"

namespace Ui

{
    class MainWindow;
}

class MainWindow : public QMainWindow

{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:

        //* create instance of dva widget and set it up
        void opendvaWidget();
        //* Close the widget
        void mainExit();
        // Enable the buttons in main window when 'Back' Button in dva solver
        //is pressed
        void buttonEnabler();

    private:
        Ui::MainWindow *ui;
        dva *w2; // dva Widget
};

#endif // MAINWINDOW_H
