#ifndef CDISPLAYADAPTERBASE_H_INCLUDED
#define CDISPLAYADAPTERBASE_H_INCLUDED
#include <list>
using namespace std;

class CVesaMonitor;

class CDisplayAdapterBase
{
public:
	CDisplayAdapterBase();
	virtual ~CDisplayAdapterBase();

	list <CVesaMonitor*> m_VesaMonitorList;
	inline int GetNVesaMonitors() {return m_VesaMonitorList.size();}
	
	virtual bool Init();	// Do whatever is necessary on initialization
	virtual void Cleanup(); // call at end to ripple through and delete all entries

	virtual char *GetDeviceName() {return "<adapter name not supported>";}

	// Override the following if we want to do something different for printing.
	virtual char *GetDeviceNameForPrinting() {return GetDeviceName();}

        // Make this system independant
        virtual char *GetDeviceString() { return GetDeviceName(); }

	virtual bool SupportsVideoOverlay() {return false;}
};
#endif
