/*
 *  CMCCSController.h
 *  ProColor
 *
 *  Created by Ben Guthro on Mon Aug 22 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *  
 *  a virtual class to control DDC protocol MCCS spec 2.1
 */
#ifndef __CMCCSCONTROLLER_H__
#define __CMCCSCONTROLLER_H__
#include "CDigitalController.h"

class CMCCSController : public CDigitalController
{
public:
	CMCCSController();
	virtual ~CMCCSController(){};
	virtual DDC_CONTROLLER_STATUS SupportsDDC(VESAMonitorContext device) { return FULL_SUPPORT;}
	virtual bool SupportsDisplayHardwareLUT(VESAMonitorContext cp);
	virtual bool GetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);
	virtual bool SetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize);

protected:
	bool	m_lutProbed,m_iLutSupported;
};
#endif

