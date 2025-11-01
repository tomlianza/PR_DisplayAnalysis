#ifndef CSIREGISTERACCESS_H_INCLUDED
#define CSIREGISTERACCESS_H_INCLUDED

#include "TVicHW32.h"

class CSIRegisterAccess
{
public:
	CSIRegisterAccess();
	virtual ~CSIRegisterAccess() {};
	virtual bool OpenDriver();
	virtual void CloseDriver();
	virtual PCI_COMMON_CONFIG *GetHeader(int vid, int pid);
	virtual char *MapMemory(long mmBase, int length);
	virtual void UnmapMemory(long mmBase, int length);

	virtual long GetLong(long base, int offset);
	virtual short GetShort(long base, int offset);
	virtual unsigned char GetByte(long base, int offset);
	virtual bool SetLong(long base, int offset, long value);
	virtual bool SetShort(long base, int offset, short value);
	virtual bool SetByte(long base, int offset, unsigned char value);

protected:
	PCI_COMMON_CONFIG m_cfg;
	bool m_open;
	HANDLE m_hwCtrl;
};
#endif