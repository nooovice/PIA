#include"BSplineCurve.h"
#include<iostream>

int main()
{
    BSplineCurve bsc(5,quasiuniform);
    bsc.InsertControlPoint(1,1,0);
    bsc.InsertControlPoint(10,5,6);
    bsc.InsertControlPoint(3,8,7);
    bsc.InsertControlPoint(10,10,8);
    bsc.InsertControlPoint(8,9,12);
    bsc.InsertControlPoint(12,5,15);
    bsc.InsertControlPoint(4,1,17);
    //std::cout<<"number of control points:"<<bsc.GetControlPointNum()<<std::endl;
    bsc.PrintControlPoint();
    //std::cout<<"type of knot vector:"<<bsc.GetKnotIntervalType()<<std::endl;
    //std::cout<<"base rank:"<<bsc.GetBaseRank()<<std::endl;
    bsc.PrintCurve(200);
    return 0;
}
