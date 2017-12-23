#pragma once
#ifndef B_SPLINE_CURVE_H
#define B_SPLINE_CURVE_H

#define B_SPLINE_CURVE_MAX_NUM 100
#define B_SPLINE_CURVE_KNOT_VECTOR_START 0
#define B_SPLINE_CURVE_KNOT_VECTOR_END 1

enum KnotIntervalType{uniform=0,nonuniform=1,halfuniform=2};

class BSplineCurve
{
private:
    int control_point_num;
    double* control_point;
    int base_degree;
    KnotIntervalType type;
public:
    BSplineCurve(int base_degree=3,KnotIntervalType type=uniform)
    {
        control_point=new double[B_SPLINE_CURVE_MAX_NUM*3];
        control_point_num=0;
        this->base_degree=base_degree;
        this->type=type;
    }
    ~BSplineCurve()
    {
        delete []control_point;
    }
    void PrintControlPoint();
    void InsertControlPoint(double x,double y,double z);
    int GetControlPointNum();
    int GetBaseDegree();
    KnotIntervalType GetKnotIntervalType();
    
};

#endif
