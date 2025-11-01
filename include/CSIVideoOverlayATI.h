#ifndef CSIVIDEOOVERLAYATI_H_INCLUDED
#define CSIVIDEOOVERLAYATI_H_INCLUDED

#include "CSIVideoOverlay.h"

class CSIVideoOverlayATI : public CSIVideoOverlay
{
public:
	CSIVideoOverlayATI() {};
	virtual ~CSIVideoOverlayATI() {}

public:
	bool StartPatch(unsigned short *filename, int x = 0, int y = 0, int w = 400, int h = 400);
	void StopPatch();

private:

};
#endif