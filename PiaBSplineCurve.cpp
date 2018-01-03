#include"PiaBSplineCurve.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>

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

        int num=PIA_Curve->GetControlPointNum();
        initial_control_point=new double[num][3];
        for(int i=0;i<num;++i)
        {
            PIA_Curve->GetControlPoint(i);
            initial_control_point[i][0]=PIA_Curve->temp_point[0];
            initial_control_point[i][1]=PIA_Curve->temp_point[1];
            initial_control_point[i][2]=PIA_Curve->temp_point[2];
        }
    }
}

void PiaBSplineCurve::PrintControlPoint()
{
    PIA_Curve->PrintControlPoint();
    std::cout<<"initial control point:"<<std::endl;
    for(int i=0;i<PIA_Curve->GetControlPointNum();++i)
    {
        std::cout<<initial_control_point[i][0]<<","<<initial_control_point[i][1]<<","<<initial_control_point[i][2]<<std::endl;
    }
    std::cin.get();
}

void PiaBSplineCurve::PIA(int segmentation_num)
{
    double x1,y1,z1,x2,y2,z2;
    PIA_Curve->GenerateKnotVector(); 
    PIA_Curve->PrintCurve(segmentation_num);
    std::cin.get();

    do
    {
        delta=0;
        for(int i=2;i<=PIA_Curve->GetControlPointNum()-3;++i)
        {
            PIA_Curve->GetControlPoint(i);
            x1=PIA_Curve->temp_point[0];
            y1=PIA_Curve->temp_point[1];
            z1=PIA_Curve->temp_point[2];
            PIA_Curve->CalculateCurvePoint(PIA_Curve->GetKnotVector(i+2));
            x2=PIA_Curve->temp_point[0];
            y2=PIA_Curve->temp_point[1];
            z2=PIA_Curve->temp_point[2];

            std::cout<<"initial control point:"<<initial_control_point[i][0]<<","<<initial_control_point[i][1]<<","<<initial_control_point[i][2]<<std::endl;
            std::cout<<"current control point:"<<x1<<","<<y1<<","<<z1<<std::endl;
            std::cout<<"current curve point:"<<x2<<","<<y2<<","<<z2<<std::endl;

            double temp=sqrt(pow(x2-initial_control_point[i][0],2)+pow(y2-initial_control_point[i][1],2)+pow(z2-initial_control_point[i][2],2));
            if(temp>delta)
                delta=temp;

            PIA_Curve->ModifyControlPoint(i,x1+initial_control_point[i][0]-x2,y1+initial_control_point[i][1]-y2,z1+initial_control_point[i][2]-z2);
        }
        PIA_Curve->PrintCurve(segmentation_num);
        std::cout<<" max difference is "<<delta<<std::endl;
        std::cin.get();
    }while(delta>PIA_ERR);
    std::cout<<"max difference is "<<delta<<std::endl;
}
