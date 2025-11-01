#ifndef CDDCQUALIFIERAPPBASE_H_DEFINED
#define CDDCQUALIFIERAPPBASE_H_DEFINED

#include "DataPersistance.h"
#include "CMonitorWorld.h"
#include "dataLogging.h"

class CDDCQualifierAppBase
{
public:
	CDDCQualifierAppBase();
	virtual ~CDDCQualifierAppBase();

	bool GenerateScreenReport();
	virtual bool AddStringToReport (char *) = 0;
	virtual void SetReportPath (char *path, char *realPath=NULL);
	CMonitorWorld w;
	char m_reportPath[512];
	char m_realPath[512];
};
#endif