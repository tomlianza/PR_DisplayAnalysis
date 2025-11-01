#ifndef CCALIBRATIONCOMBO_H_INCLUDED
#define CCALIBRATIONCOMBO_H_INCLUDED
#include "CVesaMonitor.h"
#include "CGenericCalibrator.h"

class CsicmProcesses;

#include "CCalTargetDisplay.h"
	
typedef enum {
	CALIBRATOR_SUPPORT_STATUS_NO_MONITOR,
	CALIBRATOR_SUPPORT_STATUS_NO_CALIBRATOR,
	CALIBRATOR_SUPPORT_STATUS_SUPPORTED,
	CALIBRATOR_SUPPORT_STATUS_NOT_SUPPORTED
	} CALIBRATOR_SUPPORT_STATUS;

class CVesaMonitor;

class CCalibrationCombo
{
public:
	CCalibrationCombo();
	CCalibrationCombo(CVesaMonitor* mon, CGenericCalibrator* cal, CCalTargetDisplay* target, CDSDB* cdsdb);

	virtual ~CCalibrationCombo();

	CVesaMonitor		*m_Monitor;
	CGenericCalibrator	*m_Calibrator;
	CCalTargetDisplay	*m_CalTargetDisplay;
	CDSDB				*m_CDSDB;
	CsicmProcesses		*m_SICM;

	void SetCalibrator(CGenericCalibrator *cal) {m_Calibrator = cal;}
	void SetCalTargetDisplay(CCalTargetDisplay *target) {m_CalTargetDisplay = target;}
	void SetMonitor(CVesaMonitor *mon) {m_Monitor = mon;}
	void SetCDSDB(CDSDB* cdsdb) {m_CDSDB = cdsdb;}

	CALIBRATOR_SUPPORT_STATUS CalibratorSupportsMonitorType();

	CVesaMonitor*		GetMonitor() {return m_Monitor;}
	CGenericCalibrator*	GetCalibrator() {return m_Calibrator;}
	CCalTargetDisplay*	GetCalTargetDisplay() {return m_CalTargetDisplay;}
	CDSDB*				GetCDSDB() {return m_CDSDB;}
	CsicmProcesses*		GetSICM() {return m_SICM;}
	void				SetSICM(CsicmProcesses* sicm) {m_SICM = sicm;}
};
#endif
