#ifndef __SICMUTILS_H__
#define __SICMUTILS_H__

bool CheckRatioCoarse(dRGB ratio);
bool CheckRatioCoarse(double ratio);
bool CheckRatioFine(dRGB ratio);
int CalcBrightnessIncrement(double ratio);
int CalcBiasIncrement(double ratio);
void LogMessage(char *msg);

#ifdef SMART_BLACK
double
DoubleABS(double x);
#endif
#endif
