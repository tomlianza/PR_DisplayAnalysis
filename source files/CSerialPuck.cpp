#include "stdafx.h"
#include "CSerialPuck.h"

#define DEBUG_RW	1


CSerialPuck::CSerialPuck()
{
	m_iIntegrationTimeNStrings = (int)IT_NUM;
	m_iGainNStrings = (int)GNUM;

	m_dAutoRange[AC_LOW].dGain = 2048.0;
	m_AutoRange[AC_LOW].GainIndex = G2048;
	m_dAutoRange[AC_LOW].dIntTime = 512.0;
	m_AutoRange[AC_LOW].IntTimeIndex = IT_9;

	m_dAutoRange[AC_MEDIUM].dGain = 512.0;
	m_AutoRange[AC_MEDIUM].GainIndex = G512;
	m_dAutoRange[AC_MEDIUM].dIntTime = 128.0;
	m_AutoRange[AC_MEDIUM].IntTimeIndex = IT_7;

	m_dAutoRange[AC_HIGH].dGain = 128.0;
	m_AutoRange[AC_HIGH].GainIndex = G128;
	m_dAutoRange[AC_HIGH].dIntTime = 32.0;
	m_AutoRange[AC_HIGH].IntTimeIndex = IT_5;

	short j;
	for (j = 0; j < 3; j++)
	{
		m_3X3_RAW2XYZ[j][0] = 1.0;
		m_3X3_RAW2XYZ[j][1] = 0;
		m_3X3_RAW2XYZ[j][2] = 0;
		m_3X3_RAW2XYZ[j][3] = 0;
		m_3X3_RAW2XYZ[j][4] = 1.0;
		m_3X3_RAW2XYZ[j][5] = 0;
		m_3X3_RAW2XYZ[j][6] = 0;
		m_3X3_RAW2XYZ[j][7] = 0;
		m_3X3_RAW2XYZ[j][8] = 1.0;

	}
	m_CurrentRaw2XYZmatrix[0] = 1.0;
	m_CurrentRaw2XYZmatrix[1] = 0;
	m_CurrentRaw2XYZmatrix[2] = 0;
	m_CurrentRaw2XYZmatrix[3] = 0;
	m_CurrentRaw2XYZmatrix[4] = 1.0;
	m_CurrentRaw2XYZmatrix[5] = 0;
	m_CurrentRaw2XYZmatrix[6] = 0;
	m_CurrentRaw2XYZmatrix[7] = 0;
	m_CurrentRaw2XYZmatrix[8] = 1.0;

  char *SerialPuckCommandStrings[20] =
  {
	  "tar",// trigger measuremeent
	  "nra",// check for completion 
	  "grdn",// take 3 point data 
	  "sste",// set sample rate
	  "gste",// get sample rate 
	  "ssr", // set sample rate 
	  "gsr", // get sample rate 
	  "sagc",// set autogain on
	  "gagc",// get autogain state 
	  "gnagi",// number of auto gain states
	  "sg", // set gain
	  "gg",  // get gain
	  "gngl", // number of adc gain levels 
	  "st",// set int time;
	  "gt", // get int time; 
	  "gnitl",// get numbrer of intergation time levels 
	  "scp",//set the gain channel and index  scp  5 0
	  "gcp",//set the gain channel to get the data from 
	  "scce",// float values from index 0 to 8
	  "gcce"// get float values in order  


};

#if DEBUG_RW
	m_cfDebug.Open("DebugDataRead.text", CFile::modeCreate | CFile::modeWrite, &m_cfex);
#endif
}
bool CSerialPuck::OpenCommPort(int PortNumber)
{
	char cbuf[256], cComPortName[64];
	COMMTIMEOUTS timeouts;

	DCB port;
	strcpy(cComPortName, "COM");
	_itoa(PortNumber, cbuf, 10);
	strcat(cComPortName, cbuf);
	//strcat(cComPortName, ":");
	char ComPortName[256];
	strcpy_s(ComPortName, "\\\\.\\");
	strcat_s(ComPortName, cComPortName);

	m_HComPort = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (m_HComPort == INVALID_HANDLE_VALUE)
	{
		CommErrorDisplay("Comport Failed to open properly");
		m_bComPortOpen = false;
		return false;
	}
	m_bComPortOpen = true;

	// get the current DCB, and adjust a few bits to our liking.
	memset(&port, 0, sizeof(port));
	port.DCBlength = sizeof(port);
	if (!GetCommState(m_HComPort, &port))
	{
		CommErrorDisplay("Getting CommState");

		return false;
	}


	if (!BuildCommDCB("baud=115200 parity=n data=8 stop=1", &port))
	{
		CommErrorDisplay("building comm DCB");
		return false;
	}
	if (!SetCommState(m_HComPort, &port))
	{
		CommErrorDisplay("adjusting port settings");
		return false;
	}

	// set short timeouts on the comm port.
	timeouts.ReadIntervalTimeout = 250;// millisecs between characters
	timeouts.ReadTotalTimeoutMultiplier = 250;	// millisec multiplier by number of characters
	timeouts.ReadTotalTimeoutConstant = 2000; // was 2500 2.5 sec + nchar * 250 msec total time out(about 3secs);
	timeouts.WriteTotalTimeoutMultiplier = 250;
	timeouts.WriteTotalTimeoutConstant = 2500;
	if (!SetCommTimeouts(m_HComPort, &timeouts))
	{
		CommErrorDisplay("Setting TimeOuts failed");
		return false;
	}



	Get3X3Matrix(0, m_CurrentRaw2XYZmatrix);

	return(true);
	
}

