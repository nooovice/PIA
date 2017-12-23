#include"BSplineCurve.h"
#include<iostream>

void BSplineCurve::PrintControlPoint()
{
    for(int i=0;i<this->control_point_num;++i)
    {
        std::cout<<control_point[i]<<","<<control_point[B_SPLINE_CURVE_MAX_NUM+i]<<","<<control_point[2*B_SPLINE_CURVE_MAX_NUM+i]<<std::endl;
    }
    std::cout<<"totally "<<control_point_num<<" control points"<<std::endl;
}

void BSplineCurve::InsertControlPoint(double x,double y,double z)
{
    if(this->control_point_num<B_SPLINE_CURVE_MAX_NUM)
    {
        control_point[control_point_num]=x;
        control_point[B_SPLINE_CURVE_MAX_NUM+control_point_num]=y;
        control_point[2*B_SPLINE_CURVE_MAX_NUM+control_point_num]=z;
        std::cout<<"Insertion succeeded."<<std::endl;
        ++control_point_num;
    }
    else
    {
        std::cout<<"Insertion failed."<<std::endl;
    }
}

int BSplineCurve::GetControlPointNum()
{
    return this->control_point_num;
}

int BSplineCurve::GetBaseDegree()
{
    return this->base_degree;
}

KnotIntervalType BSplineCurve::GetKnotIntervalType()
{
    return this->type;
}

