#pragma once

#ifndef PIA_B_SPLINE_CURVE_H
#define PIA_B_SPLINE_CURVE_H

#include "BSplineCurve.h"

#define PIA_ERR (1e-8)

class PiaBSplineCurve
{
private:
    BSplineCurve *PIA_Curve;
public:
    PiaBSplineCurve()
    {
        PIA_Curve=new BSplineCurve(4,quasiuniform);
    }
    ~PiaBSplineCurve()
    {
        delete PIA_Curve;
    }

    void ReadControlPointData(char *file_path);
    void PIA();
};

#endif
