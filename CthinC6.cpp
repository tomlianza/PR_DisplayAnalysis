// CthinC6.cpp
#include "stdafx.h"
#include "CthinC6.h"


CthinC6::CthinC6()
{

	short i;
	for (i = 0; i < N_EDRS;i++)
	{

		m_EDR_LIST[i].EDR_ENUM = EDRVALUE[i];
		m_EDR_LIST[i].EDR_NAME = EDRNAME[i];

	}
	

		


	



};
bool CthinC6::C6Initialize()
{
	
	m_bInitialized = i1d3Initialize();
	
	m_i1d3Status = i1d3GetDeviceHandle(NULL, &m_devHndl);
	if (m_i1d3Status != i1d3Success) return (false);
	// Override key for C6 
	// unsigned char key[] = {0x20,0x9A,0x50,0xEE,0x40,0x78,0x36,0xFD,0x00,0x00};   // C6 Key
	unsigned char keyE[] = { 0x00,0x50,0x40,0x36,0x00,0x00 };   // C6 Key
	unsigned char keyO[] = { 0x9A,0xEE,0x78,0x00,0x00,0x00 };   // C6 Key
	unsigned char key[256];
	sprintf((char *)key, "%c%c%c%c%c%c%c%c%c", 0x20, keyO[0], keyE[1], keyO[1], keyE[2], keyO[2], keyE[3], 0xFD, 0);
	m_i1d3Status = i1d3OverrideDeviceDefaults(0, 0, key);
	m_i1d3Status = i1d3DeviceOpen(m_devHndl);
	m_i1d3Status = i1d3GetDeviceHandle(NULL, &m_devHndl);
	if (m_i1d3Status != i1d3Success)
	{
		m_cSN[0] = NULL; // no string for serial numbers; 
		m_bInitialized = false;
	}
	else	
	{
		
		m_bInitialized = true;
		C6GetSerialNumber();
		i1d3GetCalibrationList(m_devHndl,  &m_numCals,  &m_calList);
		
	}
		return m_bInitialized;
}

i1d3XYZ_t CthinC6::C6MeasureXYZ()
{
	m_XYZdata.X = -1.0;
	m_XYZdata.Y = -1.0;
	m_XYZdata.Z = -1.0;
	m_i1d3Status = i1d3MeasureXYZ(m_devHndl, &m_XYZdata);
	return(m_XYZdata);

}
bool CthinC6::C6MSetEDRFile(unsigned char * cEDRFilePathsandName)
{

	i1d3Status_t status = i1d3SetCalibrationFromFile(m_devHndl, cEDRFilePathsandName);
	if (status != i1d3Success)
		return(false);
	else
		return(true);
}
bool CthinC6::C6MSetEDR(BYTE*cEDRImage, ULONG ulLength)
{
	i1d3Status_t status = i1d3SetCalibrationFromBuffer(m_devHndl, (unsigned char *)cEDRImage, (int)ulLength);
	if (status != i1d3Success)
		return(false);
	else
		return(true);

};

bool CthinC6::C6Close()
{

	i1d3Destroy();
	return(true);
}
bool CthinC6::C6SetCalibrationEntry()
{
	i1d3Status_t status = i1d3SetCalibration(m_devHndl, &m_currentEntry);
	if(status != i1d3Success)
		return(false);
	else
	return(true);

}

bool CthinC6::C6SetCalibrationEntry(unsigned char * cEDRFilePathsandName, char * key, short DisplayTypeEnum)
{
	CFile cfEDR;
	CFileException cfx;
	cfEDR.Open((char *)cEDRFilePathsandName, CFile::modeRead, &cfx);  // no check for existance here 
	cfEDR.Read(&m_EDRheader, sizeof(EDR_HEADER));
	memset(&m_currentEntry, 0, sizeof(i1d3CALIBRATION_ENTRY));
	m_currentEntry.calSource = CS_USER_SUPPLIED;
	EDR_WriteString(m_currentEntry.fileName, (char *)cEDRFilePathsandName);  // write the file name 
	EDR_WriteString(m_currentEntry.displayName, (char *)m_EDRheader.Model);
	EDR_WriteString(m_currentEntry.displayMfg, (char *)m_EDRheader.Mfg);
	EDR_WriteString(m_currentEntry.displayModel, (char *)m_EDRheader.Model);
	EDR_WriteString(m_currentEntry.key, key);
	m_currentEntry.edrDisplayType = DisplayTypeEnum;
	i1d3Status_t status = i1d3SetCalibration(m_devHndl, &m_currentEntry);
	if (status != i1d3Success)
		return(false);
	else
		return(true);

}
bool CthinC6::C6GetSerialNumber()
{
	char cTextSerialNumber[64];
	char *ptr,*startNum;
	//char cSerialNumber[16];
	
	m_i1d3Status = i1d3GetSerialNumber(m_devHndl, &cTextSerialNumber[0]);// raw text value 
	ptr = strchr(cTextSerialNumber, 0x2e);  // first decimal 
	ptr += 2;
	ptr = strchr(ptr, 0x2e);
	startNum = ++ptr; // advance past decimal point;
	ptr = strrchr(startNum, 0x2e);
	*ptr = NULL; //null terminate the 
	strcpy_s(m_cSN, 16, startNum);

	m_lSN = atol(m_cSN);
	
	return(true);
}

