#include "CCirrusCalibrator.h"
#include "CirrusMonSDK.h"

#define HUEY_PRO_ID_BYTE 0

class CPrivateCirrusCalibrator  : public CCirrusCalibrator
{
public:
	CPrivateCirrusCalibrator();
	virtual ~CPrivateCirrusCalibrator();

	long ReadCirrusIDByte(unsigned char *data);
	long WriteCirrusIDByte(unsigned char data);
	bool IsHueyPro();

};