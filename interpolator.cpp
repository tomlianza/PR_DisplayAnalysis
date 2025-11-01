//CInterpolator.cpp
#include "stdafx.h"
#include "interpolator.h"
#include "stdio.h"
//#include "DataPersistance.h"

// define this to re-enable the interpolator output
// _DATADUMP is now in the h file


int numC=0;
int numD=0;
int numI=0;
#define nearzero 1.0E-20

#define D_MULT 10000

CInterpolator::CInterpolator()
{
	m_x = NULL;
	m_y = NULL;
	m_derivs = NULL;
	
	m_dOut = -1;
	m_npts = 0;
	m_pSlopes = NULL;
	m_pOffsets = NULL;

	#ifndef USES_SPLINE_INTERP
	m_whichType = I_LINEAR;
	#else
	m_whichType = I_SPLINE;
	#endif
	m_currentStatus = I_NO_INIT; 
	numC++;	
}
CInterpolator::~CInterpolator()
{
	if(m_pSlopes != NULL) delete[] m_pSlopes;
	if(m_pOffsets != NULL) delete[] m_pOffsets;
	if(m_derivs != NULL) delete[] m_derivs;
	numD++;
}
int CInterpolator::Init()
{
	numI++;
	short i;

	if (!m_pSlopes)
		m_pSlopes = new double[m_npts];

	if (!m_pOffsets)
		m_pOffsets = new double[m_npts];
	
	if(!m_derivs)
		m_derivs = new double[m_npts];
				

	SmoothX();
	switch (m_whichType)
	{
		

	case I_LINEAR:
		{
			
			
			for(i=0; i<m_npts -1 ; i++)
			{
				if((m_x[i+1] - m_x[i])==0)
				{
					m_currentStatus = I_DIVIDE_BY_ZERO;
					delete[] m_pSlopes;
					delete[] m_pOffsets;
					m_pSlopes = NULL;
					m_pOffsets = NULL;
					m_npts = 0;
					return(1);
					
				}
				else
				{
					m_pSlopes[i] = (m_y[i+1] - m_y[i])/(m_x[i+1] - m_x[i]);
					m_pOffsets[i] = m_y[i];
					m_currentStatus = I_SLOPES_OFFSETS_VALID;
				}
				
			}
#ifdef _DATADUMP
			#ifdef OS9_DRIVER
			FILE *fp = FSOpenInSpec(INTERPOLATOR_FILE, getWorkingDir(), "a");
			#else
			FILE *fp = fopen(INTERPOLATOR_FILE,"a");
			#endif
			if (!fp)
				break;
			for(i= 0; i<m_npts-1; i++)
				fprintf(fp,"%d\t%10.5f\t%10.5f\n", i, m_pSlopes[i], m_pOffsets[i]);
			
			fprintf(fp,"\n\n");
			
			fclose (fp);
#endif
			
			
		}
		break;
	case I_SPLINE:
		{
			//normalize x
			
			//calc zeroth prime
			double ypz = (m_y[1]-m_y[0])/(m_x[1]-m_x[0]);
			
			//calc n prime
			double ypn = (m_y[m_npts-1]-m_y[m_npts-2])/(m_x[m_npts-1]-m_x[m_npts-2]);
			spline(m_x, m_y, m_npts, ypz, ypn, m_derivs);
			
			m_currentStatus = I_SLOPES_OFFSETS_VALID;

		}
		break;
		
	default: 
		m_currentStatus = I_WRONG_TYPE;
		break;
		
	}
	
	return(0);	
}
double CInterpolator::GetInterpolatedValue(double dx )
{
	short i;
	m_dOut = -1;
	
	switch (m_whichType)
	{
		case I_LINEAR:
		{
			for(i=0; i< m_npts-1; i++)
			{
				if((dx >= m_x[i]) && (dx <= m_x[i+1]))
				{
					m_dOut = m_pSlopes[i]*(dx-m_x[i]) + m_pOffsets[i]; 
					m_currentStatus = I_OK;
					return (m_dOut);
				}
				m_dOut = m_pSlopes[i]*(dx-m_x[i]) + m_pOffsets[i];
				
			}
			m_currentStatus = I_RANGE_ERROR;
		break;
		}
		
		case I_SPLINE:
		{
			if(splint(m_x, m_y, m_derivs, m_npts, dx, &m_dOut)){
				m_currentStatus = I_OK;
				return (m_dOut);
			}
			break;
		}
	
		default:
		m_currentStatus = I_RANGE_ERROR;
		break;
	}
	
	return(m_dOut);
}

