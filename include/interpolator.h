//interpolator.h
//#include "stdafx.h"

#if !defined(_INTERPOLATOR_)
	#define _INTERPOLATOR_
// define this to re-enable the interpolator output
// _DATADUMP is now in the h file
//#define _DATADUMP

#ifdef  _DATADUMP   
#define INTERPOLATOR_FILE "InterpolatorData.txt"
#endif

typedef enum {

	I_LINEAR = 0,
	I_SPLINE,
	I_NTYPES
}I_TYPE;

typedef enum {
	I_OK = 0,
	I_NO_INIT,
	I_WRONG_TYPE,
	I_DIVIDE_BY_ZERO,
	I_SLOPES_OFFSETS_VALID,
	I_RANGE_ERROR,
	I_NSTATUS
}I_STATUS;

class CInterpolator 
{

public:

	CInterpolator();
	~CInterpolator();
	
	double		*m_x;

	double		*m_y;
	double		m_dOut;
	short		m_npts;

	I_TYPE		m_whichType;
	I_STATUS	m_currentStatus;
	double GetInterpolatedValue(double dx);
    int Init();

private:

	double		*m_pSlopes;
	double		*m_pOffsets;
	double		*m_derivs;

	double		*m_lx; // Local copy of x values
	double		*m_ly; // Local copy of y values
	
	void		SmoothX();

	//for spline fitting
	void spline(double *x, double *y, unsigned short n, double ypi, double ypn, double *y2);
	bool splint(double *xa, double *ya, double *y2a, unsigned short n, double x, double *y);
};
#endif
