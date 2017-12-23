#include"BSplineCurve.h"
#include<iostream>

int main()
{
    BSplineCurve bsc;
    bsc.InsertControlPoint(1,1,1);
    bsc.InsertControlPoint(2,2,2);
    std::cout<<bsc.GetControlPointNum()<<std::endl;
    bsc.PrintControlPoint();
    std::cout<<bsc.GetKnotIntervalType()<<std::endl;
    std::cout<<bsc.GetBaseDegree()<<std::endl;   
    return 0;
}
