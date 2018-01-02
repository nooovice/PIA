#pragma once
#ifndef B_SPLINE_CURVE_H
#define B_SPLINE_CURVE_H

#define B_SPLINE_CURVE_MAX_CONTROL_POINT 100
#define B_SPLINE_CURVE_MAX_SEGMENTATION 1000
#define B_SPLINE_CURVE_MAX_RANK 10
#define B_SPLINE_CURVE_MAX_CURVE_POINT ((B_SPLINE_CURVE_MAX_CONTROL_POINT+B_SPLINE_CURVE_MAX_RANK-1)*B_SPLINE_CURVE_MAX_SEGMENTATION+1)
//#define B_SPLINE_CURVE_KNOT_VECTOR_START 0
//#define B_SPLINE_CURVE_KNOT_VECTOR_END 1

enum KnotIntervalType{uniform=0,nonuniform=1,quasiuniform=2};

class BSplineCurve
{
private:
    int control_point_num;
    int knot_vector_num;
    int base_rank;
    KnotIntervalType type;
    double* control_point;
    double* curve_point;
    double* knot_vector;

    bool flag_knot_vector;

    void SetBaseRank(int base_rank);
    void SetKnotIntervalType(KnotIntervalType type);
    
    void GenerateKnotVector();
    void GenerateUniformKnotVector();
    void GenerateQuasiUniformKnotVector();
    void GenerateNonUniformKnotVector();
    void GenerateCurvePoint(int segmentation_num);
    void CalculateCurvePoint(double t);

public:
    double temp_point[3];
    

    BSplineCurve(int base_rank=4,KnotIntervalType type=uniform)
    {
        control_point=new double[B_SPLINE_CURVE_MAX_CONTROL_POINT*3];
        control_point_num=0;
        this->base_rank=base_rank;
        this->type=type;
	flag_knot_vector=false;
	curve_point=new double[B_SPLINE_CURVE_MAX_CURVE_POINT*3];
    }
    virtual ~BSplineCurve()
    {
        delete []control_point;
	delete []curve_point;
	if(true==flag_knot_vector) delete []knot_vector;
    }

    void PrintControlPoint();
    void InsertControlPoint(double x,double y,double z);

    //counting from P1,P2,...
    void ModifyControlPoint(int position,double x,double y,double z);

    void GetControlPoint(int position);
    int GetControlPointNum();
    int GetBaseRank();
    KnotIntervalType GetKnotIntervalType();

    void PrintKnotVector();
    void PrintCurve(int segmentation_num);
};

#endif
