#pragma once

#ifndef PIA_B_SPLINE_CURVE_H
#define PIA_B_SPLINE_CURVE_H

#include "BSplineCurve.h"
#include <iostream>

#define PIA_ERR (1e-5)

class PiaBSplineCurve
{
private:
    BSplineCurve *PIA_Curve;
    double (*initial_control_point)[3]=NULL;
    //max difference;
    double delta;
public:
    PiaBSplineCurve()
    {
        PIA_Curve=new BSplineCurve(4,nonuniform);
        
    }
    ~PiaBSplineCurve()
    {
        delete PIA_Curve;
        delete []initial_control_point;
    }

    void ReadControlPointData(char *file_path);
    void PrintControlPoint();
    void PIA(int segmentation_num);
};

#endif