bool CthinC6::C6MSetEDR()
{
	C6MSetEDR(m_iEDRvalue);
	return true;
}
int CthinC6::EDR_WriteString(char *pEDRloc, char * cStringToWrite)
{
	//this function is used instead of strcpy_s because the safe function fills the buffer with garbage characters after the string
	short sLength = (short)(strlen(cStringToWrite));
	short i;
	char * pTemp = pEDRloc;
	char *pSTW = cStringToWrite;
	for (i = 0; i < sLength; i++)
		*pEDRloc++ = *pSTW++;

	return(sLength);

}

bool CthinC6::C6MSetEDR(int whichEDR)
{
	m_iEDRvalue = whichEDR;

	char edrPath[MAX_PATH];
	char edrRootPath[MAX_PATH];

	UINT32 len = sprintf(edrPath, "%s/C6/", DataPath ? DataPath : "..");
	UINT32 len2 = sprintf(edrRootPath, "%s/C6/", DataPath ? DataPath : "..");


	switch (whichEDR)
	{
	case 0:	    // Factory Raw RGB
		whichEDR = 0;
		edrPath[0] = 0;
		break;

	case 1:	    // Factory CMF 1932 2deg XYZ
		whichEDR = 1;
		edrPath[0] = 0;
		break;

	case 2:	    // First loaded EDR
		whichEDR = 2;
		edrPath[0] = 0;
		break;

	case 12:    // LCD CCFL
		len += sprintf(edrPath + len, "45584302FA58.cbfx");
		break;

	case 13:    // LCD CCFL Wide
		len += sprintf(edrPath + len, "A1BC79888AB7.cbfx");
		break;

	case 14:    // LCD White LED
		len += sprintf(edrPath + len, "1B69818CCB39.cbfx");
		break;

	case 15:    // LCD RGB LED (HP Dreamcolor)
		len += sprintf(edrPath + len, "E84A53BFC836.cbfx");
		break;

	case 16:    // Projector UHP
		len += sprintf(edrPath + len, "64A93B4B921D.cbfx");
		break;

	case 17:    // CRT
		len += sprintf(edrPath + len, "BE46EDFA7A6B.cbfx");
		break;

	case 18:    // Plasma
		len += sprintf(edrPath + len, "202FABCCF9DA.cbfx");
		break;

	case 19:    // Projector White LED
		len += sprintf(edrPath + len, "260D5518C60D.cbfx");
		break;

	case 20:    // Projector RGB LED
		len += sprintf(edrPath + len, "5CAB91855E23.cbfx");
		break;

	case 21:    // Quad Pixel (Sharp Quad)
		len += sprintf(edrPath + len, "402BE0A2A156.cbfx");
		break;

	case 22:    // LCD White LED Wide
		len += sprintf(edrPath + len, "F7AEE3E65EA7.cbfx");
		break;

	case 23:    // OLED Direct Drive
		len += sprintf(edrPath + len, "3CFDF1C4C546.cbfx");
		break;

	case 24:    // DC/P3 CCFL (FSI)
		len += sprintf(edrPath + len, "E011C12EF8E6.cbfx");
		break;

	case 25:    // HP DreamColor Wide Gamut RGB
		len += sprintf(edrPath + len, "7F45F8961EB7.cbfx");
		break;

	case 26:    // Wide Gamut BG
		len += sprintf(edrPath + len, "4B96B149B4B4.cbfx");
		break;

	case 27:    // HP zBook
		len += sprintf(edrPath + len, "C5B0E9537BB2.cbfx");
		break;
	case 28:    // LG White OLED
		len += sprintf(edrPath + len, "3B97418C94DD.cbfx");
		break;
	case 29:    // Visio QD
		len += sprintf(edrPath + len, "A0B551234D00.cbfx");
		break;
	case 30:    // LED PFS
		len += sprintf(edrPath + len, "D35414323CDA.cbfx");
		break;
	case 31:    // Panasonic-RZ12K-LaserPhosphor
		len += sprintf(edrPath + len, "RM04ZLWI4DCA.cbfx");
		break;
	case 32:    // Panisonic-RZ970-LaserPhosphor
		len += sprintf(edrPath + len, "7DQP6KI69E9O.cbfx");
		break;
	case 33:    // Barco-HDXW20-Xenon
		len += sprintf(edrPath + len, "8FK1192KQW67.cbfx");
		break;
	case 34:    // Samsung 15
		len += sprintf(edrPath + len, "40F4720DB68E.cbfx");
		break;
	case 35:    // Samsung 16
		len += sprintf(edrPath + len, "D3C953195DAF.cbfx");
		break;
	case 36:    // Samsung 17
		len += sprintf(edrPath + len, "E6ACDF781574.cbfx");
		break;
	case 37:    // HP DreamColor III
		len += sprintf(edrPath + len, "75FF82917BDE.cbfx");
		break;
	case 38:	// HP DreamColor zBook G5 EDR (2018) 
		len += sprintf(edrPath + len, "VQ177VAZ48T9.cbfx");
		break;
	case 99:	// Test EDR
		len += sprintf(edrPath + len, "test.edr");
		break;
	default:
		whichEDR = 1;
		edrPath[0] = 0;
		break;
	}

	

	if (edrPath[0])
	{
		if (whichEDR == 99)
		{
			if (i1d3SetCalibrationFromFile(m_devHndl, (unsigned char*)edrPath) != i1d3Success)
			{
				SetError(ERR_TABLE_INSTALL);
				

				return FALSE;
			}
		}
		else
		{
			char edrFullPath[MAX_PATH] = { 0 };

			strcpy(edrFullPath, edrPath);

			char *ptr = strrchr(edrPath, 0x5c);
			if (ptr) {
				ptr[0] = 0;
			}

			unsigned char temp[256];
			RandomChar(temp, 12);
			temp[12] = 0;

			char tmpPath[MAX_PATH];
			sprintf(tmpPath, "%s%s", edrRootPath, temp);


			BOOL result = FALSE;

			if (DecryptTo) {
				//result = DecryptTo(edrFullPath, tmpPath);
			}

			if (!result)
			{
				SetError(ERR_TABLE_INSTALL);
				

				return FALSE;
			}


		//	std::string strOutputPath = tmpPath;
		//	std::string strTemp1, strTemp2, strTemp3, strTemp4;
# if 0
			CString strOutputPath = tmpPath;
			CString  strTemp1, strTemp2, strTemp3, strTemp4;
			int pos1 = 0, pos2 = 0;

			pos1 = (int)strOutputPath.find_first_of('/');

			strTemp1 = strOutputPath.substr(0, pos1);
			strTemp2 = strOutputPath.substr(pos1 + 1);
			pos2 = (int)strTemp2.find_first_of('/');
			strTemp3 = strTemp2.substr(0, pos2);
			strTemp4 = strTemp2.substr(pos2 + 1);

			strTemp1 += "\\";
			strTemp1 += strTemp3;
			strTemp1 += "\\";
			strTemp1 += strTemp4;

			int status = i1d3SetCalibrationFromFile(m_devHndl, (unsigned char*)strTemp1.c_str());
			//			int status = i1d3SetCalibrationFromFile(m_devHndl, (unsigned char*)tmpPath);
# endif

			

			if (status != i1d3Success)
			{
				SetError(ERR_TABLE_INSTALL);
				

				return FALSE;
			}
		}

		whichEDR = 2;
	}

	i1d3CALIBRATION_LIST * calList;
	int numCals = 0;
	int status = i1d3GetCalibrationList(m_devHndl, &numCals, &calList);

	// used for debugging whichEDR loads
	if (status == i1d3Success)
	{
		char temp[256];
		sprintf(temp, "%d", numCals);
		//LogWriteInfo(Name, (char*)"whichEDRs ", temp);

		for (int i = 0; i < numCals; i++)
		{
			i1d3CALIBRATION_ENTRY *cal = calList->cals[i];

			sprintf(temp, "%s%d - %s", whichEDR == i ? "*" : " ", i, cal->displayName);
			//LogWriteInfo(Name, (char*)"whichEDR ", temp);
		}
	}

	if ((int)whichEDR > numCals - 1)
	{
		i1d3SetCalibration(m_devHndl, calList->cals[1]);

		SetError(ERR_TABLE);
		

		return FALSE;
	}

	status = i1d3SetCalibration(m_devHndl, calList->cals[whichEDR]);
	if (status != i1d3Success)
	{
		SetError(ERR_MODE);
		

		return FALSE;
	}

	

	SetError(ERR_NONE);
	return TRUE;
}
bool CthinC6::SetError(int whichError)
{

	return true;
}
bool CthinC6::LogWriteInfo(int value)
{
	return true;

}
bool CthinC6::RandomChar(unsigned char *inArray, int iLength)
{

	return true;
}