bool CSerialPuck::CommErrorDisplay(char * cText)
{
	strcpy_s(m_ErrorMessage, 1024, cText);
	return true;

}
bool CSerialPuck::SendGet(char *cBuffer,int delay)
{
	if (!m_bComPortOpen)
		return false;
	DWORD nBytesWritten;
	DWORD nBytesRead;
	//WORD i;
	short iLength;
	char cCmdBuffer[1024];
	strcpy_s(cCmdBuffer, sizeof(cCmdBuffer), cBuffer);
	iLength = (short)strlen(cBuffer);
	cCmdBuffer[iLength] = 0x0d; //add line feed
	cCmdBuffer[iLength + 1] = 0x0;



	iLength = (short)strlen(cCmdBuffer);

#if DEBUG_RW
	strcpy(m_cDebugMessage, "Write command:");
	strcat(m_cDebugMessage, cCmdBuffer);
	m_cfDebug.Write(m_cDebugMessage, strlen(m_cDebugMessage));
	#endif
	WriteFile(m_HComPort, cCmdBuffer, 1024, &nBytesWritten, NULL);



	Sleep(delay);

	memset(m_cInOutBuffer, 0, 128);
	////TRACE("Entering ReadFile in SendGet\n");
	ReadFile(m_HComPort, m_cInOutBuffer, 1024, &nBytesRead, NULL);
#if DEBUG_RW
	strcpy(m_cDebugMessage, "Read command:");
	strcat(m_cDebugMessage, m_cInOutBuffer);
	m_cfDebug.Write(m_cDebugMessage, strlen(m_cDebugMessage));
#endif
	////TRACE("Exiting SendGet \n");

	return true;

}
bool CSerialPuck::SendGet(char *cBuffer)
{
	
	
	if (!m_bComPortOpen) return false;
		
	DWORD nBytesWritten;
	DWORD nBytesRead;
	//WORD i;
	short iLength;
	char cCmdBuffer[1024];
	strcpy_s(cCmdBuffer, sizeof(cCmdBuffer), cBuffer);
	iLength = (short)strlen(cBuffer);
	cCmdBuffer[iLength] = 0x0d; //add line feed
	cCmdBuffer[iLength + 1] = 0x0;
	

	
	iLength = (short)strlen(cCmdBuffer);
	

	WriteFile(m_HComPort, cCmdBuffer, 1024, &nBytesWritten, NULL);
		
			

	Sleep(5);

	memset(m_cInOutBuffer, 0, 128);
	//TRACE("Entering ReadFile in SendGet\n");
	ReadFile(m_HComPort, m_cInOutBuffer, 1024, &nBytesRead, NULL);
	//TRACE("Exiting SendGet \n");
	
	return true;

}

void CSerialPuck::DisableAutoGain()
{
	SendGet("sagc 0",50);

}
void CSerialPuck::TriggerMeasurement()
{
	SendGet("tar",50);

}

bool CSerialPuck::IsMeasurementComplete()
{
	SendGet("nra",0);
	char * cValue, **cptr, *cNext, cTemp[1024];
	cValue = (cTemp);
	cptr = &cValue;
	strcpy_s(cTemp, 1024, m_cInOutBuffer);

	cNext = Parse2Character(" ", cptr);
	cNext = Parse2Character("\r",cptr);
	if (strstr(cNext, "1") != NULL)
		return true;
	else
		return false;
}
bool CSerialPuck::AutoRange()
{
	SetGainTimeCombo(AC_HIGH);  // set lowest exposure
	Get3DecimalData();
	double dMax = 0;
	if (dMax < m_dOutValues[0]) 
		dMax = m_dOutValues[0];
	if (dMax < m_dOutValues[1])
		dMax = m_dOutValues[1];
	if (dMax < m_dOutValues[2])
		dMax = m_dOutValues[2];
	if ((dMax * 256) < 65536)
	{
		SetGainTimeCombo(AC_LOW);
		Get3DecimalData();
			return (true);

	}
	if ((dMax * 16) < 65536)
	{
		SetGainTimeCombo(AC_MEDIUM);
		Get3DecimalData();
		return (true);

	}

	return (true);
};
void CSerialPuck::SetGainTimeCombo(AUTOLIGHTLEVEL whichLevel)
{

	SetGain(m_AutoRange[whichLevel].GainIndex);
	SetIntTime(m_AutoRange[whichLevel].IntTimeIndex);
	m_CurrentGain = dGain[m_AutoRange[whichLevel].GainIndex];
	m_CurrentIntTime = dIntTimeMS[m_AutoRange[whichLevel].IntTimeIndex];

};
void CSerialPuck::SetGain(SG_ENUM whichGain)
{
	char cGain[4];
	int  iGain = (int) whichGain;
	_itoa(iGain, cGain,10);
	SetGain(cGain);

}
void CSerialPuck::SetGain(int whichGain)
{
	char cGain[4];
	int  iGain = (int)whichGain;
	_itoa(iGain, cGain, 10);
	SetGain(cGain);

}

