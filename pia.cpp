#include"PiaBSplineCurve.h"
#include<iostream>

int main()
{
    
    BSplineCurve bsc(4,nonuniform);
    bsc.InsertControlPoint(1,1,0);
    bsc.InsertControlPoint(1,1,0);
    bsc.InsertControlPoint(10,5,6);
    bsc.InsertControlPoint(3,8,7);
    bsc.InsertControlPoint(10,10,8);
    bsc.InsertControlPoint(8,9,12);
    bsc.InsertControlPoint(12,5,15);
    bsc.InsertControlPoint(4,1,17);
    bsc.InsertControlPoint(4,1,17);
    //std::cout<<"number of control points:"<<bsc.GetControlPointNum()<<std::endl;
    bsc.PrintControlPoint();
    //std::cout<<"type of knot vector:"<<bsc.GetKnotIntervalType()<<std::endl;
    //std::cout<<"base rank:"<<bsc.GetBaseRank()<<std::endl;
    bsc.PrintCurve(1);
    

    char file_path[]="/home/jack/Documents/codes/computer_graphics/PIA-master/1.txt";
    PiaBSplineCurve pia;
    pia.ReadControlPointData(file_path);
    pia.PrintControlPoint();
    pia.PIA(1);
    

    return 0;
}
