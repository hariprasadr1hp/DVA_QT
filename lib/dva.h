#ifndef DVA_H
#define DVA_H

#include <QDialog>
#include "primary.h"
#include "excitation.h"
#include "secondary.h"
#include "help.h"
#include "qcustomplot.h"

namespace Ui
{
    class dva;
}

class dva : public QDialog

{
    Q_OBJECT

    public:
        explicit dva(QWidget *parent = 0);
        ~dva();

    public slots:
        void openprimaryWidget();       //* create instance of primary widget and set it up
        void openexcitationWidget();    //* create instance of excitation widget and set it up
        void opensecondaryWidget();     //* create instance of secondary widget and set it up
        void primaryValues_set();
        void excitationValues_set();
        void secondaryValues_set();
        void simulate();
        //void s_t_plot();
        //void v_t_plot();
        //void a_t_plot();
        void disp_time_graph(QCustomPlot *disp_time_plot);
        void vel_time_graph(QCustomPlot *vel_time_plot);
        void acc_time_graph(QCustomPlot *acc_time_plot);
        void dva_buttonEnabler();   // Enable the buttons in main window when 'Back' Button in dva solver is pressed
        void dva_buttonDisabler();
        void openhelpWidget();  // Open Help Widget
        void back_main();

    private slots:
        void realtimeDataSlot_disp();
        void realtimeDataSlot_vel();
        void realtimeDataSlot_acc();


private:
        Ui::dva *ui;
        primary *p2; 
        excitation *e2; 
        secondary *s2; 
        help *h3;
        QTimer dataTimer;

    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // DVA_H