void CSerialPuck::SetGain(char *cGain)
{
	char cmd[10];
	strcpy(cmd , "sg ");
	strcat(cmd,cGain);
	SendGet(cmd,1);
	m_CurrentGain = dGain[atoi(cGain)];

}

void CSerialPuck::SetIntTime(ST_ENUM whichIntTime)
{
	char cTime[4];
	_itoa((int)whichIntTime, cTime,10);
	SetIntTime(cTime);
	m_STintegrationTime = whichIntTime;
	

}

void CSerialPuck::SetIntTime(int whichIntTime)
{
	char cTime[4];
	_itoa((int)whichIntTime, cTime, 10);
	SetIntTime(cTime);
	m_STintegrationTime = (ST_ENUM)whichIntTime;


}

void CSerialPuck::SetIntTime(char * cTime)
{
	char cmd[10];
	strcpy(cmd, "st ");
	strcat(cmd, cTime);
	SendGet(cmd,1);
	m_STintegrationTime = (ST_ENUM)atoi(cTime);
	m_CurrentIntTime = dIntTimeMS[atoi(cTime)];

}

bool CSerialPuck::Get3DecimalData()
{
	//SetHiddenCmds();
	
	//TRACE("Trigger Measurement\n");
	
	TriggerMeasurement();
	//TRACE("Waiting for completion\n");
	while (!IsMeasurementComplete());
	//TRACE("SendGet grdn\n");
	SendGet("grdn",20);
	char * cValue, **cptr, *cNext, cTemp[1024];
	cValue = (cTemp);
	cptr = &cValue;
	strcpy_s(cTemp, 1024, m_cInOutBuffer);
	if (strstr(m_cInOutBuffer, "grdn") == NULL)
	{
		
		
		return false;
	}
	cNext = Parse2Character(" ", cptr); // do nothing with this 

	cNext = Parse2Character(",", cptr);
	m_dOutValues[0] = atof(cNext);

	cNext = Parse2Character(",", cptr);
	m_dOutValues[1] = atof(cNext);

	
	cNext = Parse2Character("\r", cptr);
	m_dOutValues[2] = atof(cNext);;

	ReorderOutVals();


	return(true);
}
void CSerialPuck::ReorderOutVals()
{
	double dTemp[3];
// data determined by experiment to be in ZXY order 
	dTemp[0] = m_dOutValues[1]; // really X
	dTemp[1] = m_dOutValues[2]; // really Y;
	dTemp[2] = m_dOutValues[0]; // really Z
	
	short i;
	for (i = 0; i < 3; i++)
		m_dOutValues[i] = dTemp[i];

	// data now in appropriate order XYZ
}
bool CSerialPuck::Get3DecimalAutoRangeData()
{
	// Note that this function delivers gain & intTime corrected data 
	AutoRange();

	char * cValue, **cptr, *cNext, cTemp[1024];
	cValue = (cTemp);
	cptr = &cValue;
	strcpy_s(cTemp, 1024, m_cInOutBuffer);
	if (strstr(m_cInOutBuffer, "grdn") == NULL)
	{

				return false;
	}
	cNext = Parse2Character(" ", cptr); // do nothing with this 

	cNext = Parse2Character(",", cptr);
	m_dOutValues[0] = atof(cNext);

	cNext = Parse2Character(",", cptr);
	m_dOutValues[1] = atof(cNext);


	cNext = Parse2Character("\r", cptr);
	m_dOutValues[2] = atof(cNext);;

	double dCorrection = 1.0 / (m_CurrentGain *(m_CurrentIntTime / 1000.0));
	m_dOutValues[0] *= dCorrection;
	m_dOutValues[1] *= dCorrection;
	m_dOutValues[2] *= dCorrection;

	ReorderOutVals(); 
	return(true);// need parse the data 
}

	

