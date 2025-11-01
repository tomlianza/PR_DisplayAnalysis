/** Calculate color difference (deltaE) between two color targets using the DE2000 formula.
*	DE2000, taken from CalMAN_DLL
	checked DS 11/15/11
    edited DB 07/31/2018

	@param sample_L double value representing L* of sample color target
	@param sample_a double value representing a* of sample color target
	@param sample_b double value representing b* of sample color target
	@param target_L double value representing L* of target color target
	@param target_a double value representing a* of target color target
	@param target_b double value representing b* of target color target
*/
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define M_PI  3.14159265358979323846
double degreesToRadians(double inDegrees)
{
	return ((M_PI/180)*inDegrees);
};
double radiansToDegrees(double inRadians)
{
	return ((180./M_PI) * inRadians);
};
double DeltaE2000(double sample_L, double sample_a, double sample_b, double target_L, double target_a, double target_b)
{
	double L = (target_L + sample_L) / 2.00;

	double C1 = sqrt(pow(target_a, 2.00) + pow(target_b, 2.00));

	double C2 = sqrt(pow(sample_a, 2.00) + pow(sample_b, 2.00));

	double C = (C1 + C2) / 2.00;

	double G = (1.00 - sqrt(pow(C, 7.00) / (pow(C, 7.00) + pow(25.00, 7.00)))) / 2.00;

	double a1_prime = target_a * (1.00 + G);

	double a2_prime = sample_a * (1.00 + G);

	double C1_prime = sqrt(pow(a1_prime, 2.00) + pow(target_b, 2.00));

	double C2_prime = sqrt(pow(a2_prime, 2.00) + pow(sample_b, 2.00));

	double C_prime = (C1_prime + C2_prime) / 2.00;

	double h1 = radiansToDegrees(atan2(target_b, a1_prime));

	if (h1 < 0)
	{
		h1 += 360;
	}

	double h2 = radiansToDegrees(atan2(sample_b, a2_prime));

	if (h2 < 0)
	{
		h2 += 360;
	}

	double H;

	if (abs(h1 - h2) <= 180.0)
	{
		H = (h1 + h2) / 2.0;
	}
	else if (abs(h1 - h2) > 180 && (h1 + h2) < 360)
	{
		H = (h1 + h2 + 360) / 2.0;
	}
	else if (abs(h1 - h2) > 180 && (h1 + h2) >= 360)
	{
		H = (h1 + h2 - 360) / 2.00;
	}
	else if (C1_prime * C2_prime == 0.0)
	{
		H = h1 + h2;
	}

	double T = 1.00 - 0.17 * cos(degreesToRadians(H - 30)) + 0.24 * cos(degreesToRadians(2.0 * H)) + 0.32 * cos(degreesToRadians(3.0 * H + 6.0)) - 0.20 * cos(degreesToRadians(4.0 * H - 63));

	double dEh;

	if (C1_prime * C2_prime == 0.0)
	{
		dEh = 0.0;
	}
	else if (abs(h2 - h1) <= 180.0)
	{
		dEh = (h2 - h1);
	}
	else if ((h2 - h1) > 180.0)
	{
		dEh = h2 - h1 - 360.0;
	}
	else if ((h2 - h1) < -180.0)
	{
		dEh = h2 - h1 + 360.0;
	}

	if (_finite(dEh))
	{
		dEh = dEh;
	}
	else
	{
		dEh = 0;
	}

	double dEL = sample_L - target_L;

	double dEC = C2_prime - C1_prime;

	double dEH = 2.00 * sqrt(C1_prime * C2_prime) * sin(degreesToRadians(dEh / 2.00));

	double K1 = 0.015;

	double K2 = 0.045;

	double Sl = 1.00 + ((K1 * pow(L - 50.00, 2.00)) / sqrt(20.00 + pow(L - 50.00, 2.00)));

	double Sc = 1.00 + (K2 * C_prime);

	double Sh = 1.00 + (K1 * C_prime * T);

	double Kl = 1.00;

	double Kc = 1.00;

	double Kh = 1.00;

	double dEo = 30.0  * exp(-pow((H - 275.00) / 25.00, 2.00));

	double Rc = 2.0 * sqrt(pow(C_prime, 7.00) / (pow(C_prime, 7.00) + pow(25.00, 7.00)));

	double Rt = -1.00 * Rc *  sin(degreesToRadians(2.00 * dEo));

	double Ln = pow((dEL / (Kl * Sl)), 2.00);

	double Cn = pow((dEC / (Kc * Sc)), 2.00);

	double Hn = pow((dEH / (Kh * Sh)), 2.00);

	double Rn = Rt * (dEC / (Kc * Sc)) * (dEH / (Kh * Sh));

	double dE = sqrt(Ln + Cn + Hn + Rn);

	if (_finite(dE))
	{
		dE = dE;
	}
	else
	{
		dE = 0;
	}

	return dE;
}