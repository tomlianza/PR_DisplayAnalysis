#ifndef CSIVIDEOOVERLAY_H_INCLUDED
#define CSIVIDEOOVERLAY_H_INCLUDED

#include <dshow.h>

class CSIVideoOverlay
{
public:
	CSIVideoOverlay();
	virtual ~CSIVideoOverlay();

public:
	virtual void Init();
	virtual void SetPosition (long x, long y);
	virtual void SetPosition (long x, long y, long w, long h);
	virtual bool SetCaption (unsigned short *caption);
	virtual bool SetFile (unsigned short *filename);
	virtual bool Start();
	virtual bool Stop();
	virtual void SetFullScreen (bool full);

protected:
	IGraphBuilder *pGraph;
    IMediaControl *pControl;
    IMediaEvent   *pEvent;
	IVideoWindow *pVW;

	HRESULT hr;
};
#endif