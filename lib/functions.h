#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


//################################# SOLID CIRCLE #################################################################################
class solid_circle
{
    private:
        double dia;
    public:
        double moi(double a)
        {
            dia =a;
            return ((M_PI*pow(dia,4))/64)*pow(10,-8);
        }
        double csa(double a)
        {
            dia =a;
            return ((M_PI*pow(dia,2))/4)*pow(10,-4);
        }

};

//################################# HOLLOW CIRCLE #################################################################################

class hollow_circle
{
    private:
        double outer_dia,inner_dia;
    public:
        double moi(double a,double b)
        {
            outer_dia = a;
            inner_dia = b;
            return ((M_PI*(pow(outer_dia,4)-pow(inner_dia,4)))/64)*pow(10,-8);
        }

        double csa(double a,double b)
        {
            outer_dia = a;
            inner_dia = b;
            return ((M_PI*(pow(outer_dia,2)-pow(inner_dia,2)))/4)*pow(10,-4);
        }

};

//################################# RECTANGLE #################################################################################

class rectangle
{
    private:
        double breadth,depth;
    public:
        double moi(double a,double b)
        {
            breadth = a;
            depth = b;
            return ((breadth*pow(depth,3))/12)*pow(10,-8);
        }

        double csa(double a,double b)
        {
            breadth = a;
            depth = b;
            return (breadth*depth)*pow(10,-4);
        }

};

//################################# SQUARE #################################################################################

class square
{
    private:
        double side_length;
    public:
        double moi(double a)
        {
            side_length = a;
            return (pow(side_length,4)/12)*pow(10,-8);
        }

        double csa(double a)
        {
            side_length = a;
            return (pow(side_length,2))*pow(10,-4);
        }

};

//################################# I-SECTION #################################################################################

class isection
{
    private:
        double top_flange_breadth,top_flange_depth,web_breadth,web_depth,bottom_flange_breadth,bottom_flange_depth;
    public:
        double moi(double tfb,double tfd,double wb,double wd,double bfb,double bfd)
        {
            double a1,a2,a3,y1,y2,y3,ym,i1,i2,i3,im;
            top_flange_breadth = tfb;
            top_flange_depth = tfd;
            web_breadth = wb;
            web_depth = wd;
            bottom_flange_breadth = bfb;
            bottom_flange_depth = bfd;
            a1 = top_flange_breadth*top_flange_depth;
            a2 = web_breadth*web_depth;
            a3 = bottom_flange_breadth*bottom_flange_depth;
            y1 = bottom_flange_depth+web_depth+(top_flange_depth/2);
            y2 = bottom_flange_depth+(web_depth/2);
            y3 = bottom_flange_depth/2;
            ym = ((a1*y1)+(a2*y2)+(a3*y3))/(a1+a2+a3);
            i1 = ((top_flange_breadth*pow(top_flange_depth,3))/12)+(a1*(pow(ym-y1,2)));
            i2 = ((web_breadth*pow(web_depth,3))/12)+(a2*(pow(ym-y2,2)));
            i3 = ((bottom_flange_breadth*pow(bottom_flange_depth,3))/12)+(a3*(pow(ym-y3,2)));
            im = i1+i2+i3;

            return im*pow(10,-8);
        }

        double csa(double tfb,double tfd,double wb,double wd,double bfb,double bfd)
        {
            top_flange_breadth = tfb;
            top_flange_depth = tfd;
            web_breadth = wb;
            web_depth = wd;
            bottom_flange_breadth = bfb;
            bottom_flange_depth = bfd;
            return ((top_flange_breadth*top_flange_depth)+(web_breadth*web_depth)+(bottom_flange_breadth*bottom_flange_depth))*pow(10,-4);
        }

};

//################################# PRIMARY SYSTEM #################################################################################

class prim
{
    private:
        double length,csa,rho,youngs_mod,moi,stiffness,mass;

    public:

        double prim_mass(double u,double v,double w)																//primary mass(length,cross_section,density)
        {
            length = u;
            csa = v;
            rho = w;
            return (length*csa*rho);
        }

        double prim_stiff(double u,double v,double w)																//primary stiffness(modulus,moi,length)
        {
            youngs_mod = u;
            moi = v;
            length = w;
            return (48*((youngs_mod*pow(10,9)*moi)/pow(length,3)));
        }

