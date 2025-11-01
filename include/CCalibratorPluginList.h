/*
 *  CCalibratorPluginList.h
 *  MyPlugInTester
 *
 *  Created by Ben Guthro on Mon Apr 25 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 */
#ifndef __CCALIBRATORPLGINLIST_H__
#define __CCALIBRATORPLGINLIST_H__

#include "CCalibratorList.h"
class CCalibratorPluginList
{
protected:
	char pth[1024]; //!< the path to plugins
public:
	CCalibratorPluginList();
	virtual ~CCalibratorPluginList();
	
	list <CGenericCalibrator*> m_List;
	inline int GetNCalibrators() {return m_List.size();}
	
	virtual bool Init();	// Do whatever is necessary on initialization
	virtual void Cleanup(); // call at end to ripple through and delete all entries
};

#endif