#ifndef __SICMPAPERWHITE_H__
#define __SICMPAPERWHITE_H__

class CsicmProcesses;

extern int  MeasurePaperWhite(CsicmProcesses *Process, dYxy *YxyMeasurement);
extern void GetPaperWhiteRGB(dYxy YxyMeasurement, dRGBColor *RGB);

#endif
