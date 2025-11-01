
#ifndef __CMACMONITORWORLD_H__
#define __CMACMONITORWORLD_H__

#define kMaxMacDisplays 8
#include <CMonitorWorldBase.h>

class CMonitorWorld : public CMonitorWorldBase
{
public:
	CMonitorWorld();
	virtual ~CMonitorWorld();

	bool Init();
	void InventoryMonitors();


		// for now, assume we only have 1, we'll need to search the code base
		// for myDisplays and fix the index in all occurances.
	#ifdef OS9_DRIVER
	long myDisplays[kMaxMacDisplays];
	#else
	CGDirectDisplayID myDisplays[kMaxMacDisplays];
	#endif
	
protected:
	int mainMonitorBottom;
	bool initialized;
};

#endif