void CSerialPuck::Set3X3Matrix(int channel, double * d3X3Matrix)
{
	char cCmd[128];
	char cBuffer[64];
	short i; 

	sprintf_s(cBuffer, 64, " %2d ", channel);
	strcpy(cCmd, "spc");
	strcat(cCmd, cBuffer);
	strcat(cCmd, "0");
	SendGet(cCmd,20);
	for (i = 0; i < 9; i++)
	{
		strcpy(cCmd, "scce ");
		sprintf_s(cBuffer, 64, "%12.5f", d3X3Matrix[i]);
		strcat(cCmd, cBuffer);
		SendGet(cCmd, 20);

	}
	for (i = 0; i < 3; i++)//stuff dummy offset values into the matrix
	{
		strcpy(cCmd, "scce ");
		strcat(cCmd, "-10");
		SendGet(cCmd, 20);
	}


}

void CSerialPuck::Get3X3Matrix(int channel, double * d3X3Matrix)
{
	char cCmd[128];
	char cBuffer[64];
	char *cPtr1,*cPtr2;
	short i;
	//TBD channel += 4; // this is done to map the data into unused channels in the current firmware 
	sprintf_s(cBuffer, 64, " %2d ", channel);
	
	
	strcpy(cCmd, "scp");
	strcat(cCmd, cBuffer);// set to offset for cal data 
	strcat(cCmd, " 0"); // set ptr to first index
	SendGet(cCmd, 20);

	for (i = 0; i < 9; i++)
	{
		strcpy(cCmd, "gcce ");
		
		SendGet(cCmd, 20);
		cPtr1 = m_cInOutBuffer;
		// parse string returned when you understand what get returned.... 
		
		cPtr2 = Parse2Character(" ", &cPtr1); // move to the first space
		cPtr2 = Parse2Character(" ", &cPtr1);// move to second space 
		cPtr2 = Parse2Character(" ", &cPtr1);// move to third space 
		cPtr2 = Parse2Character(" ", &cPtr1);// move to fourth space 
		cPtr2 = Parse2Character("\r", &cPtr1);// move to cr 
		d3X3Matrix[i]=atof(cPtr2);

	}
	strcpy(cCmd, "scp");
	strcat(cCmd, cBuffer);// set to offset for cal data 
	strcat(cCmd, " 0"); // set ptr to first index
	SendGet(cCmd, 20);
	

}
bool CSerialPuck::GetXYZData()
{

	Get3DecimalAutoRangeData();
	 MatMult((double *)m_CurrentRaw2XYZmatrix, 3, 3, m_dOutValues, 3, 1, m_dXYZdata);
	 
	 
	 return true;
};

bool CSerialPuck::GetYxyData()
{
	GetXYZData();
	double dSum = m_dXYZdata[0] + m_dXYZdata[1] + m_dXYZdata[2];
	m_dYxydata[0] = m_dXYZdata[1]; // Y 
	m_dYxydata[1] = m_dXYZdata[0] / dSum;
	m_dYxydata[2] = m_dXYZdata[1] / dSum;
	return (true);

}



char * CSerialPuck::Parse2Character(char * ch, char** cPtrInString)
{
	char *cLoc = strstr(*cPtrInString, ch); // find the character location 
	if (cLoc == NULL)
		return((char *)-1);
	*cLoc = NULL; //null terminate the string.
	int offset = cLoc - *cPtrInString;
	*cPtrInString = cLoc + 1;
	
	return (cLoc-offset); 

};
void CSerialPuck::ParseDvaluesFromString(char * cPtrInString)
{

	char * cLoc = Parse2Character(" ", &cPtrInString);  // parse past the space 
	if ((int)cLoc == -1) // an error has occured
	{
		strcpy (m_ErrorMessage,"Error Occured in ParseDvalues from String");
		m_bMeasurementError = true;

	}
	sscanf(cLoc, "%lf,%lf,%lf", &m_dOutValues[0], &m_dOutValues[1], &m_dOutValues[2]);
};


/********************************************************************/

int CSerialPuck::MatMult(double *aptr, int nrow, int pcol, double *bptr, int prow, int ncol,
	double *outptr)
	/********************************************************************/
{
	double *cptr, *dptr, *eptr;
	int i, j, k, ibase;

	if (pcol != prow)
		return(0); /* The matrices are not order correctly! */

	for (i = 0; i < nrow; i++)
		for (j = 0; j < ncol; j++) {
			cptr = outptr + (i * ncol) + j;
			*cptr = 0.0000;
			ibase = i * pcol;

			for (k = 0; k < pcol; k++) {
				dptr = aptr + ibase + k;
				eptr = bptr + (k * ncol) + j;
				*cptr = *cptr + (*dptr) * (*eptr);
			}
		}
	return (1);
}