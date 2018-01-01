#include"BSplineCurve.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>

void BSplineCurve::PrintControlPoint()
{
    for(int i=0;i<this->control_point_num;++i)
    {
        std::cout<<control_point[i]<<","<<control_point[B_SPLINE_CURVE_MAX_CONTROL_POINT+i]<<","<<control_point[2*B_SPLINE_CURVE_MAX_CONTROL_POINT+i]<<std::endl;
    }
    std::cout<<"totally "<<control_point_num<<" control points"<<std::endl;
}

void BSplineCurve::InsertControlPoint(double x,double y,double z)
{
    if(this->control_point_num<B_SPLINE_CURVE_MAX_CONTROL_POINT)
    {
        control_point[control_point_num]=x;
        control_point[B_SPLINE_CURVE_MAX_CONTROL_POINT+control_point_num]=y;
        control_point[2*B_SPLINE_CURVE_MAX_CONTROL_POINT+control_point_num]=z;
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





int BSplineCurve::GetBaseRank()
{
    return this->base_rank;
}

void BSplineCurve::SetBaseRank(int base_rank)
{
	this->base_rank=base_rank;
}



//Knot interval type:uniform,non-uniform,quasi_uniform
KnotIntervalType BSplineCurve::GetKnotIntervalType()
{
    return this->type;
}

void BSplineCurve::SetKnotIntervalType(KnotIntervalType type)
{
	this->type=type;
}

void BSplineCurve::GenerateKnotVector()
{
    if(uniform==this->type)
    {
        this->GenerateUniformKnotVector();
        PrintKnotVector();
    }
    else if(nonuniform==this->type && 4==base_rank)
    {
        this->GenerateNonUniformKnotVector();
        PrintKnotVector();
    }
    else if(quasiuniform==this->type)
    {
        this->GenerateQuasiUniformKnotVector();
        PrintKnotVector();
    }
    else
    {
        std::cout<<"no match for knot vector type:"<<this->type<<std::endl;
        exit(0);
    }
}

//Fix uniform knot vector to t[0]=0,t[1]=1,...,t[base_rank+control_point_num-1]=base_rank+control_point_num-1
void BSplineCurve::GenerateUniformKnotVector()
{
    //t[0],t[1],...,t[num]
    
    //base_rank=base_degree+1;knot_point_num=base_rank+1;
    knot_vector_num=base_rank+control_point_num;
    knot_vector=new double[knot_vector_num];
    flag_knot_vector=true;
    for(int i=0;i<base_rank+control_point_num;++i)
    {
	knot_vector[i]=i;
    }
}

void BSplineCurve::GenerateQuasiUniformKnotVector()
{
    knot_vector_num=base_rank+control_point_num;
    knot_vector=new double[knot_vector_num];
    flag_knot_vector=true;
    for(int i=0;i<base_rank;++i)
    {
        knot_vector[i]=0;
    }
    for(int i=base_rank;i<=control_point_num;++i)
    {
        knot_vector[i]=i-base_rank+1;
    }
    for(int i=control_point_num+1;i<base_rank+control_point_num;++i)
    {
        knot_vector[i]=knot_vector[control_point_num];
    }
}

//special case for PIA: base rank = 4
void BSplineCurve::GenerateNonUniformKnotVector()
{
    knot_vector_num=base_rank+control_point_num+2;
    knot_vector=new double[knot_vector_num];
    flag_knot_vector=true;

    double accumulator=0;
    for(int i=0;i<base_rank;++i)
    {
        knot_vector[i]=0;
    }
    for(int i=base_rank;i<=control_point_num+2;++i)
    {
        accumulator+=sqrt(
                             pow(control_point[i-base_rank+1]-control_point[i-base_rank],2)
                            +pow(control_point[B_SPLINE_CURVE_MAX_CONTROL_POINT+i-base_rank+1]-control_point[B_SPLINE_CURVE_MAX_CONTROL_POINT+i-base_rank],2)
                            +pow(control_point[2*B_SPLINE_CURVE_MAX_CONTROL_POINT+i-base_rank+1]-control_point[2*B_SPLINE_CURVE_MAX_CONTROL_POINT+i-base_rank],2)
                         );
        knot_vector[i]=accumulator;
    }
    for(int i=control_point_num+3;i<=base_rank+control_point_num+1;++i)
    {
        knot_vector[i]=knot_vector[control_point_num+2];
    }
}

void BSplineCurve::GenerateCurvePoint(int segmentation_num)
{
    //curve_point[cursor]
    int cursor=0;

    //delta=interval_length/segmentation_num
    double delta;

    //the x,y,z coordinates are stored in fixed locations in the array curve_point[] seperately,
    //x starts from curve_point[0], y starts from curve_point[offset], and z starts from curve_point[2*offset]
    int offset=B_SPLINE_CURVE_MAX_CURVE_POINT;

    //std::cout<<"base rank:"<<base_rank<<std::endl;
    //std::cout<<"number of control points:"<<control_point_num<<std::endl;

    //curve interval:[t[base_rank-1],t[control_point_num]];
    //the intervals [t[0],t[base_rank-1]] and [t[control_point_num],t[base_rank+control_point_num-1]]
    //will not be used because in those two intervals the curve is not fully supported;
    for(int i=base_rank-1;i<control_point_num;++i)
    {
        delta=(knot_vector[i+1]-knot_vector[i])/segmentation_num;
        //std::cout<<"delta:"<<delta<<std::endl;
	for(int j=0;j<segmentation_num;++j)
	{
            //first calculate the value of the argument t[cursor];
	    curve_point[cursor]=knot_vector[i]+j*delta;	
            //std::cout<<"curve point argument:"<<curve_point[cursor]<<std::endl;		
			
	    ++cursor;
	}
    }
    //std::cout<<"cursor:"<<cursor<<std::endl;


    //memory allocated for iteration
    double *temp=new double[base_rank*3];
    int p=base_rank-1;
    //std::cout<<"curve point:"<<std::endl;

    for(int i=0;i<cursor;++i)
    {
        int k=i/segmentation_num+base_rank-1;

	for(int j=0;j<base_rank;++j)
	{
            temp[j]=control_point[j+k-p];
	    temp[j+base_rank]=control_point[j+k-p+B_SPLINE_CURVE_MAX_CONTROL_POINT];
	    temp[j+2*base_rank]=control_point[j+k-p+2*B_SPLINE_CURVE_MAX_CONTROL_POINT];
            //std::cout<<"temp["<<j<<"]:"<<temp[j]<<","<<temp[j+base_rank]<<","<<temp[j+2*base_rank]<<std::endl;
	}   
	for(int r=1;r<base_rank;++r)
	{
            for(int j=base_rank-1;j>=r;--j)
	    {
		double alpha=(curve_point[i]-knot_vector[j+k-p])/(knot_vector[j+1+k-r]-knot_vector[j+k-p]);
                temp[j]=(1-alpha)*temp[j-1]+alpha*temp[j];
		temp[j+base_rank]=(1-alpha)*temp[j-1+base_rank]+alpha*temp[j+base_rank];
		temp[j+2*base_rank]=(1-alpha)*temp[j-1+2*base_rank]+alpha*temp[j+2*base_rank];
	    }
	}
	curve_point[i]=temp[p];
	curve_point[i+cursor]=temp[p+base_rank];
	curve_point[i+2*cursor]=temp[p+2*base_rank];
	/*************************************************************************************************/
        /*************************************************************************************************
        //draw();
        double max=17;
        if(i>0)
        {
            glBegin(GL_LINES);
        
            glVertex3f(curve_point[i-1]/max,curve_point[i-1+cursor]/max,curve_point[i-1+2*cursor]/max);
            glVertex3f(curve_point[i]/max,curve_point[i+cursor]/max,curve_point[i+2*cursor]/max);

            glEnd();
        }
        *************************************************************************************************/
        /*************************************************************************************************/
	std::cout<<curve_point[i]<<","<<curve_point[i+cursor]<<","<<curve_point[i+2*cursor]<<std::endl;
    }

    delete []temp;
}

void BSplineCurve::PrintCurve(int segmentation_num)
{
	if(segmentation_num>B_SPLINE_CURVE_MAX_SEGMENTATION || segmentation_num<=0)
	{
		std::cout<<"segmentation number incorrect!"<<std::endl;
		return;
	}
        if(true!=flag_knot_vector)
	{
		this->GenerateKnotVector();
	}

	this->GenerateCurvePoint(segmentation_num);
}

void BSplineCurve::CalculateCurvePoint(double t)
{
/*  if(true!=flag_knot_vector)
    {
		std::cout<<"must generate curve vector before calculating curve points"<<std::endl;
		return;
	}*/



}

void BSplineCurve::PrintKnotVector()
{
    if(true==this->flag_knot_vector)
    {
        std::cout<<"knot vector=["<<std::endl;
        for(int i=0;i<knot_vector_num;++i)
        {
            std::cout<<knot_vector[i]<<","<<std::endl;
        }
        std::cout<<"]"<<std::endl;
    }
    else
        std::cout<<"have not generated knot vector yet"<<std::endl;
}

