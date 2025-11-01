/*
 *
 *  Created by Ben Guthro on Mon Jan 26 2004.
 *  Copyright (c) 2004 SequelImaging. All rights reserved.
 *
 */

#ifndef __CNECDDCCICONTROLLER_H_DEFINED
#define __CNECDDCCICONTROLLER_H_DEFINED

#include "CMacDDCCIController.h"
#include "CDigitalController.h"

class CNECDDCCIController : public CMacDDCCIController
{
private:
	BYTE m_VCPPageNumber;		//which page
public:
	CNECDDCCIController(CVesaMonitor *mon = NULL);
	//Support for storing LUTs in the display
	//these will always be represented in float format 0.0-1.0
	//until we get to the storage in the hardware
	virtual bool SupportsDisplayHardwareLUT(){ return true; }
	virtual bool GetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);
	virtual bool SetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);
	
	
	virtual BYTE GetVCPPage(){ return m_VCPPageNumber; }
	virtual void SetVCPPage(BYTE b){ m_VCPPageNumber = b; }
	
	//use paged VCP results
	virtual short SetVCPFeatureUtil(VESAMonitorContext device, DMC_CONTROL VCP, short sSetVal);
	virtual short LoGetVCPFeatureUtil (VESAMonitorContext *device, DMC_CONTROL VCP, short *sMax, short *sCurrent,short *sStatus, int usToWait);

};

#endif
