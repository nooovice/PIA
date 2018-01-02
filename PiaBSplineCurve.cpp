#include"PiaBSplineCurve.h"
#include<iostream>
#include<fstream>
#include<cstdlib>

//repeat start point and end point
void PiaBSplineCurve::ReadControlPointData(char *file_path)
{
    //std::cout<<"please input file path:"<<std::endl;
    std::ifstream data;
    data.open(file_path,std::ios::in);
    if(!data.is_open())
    {
        std::cout<<"can not open file"<<std::endl;
        exit(0);
    }
    else if(data.peek()==EOF)
    {
        std::cout<<"empty file"<<std::endl;
        exit(0);
    }
    else
    {
        double x,y,z;
        while(!data.eof())
        {
            data>>std::ws;
            if(data.peek()==EOF) break;
            data>>x>>y>>z;
            PIA_Curve->InsertControlPoint(x,y,z);
            if(1==PIA_Curve->GetControlPointNum())
            {
                PIA_Curve->InsertControlPoint(x,y,z);
            }
        }
        data.close();
        PIA_Curve->InsertControlPoint(x,y,z);
    }
}

void PiaBSplineCurve::PIA()
{
    PIA_Curve->PrintControlPoint();
}
