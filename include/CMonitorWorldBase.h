// CMonitorWorldBase base class
// This class serves as a base for platform-specific derived classes
// to contain all information about the display adapters and monitors.

#ifndef CMONITORWORLDBASE_H_INCLUDED
#define CMONITORWORLDBASE_H_INCLUDED
#include <list>
using namespace std;

#include "CDisplayAdapter.h"
#include "CVesaMonitor.h"

class CMonitorWorldBase
{
public:
	CMonitorWorldBase();
	virtual ~CMonitorWorldBase();
	
	list <CDisplayAdapter*> m_DisplayAdapterList;
	inline int GetNDisplayAdapters() { return m_DisplayAdapterList.size();}

	list <CVesaMonitor*> m_MonitorsOnDesktop;
	inline int GetNMonitorsOnDesktop() {return m_MonitorsOnDesktop.size();}

	virtual bool Init() = 0;	// Inventory display adapter(s) and monitor(s)
	virtual void Cleanup();		 // call at end to ripple through and delete all entries

	// Get CVesaMonitor associated with enable cable #x
	virtual CVesaMonitor* GetMonitorFromECable(short eCableNumber);

	// Get all active CVesaMonitor objects
	virtual void GetActiveMonitors(list <CVesaMonitor*>&);

	// Get CVesaMonitors associated with the current desktop
	virtual void GetMonitorsOnDesktop();

	virtual list<CVesaMonitor*>& GetListOfMonitorsOnDesktop() {return m_MonitorsOnDesktop;}

	// Return a CVesaMonitor for a screen location.
	CVesaMonitor* GetMonitorFromPoint(long x, long y);

	// Return a list of CVesaMonitors of a specific model type.
	// Defined here and returns false unless overridden in derived class.
	virtual bool GetMonitorsOfSpecificModel (char *, list<CVesaMonitor*>*) {return false;} 

	// Return a list of CVesaMonitors with device name matching (or partially
	// matching) passed in string. These must be marked as "on desktop".
	virtual bool GetMonitorsMatchingDeviceName (char *, list<CVesaMonitor*>*) {return false;} 
	
	// Generate a diagnostic file about the system state
	virtual bool GenerateDisplayDiagnostics(char* filename);
};
#endif
