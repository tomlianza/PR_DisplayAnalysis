#ifndef __CMACDISPLAYADAPTER_H__
#define __CMACDISPLAYADAPTER_H__
#include "CDisplayAdapterBase.h"
#include "CMacDisplayAdapter.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <ApplicationServices/ApplicationServices.h>
#ifdef __cplusplus
}
#endif

class CDisplayAdapter : public CDisplayAdapterBase
{
private:
	io_service_t	service;
	char* m_DeviceName;

public:
	CDisplayAdapter();
	virtual ~CDisplayAdapter();
	virtual inline char* GetDeviceName(){ return m_DeviceName; }
	virtual void SetDeviceName(char *inName);
	virtual inline void SetDeviceService(io_service_t svc){ service = svc; }
};
#endif