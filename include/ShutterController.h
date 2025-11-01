#pragma once
class CShutterController
{
public:
	virtual int OpenController() = 0; ;// To force as abstract class
	virtual int CloseController()=0;
	virtual int OpenShutter()=0;
	virtual int CloseShutter()=0;
	virtual bool isOpen() {return m_bIsOpen;}

protected:
	bool m_bIsOpen;
};