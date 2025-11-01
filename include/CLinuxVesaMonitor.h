#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#include "siLabels.h"
class CVesaMonitor : public CVesaMonitorBase
{
public:
	
	CVesaMonitor();
	virtual ~CVesaMonitor();
		
	bool SetDeviceLUTs(CSIGammaRamp *gr);
	bool GetDeviceLUTs(CSIGammaRamp *gr);
	bool FormatDSDBFileName(char *name, char *serNo, char *fileName);
	
	Display* display;
   int screen;

   
   void setDisplay(Display *d, int i){ display = d; screen=i; };
#ifdef SUPPORT_MULTIPLE_DSDBS
   	bool WriteSecondaryDSDB();
	bool FindSecondaryDSDBFiles();
	bool MakeDefaultDSDBFile(char *name);
	bool SetPrimaryDSDB(char *sourceName);
#endif

#ifdef USE_GAMMAVAL_FILE
    bool WriteGammaFile(bool beverbose=false);
#endif

#ifdef USE_LUTDATA_FILE
    bool WriteLUTDataFile(bool beverbose=false, GammaRamp *gr=NULL, GammaRampEx *grex=NULL);
#endif
};
