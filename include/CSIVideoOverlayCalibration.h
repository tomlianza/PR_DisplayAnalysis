#ifndef CSIVIDEOOVERLAYCALIBRATION_H_INCLUDED
#define CSIVIDEOOVERLAYCALIBRATION_H_INCLUDED

#include "CSIVideoOverlayATI.h"
#include "CSequelCalibrator.h"
#include "Measurementset.h"
#include "LimitSingleInstance.h"
#include "CSIRegisterAccessATI.h"

class CSIVideoOverlayCalibration
{
public:
	CSIVideoOverlayCalibration();
	virtual ~CSIVideoOverlayCalibration();
	virtual void PrintMeasurements (sicmMeasurementSet *ms, char *name);
	virtual void ComputeAndAdjust();
	virtual void TakeMeasurements (sicmMeasurementSet *ms);
	virtual int InitializeSettings();
	inline SetCalibrator(CGenericCalibrator *cal) {m_cal = cal;}
	virtual bool GetGammaSettings (ATI_GAMMA_ARRAY *g, bool fromDevice=true);
	virtual bool SetGammaSettings (ATI_GAMMA_ARRAY *g, bool toDevice=true);
	virtual bool SaveValuesToDisk();
	virtual bool GetValuesFromDisk();
	virtual bool RewriteRegs(bool allRegs=false);
	virtual void SetPosition(int x, int y, int w, int h);
	CLimitSingleInstance *m_SingleInstanceObject;

public:
	CSIVideoOverlayATI *o1;
	int m_w, m_h, m_x, m_y;
	CGenericCalibrator *m_cal;
	CSIRegisterAccessATI g_regs;

};
#endif