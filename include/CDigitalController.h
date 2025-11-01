#ifndef CDIGITALCONTROLLER_H_DEFINED
#define CDIGITALCONTROLLER_H_DEFINED

#include "dmc.h"

class CVesaMonitor;


class CDigitalController
{
private:
	short m_DMCOffsets[256];
	DMC_CONTROL m_DMCControlMap[256];
	int m_internalLUTDepth;
	int m_internalLUTChannels;
protected:


public:
	CDigitalController(CVesaMonitor *mon = NULL);
	virtual ~CDigitalController(){};
	virtual char *GetControllerType () {return "<<Base Class>>";}
	virtual bool OpenDevice (VESAMonitorContext *v, short arg);
	virtual bool CloseDevice (VESAMonitorContext *v, short arg);
	virtual short SetVCPFeature(VESAMonitorContext device, DMC_CONTROL VCP,short sSetVal);
	virtual short GetVCPFeatureEx(VESAMonitorContext device,
		DMC_CONTROL VCP, short *sMax, short *sCurrent, short *sStatus);
	virtual bool FindPhotometry(VESAMonitorContext cp, DM_MCCS *Photometry) ;
	virtual bool FindGeometry(VESAMonitorContext cp, DM_MCCS *Geometry) ;
	virtual bool FindImage(VESAMonitorContext cp, DM_MCCS *Image) ;
	virtual short GetEDIDBlock (VESAMonitorContext device, unsigned char ucOffset, unsigned char *ucBlockData );
	virtual void SetMonitorObject(CVesaMonitor *mon);
	virtual short GetCapabilities(VESAMonitorContext device, unsigned char *ucBuf, short *sLength);
	virtual bool IsDigitallyEnabled() {return true;} // Assumed true for all unless overridden.
	virtual bool InitLocalData();

	virtual bool FindDDCPhotometry(VESAMonitorContext cp, DM_MCCS *Photometry);
	virtual bool FindDDCGeometry(VESAMonitorContext cp, DM_MCCS *Geometry);
	virtual bool FindDDCImage(VESAMonitorContext cp, DM_MCCS *Image);
	virtual bool DDC_GetControl (VESAMonitorContext cp, DMC_CONTROL  whichControl, DMC *the_control);
	virtual bool IsSoftwareDDC() { return false;}
	virtual void SetDMCOffset(DMC_CONTROL whichControl, short offset){ m_DMCOffsets[whichControl] = offset; }
	virtual short GetDMCOffset(DMC_CONTROL whichControl){ return m_DMCOffsets[whichControl]; }
	virtual DMC_CONTROL GetMappedControl(DMC_CONTROL c) { return m_DMCControlMap[c];}
	virtual void SetMappedControl(DMC_CONTROL oldVal, DMC_CONTROL newVal) {m_DMCControlMap[oldVal] = newVal;}

	virtual bool SaveMonitorSettings(VESAMonitorContext cp);
	virtual bool EnableOnScreenControls(VESAMonitorContext cp, bool enable);

	virtual bool CanProbeForBrightness() {return false;}
	virtual bool CanProbeForContrast() {return false;}
	virtual bool DefaultBrightnessEnabledValue() {return true;}
	virtual bool DefaultContrastEnabledValue() {return true;}

	virtual void SetInternalLUTDepth (int depth) {m_internalLUTDepth = depth;}
	virtual void SetInternalLUTChannels (int numOfChannels) {m_internalLUTChannels = numOfChannels;}

	virtual int GetInternalLUTDepth () {return m_internalLUTDepth;}
	virtual int GetInternalLUTChannels () {return m_internalLUTChannels;}

	CVesaMonitor *m_monitor;

	// Status values returned from SupportsDDC() call.
	typedef enum {
		NO_DDC,				// Doesn't support DDC at all.
		FULL_SUPPORT,		// No problems found
		FAILED_GET,			// "Get" command failed
		FAILED_SET,			// "Set" command failed
		FAILED_GETRANGE,	// "GetRange" command failed.
		FAILED_OTHER		// Other error. (If returned, we should provide new enumerations.)
	} DDC_CONTROLLER_STATUS;

	
	virtual DDC_CONTROLLER_STATUS SupportsDDC(VESAMonitorContext device) { return NO_DDC;}
	
	//Support for storing LUTs in the display
	//these will always be represented in float format 0.0-1.0
	//until we get to the storage in the hardware
	virtual bool SupportsDisplayHardwareLUT(VESAMonitorContext cp){ return false; }
	virtual bool GetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize){return false;}
	virtual bool SetDisplayHardwareLUT(double *r, double *g, double *b, int inarrsize){return false;}	
};

class CNullController : public CDigitalController
{
public:
	CNullController(CVesaMonitor *mon = NULL) {m_monitor = mon;}
	virtual bool IsDigitallyEnabled() {return false;}
	virtual char *GetControllerType () {return "<<Null Controller>>";}

	virtual bool DefaultBrightnessEnabledValue() {return false;}
	virtual bool DefaultContrastEnabledValue() {return false;}
};

#endif