void CInterpolator::SmoothX()
{

	short i,last_zero;
	double dxHeight, dSlope; 

	for(i=0; i< m_npts; i++)
		if(m_x[i] < 0) m_x[i] = 0; //zero out all negative values;
	last_zero = 0; 
	for(i=0; i<m_npts; i++)
		if(m_x[i] == 0)last_zero = i;  // this identifies where the last zero in the array was found 

			// if the measurement array never had a negative value this value should be zero. 
	if(last_zero != 0)
	{
		dxHeight = m_x[last_zero + 1];
		dSlope = dxHeight/(last_zero+1);

		for(i= 0; i<=last_zero; i++)
			m_x[i] = i*dSlope;
	}

		

	return ;




}

 // spline stuff
// derived from numerical methods in C (changed from 1 based arrays to 0 based

//
// given arrays x[0..n-1] and y[0..n-1] containing a tabulated function ie y[i] = f(x[i])
// with x[0] < x[1] < ... < x[n-1] and given values ypi and ypn for the first derivative of the interpolating function at points 0 and n-1
// this routine returns an array y[0..n] that contains the 2nd derivatives of the interpolatig function at the tabulated points x[i]
//
// NOTE: this should only be called once - access points with splint

#define SPLINE_BOUNDARY 0.99e30

void CInterpolator::spline(double *x, double *y, unsigned short n, double ypi, double ypn, double *y2)
{
	int i,k;
	double p,qn,sig,un,*u;
	
	u = new double[n+1];
	
	//lower boundary condition
	if(ypi>SPLINE_BOUNDARY){
		y2[0]=u[0]=0.0;
	}else{
		y2[0] = -0.5;
		u[0] = (3.0/(x[1]-x[0])) * ( (y[1]-y[0])/(x[1]-x[0])-ypi);
	}
	
	//this is the decomposition loop for the tridiag algorithm
	// y2 and u are used for the them storage of decomposed factors
	for(i=1;i<n;i++)
	{
		sig = (x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p = sig*y2[i-1]+2.0;
		y2[i] = (sig-1.0)/p;
		u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;
	}
	
	//upper boundary condition
	if(ypn>SPLINE_BOUNDARY){
		qn=un=0.0;  //natural
	}else{
		qn=0.5;
		un=(3.0/(x[n-1]-x[n-2]))*(ypn-(y[n-1]-y[n-2])/(x[n-1]-x[n-2])); //first derivative
	}
	
	y2[n-1]=(un-qn*u[n-2])/(qn*y2[n-2]+1.0);
	
	//backsubstitution loop for tridiagonal algorithm
	for(k=n-2;k>=0;k--){
		y2[k]=y2[k]*y2[k+1]+u[k];
	}
	
	delete[] u;
}

//spline interpolate (splint)
// given arrays xa[0..n-1] and ya[1..n-1] which tabulate a function (with xa[i] in order
// and given the array y2[0..n-1] which is the output from spline, and given a value for x
// this routine returns the spline interpolated value y
bool CInterpolator::splint(double *xa, double *ya, double *y2a, unsigned short n, double x, double *y)
{
	int klo, khi,k;
	double h,b,a;
	
	//bisection search
	klo = 0;
	khi = n-1;
	
	while(khi-klo > 1){
		k = (khi+klo) >> 1;
		if(xa[k] > x) khi=k;
		else klo=k;
	}
	
	h=xa[khi]-xa[klo];
	if(h==0.0){return false;}
	
	a=(xa[khi]-x)/h;
	b=(x-xa[klo])/h;
	
	//cubic spline polynomial is now evaluated
	*y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
	return true; 
}
