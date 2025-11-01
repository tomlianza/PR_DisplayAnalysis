#ifndef _COLOR_STRUCTS_H_INCLUDED
#define _COLOR_STRUCTS_H_INCLUDED

typedef struct {
		double Y;
		double x;
		double y;
		double z;
	}dYxy;
typedef   dYxy YxyColor;

typedef struct {
		double R;
		double G;
		double B;
	}dRGB;
typedef  dRGB dRGBColor ;


typedef struct {
	double X;
	double Y;
	double Z;
	}dXYZ;
typedef  dXYZ  XYZColor;

typedef struct LABColor {
	double L;
	double A;
	double B;
}LABColor;
//typedef dLab LABColor;

typedef struct LuvColor {
	double L;
	double u;
	double v;
}LuvColor;
//u'v' color set
typedef struct LuvPColor {
	double L;
	double up;
	double vp;
}LuvPColor;

typedef struct LUVColor {
	double L;
	double U;
	double V;
}LUVColor;


typedef struct LHCColor {
	double L;
	double H;
	double C;
}LHCColor;

#endif 