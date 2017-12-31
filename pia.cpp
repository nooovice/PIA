#include"BSplineCurve.h"
#include<iostream>

int main()
{
    BSplineCurve bsc;
    bsc.InsertControlPoint(1,1,0);
    bsc.InsertControlPoint(4,5,6);
	bsc.InsertControlPoint(3,8,7);
    std::cout<<bsc.GetControlPointNum()<<std::endl;
    bsc.PrintControlPoint();
    std::cout<<bsc.GetKnotIntervalType()<<std::endl;
    std::cout<<bsc.GetBaseRank()<<std::endl;
	bsc.GenerateKnotVector();
    bsc.PrintCurve(10);
    return 0;
}
