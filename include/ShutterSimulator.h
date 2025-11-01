#pragma once
#include "ShutterController.h"

class CShutterSimulator : public CShutterController
{
public:
	CShutterSimulator();
	~CShutterSimulator();
	virtual int OpenController() {return 1;}
	virtual int CloseController() {return 1;}
	virtual int OpenShutter();
	virtual int CloseShutter();
};