        double prim_freq(double u,double v)																//primary frequency(stiffness,mass)
        {
            stiffness = u;
            mass = v;
            return (pow((stiffness/mass),0.5));
        }

};

//################################# EXCITATION SYSTEM #################################################################################

class exc
{
    private:
        double rpm,ecc_mass,ecc_rad,eccen,force_freq;

    public:
        double exc_freq(double u)																//excitation frequency(rpm)
        {
            rpm = u;
            return (2*M_PI*rpm)/60;
        }

        double ecc(double u,double v)																//excitation frequency(rpm)
        {
            ecc_mass = u;
            ecc_rad = v;
            return ecc_mass*(ecc_rad/100);
        }

        double force(double u,double v)																	//excitation force(ecc_mass,ecc_radius,exc_freq))
        {
            eccen = u;
            force_freq = v;
            return eccen*pow(force_freq,2);
        }


};

//################################# SECONDARY SYSTEM #################################################################################

class sec
{
    private:
        double prim_mass,mass_ratio,prim_freq,ratio_freq,freq_sec,mass_sec,ratio_freq_1;

    public:
        double sec_mass(double u,double v)																//secondary mass(primary mass, mass ratio)
        {
            prim_mass = u;
            mass_ratio = v;
            return (prim_mass*mass_ratio);
        }

        double freq_ratio_1(double u)															//frequency ratio_1(mass ratio)
        {
            double v,w;
            mass_ratio = u;
            v = 1+(mass_ratio/2);
            w = mass_ratio+((pow(mass_ratio,2)/4));
            return pow((v+w),0.5);
        }

        double freq_ratio_2(double u)															//frequency ratio_2(mass ratio)
        {
            double v,w;
            mass_ratio = u;
            v = 1+(mass_ratio/2);
            w = mass_ratio+((pow(mass_ratio,2)/4));
            return pow((v-w),0.5);
        }

        double freq_ratio(double u)								//frequency ratio(frequency_ratio_1)
        {
            ratio_freq_1 = u;
            return (ratio_freq_1);
        }

        double sec_freq(double u,double v)																//secondary frequency(primary frequency,frequency ratio)
        {

            prim_freq = u;
            ratio_freq = v;
            return (prim_freq*ratio_freq);
        }

        double sec_stiff(double u,double v)																//secondary stiffness(secondary frequency,secondary mass)
        {
            freq_sec = u;
            mass_sec = v;
            return (pow(freq_sec,2)*mass_sec);
        }


};

//################################# RESULTS #################################################################################

class res
{
    private:
        double force,prim_stiff,force_freq,prim_freq,mass_ratio,freq_ratio,stat_def;

    public:
        double def_stat(double u,double v)																//static deflection(force,primary stiffness)
        {
            force = u;
            prim_stiff = v;
            return (force/prim_stiff);
        }

        double prim_amp(double u,double v,double w,double x,double y)																//primary amplitude(exc_force,prim_freq,mr,fr,stat_def)
        {
            stat_def = u;
            freq_ratio = v;
            mass_ratio = w;
            force_freq = x;
            prim_freq = y;
            return (stat_def*(1-pow(freq_ratio,2)))/(((1-pow(freq_ratio,2))*(1+mass_ratio-pow((force_freq/prim_freq),2)))-mass_ratio);
        }

        double prim_amp_wo(double u,double v,double w)																//primary amplitude without secondary system(stat_def,fr,prim_freq)
        {
            stat_def = u;
            freq_ratio = v;
            prim_freq = w;
            return (stat_def/(1-((pow(freq_ratio,2))/(pow(prim_freq,2)))));
        }


        double sec_amp(double u,double v,double w,double x,double y)																//secondary amplitude(exc_force,prim_freq,mr,fr,stat_def)
        {
            stat_def = u;
            freq_ratio = v;
            mass_ratio = w;
            force_freq = x;
            prim_freq = y;
            return (stat_def)/(((1-pow(freq_ratio,2))*(1+mass_ratio-pow((force_freq/prim_freq),2)))-mass_ratio);
        }

};



//###################################################################################################

#endif // FUNCTIONS_H
