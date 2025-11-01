#include "stdafx.h"

#include "CPRISpectro.h"
#define LOCAL_DEBUG

CPRISpectro::CPRISpectro()
{
#ifdef LOCAL_DEBUG
	
DebugFile = fopen("Debug.txt", "a+");
#endif
	
	m_ComPort = (HANDLE)-1;

};


CPRISpectro::~CPRISpectro()
{};

bool CPRISpectro::SendGetCommand(PRICOMMAND whichCMD, void *Buffer, DWORD nTimeOutms)
{
	CString  CMDString = csPRI_COMMAND[whichCMD];
	char cCmdBuffer[128];
	DWORD nBytesWritten;
	DWORD nBytesRead;
	WORD i; 
	short iLength;
	CMDString += "\r\n";
#ifdef LOCAL_DEBUG

	DebugFile = fopen("Debug.txt", "a+");
	
	strcpy(cBuffer, "Enter SendGet");
	strcat(cBuffer, csPRI_COMMAND[whichCMD]);
	strcat(cBuffer, "\n");
	fwrite(cBuffer, 1, strlen(cBuffer), DebugFile);
	fclose(DebugFile);

#endif
	
	strcpy_s(cCmdBuffer, sizeof(cCmdBuffer), CMDString);
	iLength =(short) strlen(cCmdBuffer);
	for (i = 0; i < iLength; i++)
	{
		WriteFile(m_ComPort, &cCmdBuffer[i], 1L, &nBytesWritten, NULL);
		Sleep(40);
	}
	Sleep(200);
#ifdef LOCAL_DEBUG

	DebugFile = fopen("Debug.txt", "a+");
	
	strcpy(cBuffer, "Cmd sent");
	strcat(cBuffer, csPRI_COMMAND[whichCMD]);
	strcat(cBuffer, "\n");
	fwrite(cBuffer, 1, strlen(cBuffer), DebugFile);
	fclose(DebugFile);

#endif

	memset(m_cResponse, 0, sizeof(m_cResponse));
	GetResponse(m_cResponse, sizeof(m_cResponse), nTimeOutms, &nBytesRead);
// to do -> check response 
#ifdef LOCAL_DEBUG

	DebugFile = fopen("Debug.txt", "a+");
	
	strcpy(cBuffer, "Response Recieved");
	strcat(cBuffer, csPRI_COMMAND[whichCMD]);
	strcat(cBuffer, "\n");
	fwrite(cBuffer, 1, strlen(cBuffer), DebugFile);
	fclose(DebugFile);

#endif
	
	return true;
}
bool CPRISpectro::SendGetExplicitCommand(char* cBuf , void *Buffer, DWORD nTimeOutms)
{
	CString  CMDString = cBuf;
	char cCmdBuffer[128];
	DWORD nBytesWritten;
	DWORD nBytesRead;
	WORD i;
	short iLength;
	CMDString += "\r";


	strcpy_s(cCmdBuffer, sizeof(cCmdBuffer), CMDString);
	iLength = (short)strlen(cCmdBuffer);
	for (i = 0; i < iLength; i++)
	{
		WriteFile(m_ComPort, &cCmdBuffer[i], 1L, &nBytesWritten, NULL);
		Sleep(20);
	}
	Sleep(200);

	memset(m_cResponse, 0, sizeof(m_cResponse));
	GetResponse(m_cResponse, sizeof(m_cResponse), nTimeOutms, &nBytesRead);
	// to do -> check response  

	return true;
}
bool CPRISpectro::GetDeviceName()// added 5/4/2017
{

	SendGetCommand(PRI_GET_NAME, m_cResponse, SHORT_TIMEOUT);
	// Parse m_cResponse here....
	FormatResponse(m_cResponse, &m_ProductInfo.PRI_Name);
	return true;

}

bool CPRISpectro::InitSpectroConfiguration()
{
	short i;
	//Get the Product Type String 
	i = 0;
	m_bMetric = TRUE;
	CString  cIntegrationTime;
	memset(m_cResponse, 0, sizeof(m_cResponse));
	TRACE(" entered InitSpectroConfiguration\r\n");
	SendGetCommand(PRI_SET_SINGLE_MEASUREMENT, m_cResponse, SHORT_TIMEOUT);
	TRACE(" entered InitSpectroConfiguration1\r\n");
	SendGetCommand(PRI_SET_NO_SYNC, m_cResponse, SHORT_TIMEOUT);
	TRACE(" entered InitSpectroConfiguration2\r\n");
	if (m_bMetric)
	{
		SendGetCommand(PRI_SET_METRIC, m_cResponse, LONG_TIMEOUT);
	}
	else
	{
		SendGetCommand(PRI_SET_ENGLISH, m_cResponse, LONG_TIMEOUT);
	}
    
	TRACE(" entered InitSpectroConfiguration3\r\n");
	
	SendGetCommand(PRI_GET_NAME, m_cResponse, SHORT_TIMEOUT);
	// Parse m_cResponse here....
	FormatResponse(m_cResponse, &m_ProductInfo.PRI_Name);
	TRACE(" entered InitSpectroConfiguration 4\r\n");
	SendGetCommand(PRI_GET_FIRMWARE_VERSION, m_cResponse, SHORT_TIMEOUT);
	// Parse m_cResponse here....
	FormatResponse(m_cResponse, &m_ProductInfo.PRI_FirmwareVersion);
	TRACE(" entered InitSpectroConfiguration5\r\n");
	SendGetCommand(PRI_GET_SERIAL_NUMBER, m_cResponse, SHORT_TIMEOUT);
	// Parse m_cResponse here....
	FormatResponse(m_cResponse, &m_ProductInfo.PRI_SerialNumber);
	TRACE(" entered InitSpectroConfiguration6\r\n");
	if (m_bUsingPR810)
		return(true);
	
#if 0
	MeasureXYZData(&m_MeasurementData.XYZdata);
	TRACE(" entered InitSpectroConfiguration7\r\n");
	GetYxyData();
#endif
	
	// fill the measurement structure value 
	
	 m_MeasurementData.dIntegrationTime = GetIntegrationTime();
	 TRACE(" entered InitSpectroConfiguration8\r\n");
	
	BuildSensorInfoStruct();  // the sensor info is more  complex than the 

	// now copy the configuration data into the current measuement structure 

	m_MeasurementData.DeviceDescriptor.dStartLamda = m_SensorInfo.PRI_StartingWavelength;
	m_MeasurementData.DeviceDescriptor.dEndLamda = m_SensorInfo.PRI_EndingWavelength;
	m_MeasurementData.DeviceDescriptor.dLamdaIncrement = m_SensorInfo.PRI_WavelengthIncrement;
	m_MeasurementData.DeviceDescriptor.wNRawDataPoints = m_SensorInfo.PRI_Number_Sensor_Elements;
	m_MeasurementData.DeviceDescriptor.sStartPixel = m_SensorInfo.PRI_First_Useable_Pixel;
	m_MeasurementData.DeviceDescriptor.sEndPixel = m_SensorInfo.PRI_Last_Useable_Pixel;
	//****TBD add device type descriptor 
	m_MeasurementData.bDataConfigured = true;
	if (m_bMetric)
	{
		SendGetCommand(PRI_SET_METRIC, m_cResponse, LONG_TIMEOUT);
	}
	else
	{
		SendGetCommand(PRI_SET_ENGLISH, m_cResponse, LONG_TIMEOUT);
	}
	


	
		
	return(true);
};
void CPRISpectro::FormatResponse(char * inBuffer, CString * csResponse)
{ 
	short i;
	// trim string and remove cr/lf 
	i = 0;
	char *cTemp;
	char* CR;
	while (inBuffer[i++] != 44); //move to first comma 
	cTemp = &inBuffer[i]; //includes carriage return line feed
	CR = cTemp;
	i = 0;
	while (cTemp[i++] != 0x0d);
	cTemp[i - 1] = 0x00;// trim cr/lf
	*csResponse = CR;

	
}

bool CPRISpectro::SetRemoteMode(char *cComPortName)//ie COM10
{
	char cbuf[256];
	DWORD nBytesWritten;
	short i;
	COMMTIMEOUTS timeouts;

	DCB port;
	
	char ComPortName[256];
	strcpy_s(ComPortName, "\\\\.\\");
	strcat_s(ComPortName, cComPortName);

	m_ComPort = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (m_ComPort == INVALID_HANDLE_VALUE)
	{
		CommErrorDisplay("Comport Failed to open properly");
		m_bSpectroConfigured = false;
		return false;
	}
	// get the current DCB, and adjust a few bits to our liking.
	memset(&port, 0, sizeof(port));
	port.DCBlength = sizeof(port);
	if (!GetCommState(m_ComPort, &port))
	{
		CommErrorDisplay("Getting CommState");
	
		return false;
	}
		

	if (!BuildCommDCB("baud=19200 parity=n data=8 stop=1", &port))
	{
		CommErrorDisplay("building comm DCB");
		return false;
	}
	if (!SetCommState(m_ComPort, &port))
	{
		CommErrorDisplay("adjusting port settings");
		return false;
	}

	// set short timeouts on the comm port.
	timeouts.ReadIntervalTimeout = 250;// millisecs between characters
	timeouts.ReadTotalTimeoutMultiplier = 250;	// millisec multiplier by number of characters
	timeouts.ReadTotalTimeoutConstant = 6000; // was 2500 2.5 sec + nchar * 250 msec total time out(about 3secs);
	timeouts.WriteTotalTimeoutMultiplier = 250;
	timeouts.WriteTotalTimeoutConstant = 2500;
	if (!SetCommTimeouts(m_ComPort, &timeouts))
	{
		CommErrorDisplay("Setting TimeOuts failed");
		return false;
	}



	strcpy_s(cbuf, "PHOTO");


	for (i = 0; i< 5; i++)
	{
		WriteFile(m_ComPort, &cbuf[i], 1L, &nBytesWritten, NULL);
		Sleep(5);
	}
	char *cTemp = m_cResponse;
	ReadFile(m_ComPort, cTemp, 128, &nBytesWritten, NULL);

	m_bSpectroConfigured = true;
	return(true);




}

void CPRISpectro::CommErrorDisplay(char * theMessage)
{

	strcpy_s(m_ErrorMessage,theMessage);
}
void CPRISpectro::BuildSensorInfoStruct()
{
	/* Format of data in the m_c_REsponse array:
	quality factor, 
	number of spectral points,
	bandwidth of instrument,
	starting wavelength,
	ending wavelength ,
	wavelength increment, 
	Number of detector elements,
	first useable raw pixel,
	last useable raw pixel 
	
	typedef struct PRI_SENSOR_INFO
{
	short	PRI_Sensor_nPixels;
	double  PRI_BandWidth;
	short   PRI_StartingWavelength;
	short   PRI_EndingWavelength;
	short   PRI_WavelengthIncrement;
	short   PRI_Number_Sensor_Elements;
	short   PRI_First_Useable_Pixel;
	short   PRI_Last_Useable_Pixel;

}PRISENSORINFO;

*/
	SendGetCommand(PRI_GET_SENSOR_INFO, m_cResponse, LONG_TIMEOUT);
	short i,j;
	i = 0;

	
	char mp_cBuffer[1024];
	while (m_cResponse[i++] != 44); //move to first comma 
	// get the number of pixels in the array;
	j = 0;
	
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_Sensor_nSpectralPoints = atoi(&mp_cBuffer[0]);

	// get the number of bandwidth ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_BandWidth = atof(&mp_cBuffer[0]);

	// get the number of Start WL ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_StartingWavelength = atoi(&mp_cBuffer[0]);

	// get the number of End WL ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_EndingWavelength = atoi(&mp_cBuffer[0]);
	// get the WL Increment ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_WavelengthIncrement = atoi(&mp_cBuffer[0]);

	// get the detector elements  ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_Number_Sensor_Elements = atoi(&mp_cBuffer[0]);

	// get the start pixel  ;
	j = 0;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_First_Useable_Pixel = atoi(&mp_cBuffer[0]);

	// get the end pixel  ;
	j = 0;
	while (m_cResponse[i] != 0x0d)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	i += 1;
	m_SensorInfo.PRI_Last_Useable_Pixel = atoi(&mp_cBuffer[0]);
// now copy it into the measurement data structure 
	m_MeasurementData.DeviceDescriptor.dStartLamda = m_SensorInfo.PRI_StartingWavelength;
	m_MeasurementData.DeviceDescriptor.dEndLamda = m_SensorInfo.PRI_EndingWavelength;
	m_MeasurementData.DeviceDescriptor.dLamdaIncrement = m_SensorInfo.PRI_WavelengthIncrement;
	m_MeasurementData.DeviceDescriptor.wNRawDataPoints = m_SensorInfo.PRI_Number_Sensor_Elements;
	m_MeasurementData.DeviceDescriptor.sStartPixel = m_SensorInfo.PRI_First_Useable_Pixel;
	m_MeasurementData.DeviceDescriptor.sEndPixel = m_SensorInfo.PRI_Last_Useable_Pixel;	
	m_MeasurementData.bDataConfigured = true;
}
void CPRISpectro::Clear_m_cResponse()
{
	int i; 
	for (i = 0; i < RESPONSE_LENGTH; i++)
		m_cResponse[i] = NULL;

}
void CPRISpectro::ParseXYZData(XYZDATA * dXYZData)
{
	short i, j;
	i = 0;


	//char mp_cBuffer[128];
	while (m_cResponse[i++] != 44); //move to first comma 

	j = 0;
	// get a single value 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL; // this is specified as a single value 0;
	i += 1;
	j = 0;
	// Get Y value;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dXYZData->X = atof(mp_cBuffer);
	j = 0;
	i += 1;
	// get  x value; 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dXYZData->Y = atof(mp_cBuffer);

	j = 0;
	i += 1;
	while (m_cResponse[i] != 13)//cr not comma
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dXYZData->Z = atof(mp_cBuffer);


}
void CPRISpectro::ParseYxyData(YxyDATA * dYxyData)
{
	short i, j;
	i = 0;


	//char mp_cBuffer[128];
	while (m_cResponse[i++] != 44); //move to first comma 

	j = 0;
	// get a single value 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL; // this is specified as a single value 0;
	i += 1;
	j = 0;
	// Get Y value;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dYxyData->Y = atof(mp_cBuffer);
	j = 0;
	i += 1;
	// get  x value; 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dYxyData->x = atof(mp_cBuffer);

	j = 0;
	i += 1;
	while (m_cResponse[i] != 13)//cr not comma
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	dYxyData->y = atof(mp_cBuffer);


}

bool CPRISpectro::MeasureYxyData(YxyDATA * dYxyData)
{
	
	SendGetCommand(PRI_SET_METRIC, m_cResponse, LONG_TIMEOUT);
	SendGetCommand(PRI_MEASURE_Yxy, m_cResponse, LONG_TIMEOUT);
	


	ParseYxyData(&(m_MeasurementData.YxyData));
	*dYxyData = m_MeasurementData.YxyData;
	BuildSensorInfoStruct();
	return true;
}

bool  CPRISpectro::PollMeasurementCompleteStatus()
{
	// send the p 

	// read the response if forth character = 1 The measurement is in progress..... chekc 
	return true;
}

int CPRISpectro::GetResponse(char *szResponse, short smaxlen, DWORD nTimeOutms, DWORD *len)
{
	char	*ptr;
	DWORD	nBytesRead, nTotalBytes, nByteCount;
	BOOL	bDone;
	DWORD	startcount, TimeOutCount;

	long    lResponse;
	if (smaxlen > RESPONSE_LENGTH)
		return FALSE;
	char cTemp[4095];
	int i; 
	i = 0;
	bDone = FALSE;
	ptr = szResponse;
	nTotalBytes = 0;
	nByteCount = 0;
	TimeOutCount = nTimeOutms;
	Clear_m_cResponse();
	memset(cTemp, 0, sizeof(cTemp));
	startcount = GetTickCount();
	bDone = FALSE;


	do
	{
		if ((lResponse = ReadFile(m_ComPort, &cTemp[i], 1, &nBytesRead, NULL)))
		{
			if( (cTemp[i] == '\n')&&(cTemp[i+1]== 0))
			{
				bDone = TRUE;

			}

			ptr++;
			i++;
			nByteCount++;
			if (nByteCount > RESPONSE_LENGTH)
				return (-1);
			Sleep(40);  // introduced to prevent hangs on return data.... 
		}
		else
			return lResponse;
	} while (bDone == FALSE);

	*len = nByteCount - 1;
	for (i = 0; i < (int)nByteCount; i++)
		szResponse[i] = cTemp[i];
	
	
	return SUCCESS;


}
void CPRISpectro::QuitRemoteMode()
{
	CString  CMDString = "Q";
	char cCmdBuffer[128];
	DWORD nBytesWritten;

	WORD i;
	short iLength;
	//CMDString += "\r\n";
	strcpy_s(cCmdBuffer, sizeof(cCmdBuffer), CMDString);
	iLength =(short) strlen(cCmdBuffer);
	if (m_ComPort != (HANDLE)-1L)
	{
		for (i = 0; i < iLength; i++)
		{
			WriteFile(m_ComPort, &cCmdBuffer[i], 1L, &nBytesWritten, NULL);
			Sleep(5);
		}
	}
}

double  CPRISpectro::GetIntegrationTime()
{
	
	short i, j; 
	double dIntegrationTime;

	SendGetCommand(PRI_GET_INTEGRATION_TIME, m_cResponse, SHORT_TIMEOUT);
	
	i = 0;


	char mp_cBuffer[16];
	while (m_cResponse[i++] != 44); //move to first comma 

	j = 0;
	while (m_cResponse[i++] != 44); //move to second comma skip the mode discription 
	
	while (m_cResponse[i] != 0x20)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL; // this is the integration time
	dIntegrationTime = atof(mp_cBuffer);
	m_MeasurementData.dIntegrationTime = dIntegrationTime;
	return (dIntegrationTime);
	
	
}

bool	CPRISpectro::TakeSpectralMeasurement()
{
	DWORD nBytesWritten, nBytesRead,nBytesInBuffer;
		WORD i,j;

		BYTE  testByte;
		char  cBuf[32];
		double dLamda, dPower;
	
	// first check that the configuration structure is filled 

	if (m_MeasurementData.bDataConfigured == false)
		return FALSE;
	

	//Send command to take spectral measuement 
	
		WriteFile(m_ComPort, "M5\r\n", 6, &nBytesWritten, NULL);
		Sleep(5);
	
	Clear_m_cResponse(); //Zero out the input buffer 
	testByte = NULL;
	i = 0;
	while (testByte != 0xa)
	{ 
		ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
		testByte = m_cResponse[i++]; // continue the search for line feed 
	}
	nBytesInBuffer = i - 1;
	i = 0; 
	// skip over first two commas to get at Peak Wavelength 
	while (m_cResponse[i++] != 44); //move to first comma 

	j = 0;
	while (m_cResponse[i++] != 44); //move to second comma skip the mode discription 

	while (m_cResponse[i] != 44) // get peak wavelength
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;
	m_MeasurementData.dPeakWavelength = atof(cBuf);
	j = 0;
	i++;
	while (m_cResponse[i] != 44) // integrated radiometric value
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;
	m_MeasurementData.dIntegratedEnergy = atof(cBuf);
	j = 0;
	i++;
	while (m_cResponse[i] != 0x0d) // integrated photon
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;// do nothing with this value yet
	Clear_m_cResponse();
	// now start taking spectral data 
	WORD wNloops =(WORD)( 1+(m_MeasurementData.DeviceDescriptor.dEndLamda -
		m_MeasurementData.DeviceDescriptor.dStartLamda) / m_MeasurementData.DeviceDescriptor.dLamdaIncrement);
	WORD wLoopCount;
	for (wLoopCount = 0;  wLoopCount< wNloops; wLoopCount++)
	{
		Clear_m_cResponse();
		i = 0;
		testByte = NULL;
		while (testByte != 0xa)
		{
			ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
			testByte = m_cResponse[i++]; // continue the search for line feed 
		}
		nBytesInBuffer = i - 1;
		m_cResponse[i - 2] = NULL; // lose the line fieed carriage return
		sscanf_s(m_cResponse, "%lf,%lf", &dLamda, &dPower);
		m_MeasurementData.dWavelength[wLoopCount] = dLamda;
		m_MeasurementData.dNativeSpectrum[wLoopCount] = dPower;




	}



	

	return TRUE;
}

bool	CPRISpectro::GetYxyData()
{
	if (m_bMetric)
	{
		SendGetCommand(PRI_SET_METRIC, m_cResponse, LONG_TIMEOUT);
	}
	else
	{
		SendGetCommand(PRI_SET_ENGLISH, m_cResponse, LONG_TIMEOUT);
	}
	SendGetCommand(PRI_GET_Yxy, m_cResponse, SHORT_TIMEOUT);
	ParseYxyData(&m_MeasurementData.YxyData);
	return TRUE;
}
bool 	CPRISpectro::MeasureYxyData()
{
	MeasureYxyData(&m_MeasurementData.YxyData);
	BuildSensorInfoStruct();
	return TRUE;
}

void CPRISpectro::FullMeasurementProcess()
{
	// Debug data to examine hangs 
	TRACE("InitSpecConfiguration\r\n");
	InitSpectroConfiguration();

	TRACE("Outof SpecConfiguration\r\n");
	GetPhotoMetricData();
	m_MeasurementData.CCT = m_PhotoMetricData.dCCT;
	TRACE("GetSpectralmeasurementData\r\n");
	GetSpectralMeasurementData();  // this gets the absolute spectral infomation
	TRACE("GetLightDark Data\r\n ");
	GetLightDarkData();
	CalculateResponsivity();
	m_MeasureDataClass.m_currentMeasurement = m_MeasurementData; // copy the captured data into the MeasurementData Class for manipulation 
	m_MeasureDataClass.InterpolateTo1nmData();
	m_MeasurementData = m_MeasureDataClass.m_currentMeasurement; // update the new calculated data 

}
void CPRISpectro::CalculateResponsivity()
{
	m_MeasurementData.dResponsivity = m_MeasurementData.dIntegratedLightMinusDarkData / m_MeasurementData.dIntegrationTime / 1000 / m_MeasurementData.dIntegratedEnergy;


};

 
bool CPRISpectro::MeasureXYZData(XYZDATA *XYZdata)
{

	SendGetCommand(PRI_MEASURE_XYZ, m_cResponse, SHORT_TIMEOUT);
	ParseXYZData(XYZdata);
	BuildSensorInfoStruct();

	return true;
}
void  CPRISpectro::CaptureSimpleMeasurement()
{

	CaptureSimpleMeasurement(&m_SimpleMeasurementData);
	BuildSensorInfoStruct();
}
void  CPRISpectro::CaptureSimpleMeasurement(SIMPLE_MEASUREMENT *sm_data)
{
	
	int i;

	

	// Set Adaptive mode 
	SetAdaptiveMode();
	SendGetCommand(PRI_SET_METRIC, m_cResponse, SHORT_TIMEOUT);//note that this will be variable later on.  
	MeasureXYZData(&sm_data->XYZdatadouble);
	// Get the integration time for the measurement 
	sm_data->dIntegrationTime = GetIntegrationTime();
	// make this a function soon...
	SendGetCommand(PRI_GET_SENSOR_INFO, m_cResponse, SHORT_TIMEOUT);
	BuildSensorInfoStruct();  //data stored in m_SensorInfo 

	sm_data->DeviceDescriptor.dEndLamda = m_SensorInfo.PRI_EndingWavelength;
	sm_data->DeviceDescriptor.dStartLamda = m_SensorInfo.PRI_StartingWavelength;
	sm_data->DeviceDescriptor.dLamdaIncrement = m_SensorInfo.PRI_WavelengthIncrement;
	sm_data->DeviceDescriptor.wNRawDataPoints = m_SensorInfo.PRI_Number_Sensor_Elements;
	sm_data->DeviceDescriptor.sStartPixel = m_SensorInfo.PRI_First_Useable_Pixel;
	sm_data->DeviceDescriptor.sEndPixel   =  m_SensorInfo.PRI_Last_Useable_Pixel;

	// set a configuration boolean to "fool" use the download funtion 
	m_MeasurementData.bDataConfigured = true;
	
	GetSpectralMeasurementData();//data resides in the  m_MeasurementData structure 
	m_MeasureDataClass.InterpolateTo1nmData();//  Interpolate the data to 1 nm 

	// TBD Make this a function
	sm_data->dIntegrationTime = m_MeasurementData.dIntegrationTime;
	sm_data->dIntegratedEnergy = m_MeasurementData.dIntegratedEnergy;
	sm_data->dIntegratedLightMinusDarkData = m_MeasurementData.dIntegratedLightMinusDarkData;

	// Copy spectra from the m_MeasurementData structure to the "simple" structure 
	
	short iStart = (short)m_MeasurementData.DeviceDescriptor.dStartLamda;
	short iEnd = (short )m_MeasurementData.DeviceDescriptor.dEndLamda;
	short iInc = (short)m_MeasurementData.DeviceDescriptor.dLamdaIncrement;
	short npts = (iEnd - iStart) / iInc + 1;
	for (i = 0; i < npts; i++)
	{
		sm_data->dNativeSpectrum[i] = m_MeasurementData.dNativeSpectrum[i];
		sm_data->dWavelength[i] = m_MeasurementData.dWavelength[i];
		

	}
	
	npts = iEnd - iStart + 1;

	for (i = 0; i < npts; i++)
	{

		sm_data->InterpolatedSpectrum[i] = m_MeasurementData.InterpolatedSpectrum[i];
	}


	//
}
bool	CPRISpectro::GetSpectralMeasurementData()
{
	DWORD nBytesWritten, nBytesRead, nBytesInBuffer;
	WORD i, j;

	BYTE  testByte;
	char  cBuf[32];
	double dLamda, dPower;

	// first check that the configuration structure is filled 

	if (m_MeasurementData.bDataConfigured == false)
		return FALSE;


	//Send command to take spectral measuement 

	WriteFile(m_ComPort, "D5\r\n", 6, &nBytesWritten, NULL);
	Sleep(5);

	Clear_m_cResponse(); //Zero out the input buffer 
	testByte = NULL;
	i = 0;
	while (testByte != 0xa)
	{
		ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
		Sleep(5);
		testByte = m_cResponse[i++]; // continue the search for line feed 
	}
	nBytesInBuffer = i - 1;
	i = 0;
	j=0;
	cBuf[j]= NULL;
	while (m_cResponse[i] != 44) // condition code; 
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;
	int iRet;
	iRet = atoi(cBuf);
	if(iRet != 0)
	{
		strcpy_s(m_ErrorMessage,2048,"Error Getting Spectral Data:");
		strcat_s(m_ErrorMessage,2048,cBuf);
		return(false);

	}
	j= 0; 
	cBuf[j] = NULL;
	
	j = 0;
	while (m_cResponse[i++] != 44); //move to second comma skip the mode discription 

	while (m_cResponse[i] != 44) // get peak wavelength
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;
	m_MeasurementData.dPeakWavelength = atof(cBuf);
	j = 0;
	i++;
	while (m_cResponse[i] != 44) // integrated radiometric value
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;
	m_MeasurementData.dIntegratedEnergy = atof(cBuf);
	m_MeasurementData.dRadiance = m_MeasurementData.dIntegratedEnergy;
	j = 0;
	i++;
	while (m_cResponse[i] != 0x0d) // integrated photon
	{
		cBuf[j++] = m_cResponse[i++];

	}
	cBuf[j] = NULL;// do nothing with this value yet
	Clear_m_cResponse();
	// now start taking spectral data 
	WORD wNloops = (WORD)(1 + (m_MeasurementData.DeviceDescriptor.dEndLamda -
		m_MeasurementData.DeviceDescriptor.dStartLamda) / m_MeasurementData.DeviceDescriptor.dLamdaIncrement);
	WORD wLoopCount;
	for (wLoopCount = 0; wLoopCount< wNloops; wLoopCount++)
	{
		Clear_m_cResponse();
		i = 0;
		testByte = NULL;
		while (testByte != 0xa)
		{
			ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
			//Sleep(5);
			testByte = m_cResponse[i++]; // continue the search for line feed 
		}
		nBytesInBuffer = i - 1;
		m_cResponse[i - 2] = NULL; // lose the line fieed carriage return
		sscanf_s(m_cResponse, "%lf,%lf", &dLamda, &dPower);
		m_MeasurementData.dWavelength[wLoopCount] = dLamda;
		m_MeasurementData.dNativeSpectrum[wLoopCount] = dPower;




	}

	GetLightDarkData();



	return TRUE;
}

bool CPRISpectro::GetLightDarkData()
{

	DWORD nBytesWritten, nBytesRead;
	BYTE testByte;
	short i,j;
	TRACE("GetLight Data\r\n ");
	WriteFile(m_ComPort, "D8\r\n", 6, &nBytesWritten, NULL); // Get light data 
	

	Clear_m_cResponse(); //Zero out the input buffer 
	testByte = NULL;
	i = 0;
	while (testByte != 0xa)
	{
		ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
	
		testByte = m_cResponse[i++]; // continue the search for line feed m_cResponse should contain 00000
	}
	Clear_m_cResponse();
	// get the number of elements from the hardware description 
	for (i = 0; i < m_SensorInfo.PRI_Number_Sensor_Elements;i++)
	{	
		j = 0;
		testByte = NULL;
		while (testByte != 0xa)
		{
			ReadFile(m_ComPort, &m_cResponse[j], 1L, &nBytesRead, NULL);
		
			testByte = m_cResponse[j++]; // continue the search for line feed 

		}
		// null terminate the response 
		m_cResponse[j - 2] = NULL; // subtract two because of the post index plus cr in the buffer 
		// now store the data in the measurement response 
		m_MeasurementData.LightRaw[i] = (WORD)atoi(m_cResponse);

	}
	TRACE("GetDark Data\r\n ");
	WriteFile(m_ComPort, "D9\r\n", 6, &nBytesWritten, NULL); // Get dark data 


	Clear_m_cResponse(); //Zero out the input buffer 
	testByte = NULL;
	i = 0;
	while (testByte != 0xa)
	{
		ReadFile(m_ComPort, &m_cResponse[i], 1L, &nBytesRead, NULL);
	
		testByte = m_cResponse[i++]; // continue the search for line feed m_cResponse should contain 00000
	}
	Clear_m_cResponse();
	// get the number of elements from the hardware description 
	for (i = 0; i < m_SensorInfo.PRI_Number_Sensor_Elements;i++)
	{
		j = 0;
		testByte = NULL;
		while (testByte != 0xa)
		{
			ReadFile(m_ComPort, &m_cResponse[j], 1L, &nBytesRead, NULL);

			testByte = m_cResponse[j++]; // continue the search for line feed 
		}
		// null terminate the response 
		m_cResponse[j - 2] = NULL; // subtract two because of the post index plus cr in the buffer 
								   // now store the data in the measurement response 
		m_MeasurementData.DarkRaw[i] = (WORD)atoi(m_cResponse);

	}

	// Calculate integrated light- dark data 
	SendGetCommand(PRI_GET_SENSOR_INFO, m_cResponse, LONG_TIMEOUT);
	BuildSensorInfoStruct();  // the sensor info is more  complex than the 
	TRACE(" Calculate integrated light- dark da\r\n ");
	m_MeasurementData.dIntegratedLightMinusDarkData = 0; 
	for (i = 0; i < m_SensorInfo.PRI_Number_Sensor_Elements;i++)
	{
		m_MeasurementData.dIntegratedLightMinusDarkData += (double)(m_MeasurementData.LightRaw[i] - m_MeasurementData.DarkRaw[i]);
	}

	//m_MeasurementData.dIntegratedLightMinusDarkData /= m_SensorInfo.PRI_Number_Sensor_Elements;

	return true; 
}
bool CPRISpectro::SetAdaptiveMode()
{

	char mp_cBuffer[1024];
	SendGetCommand(PRI_SET_ADAPTIVE_MODE, mp_cBuffer, SHORT_TIMEOUT);
	return true;
}
bool CPRISpectro::GetPhotoMetricData()
{
	SendGetCommand(PRI_GET_PHOTOMETRICDATA, m_cResponse, SHORT_TIMEOUT);
	ParsePhotometricData();
	return true; 
}

bool CPRISpectro::ParsePhotometricData()
{
	short i, j;
	i = 0;


	char mp_cBuffer[16];
	while (m_cResponse[i++] != 44); //move to first comma 

	j = 0;
	// get a single value 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL; // this is specified as a single value 0;
	i += 1;
	j = 0;
	// Get Y value;
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	m_PhotoMetricData.dLuminance = atof(mp_cBuffer);
	j = 0;
	i += 1;
	// get CTT value; 
	while (m_cResponse[i] != 44)
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	m_PhotoMetricData.dCCT = atof(mp_cBuffer);

	j = 0;
	i += 1;
	while (m_cResponse[i] != 13)//cr not comma
	{
		mp_cBuffer[j++] = m_cResponse[i++];
	}
	mp_cBuffer[j] = NULL;
	m_PhotoMetricData.dLocusDeviation = atof(mp_cBuffer);

	return true;
}
int  CPRISpectro::ParseToComma(char * inBuf, char* outBuf)
{
	short i=0;
	short j = 0;
	while (inBuf[i] != 44)
	{
		outBuf[j++] = inBuf[i++];
	}
	outBuf[j] = NULL;
	return(i+1);

}

int  CPRISpectro::ParseToCR_LF(char * inBuf, char* outBuf)
{
	short i = 0;
	short j = 0;
	while (inBuf[i] != 0x0a)
	{
		outBuf[j++] = inBuf[i++];
	}
	outBuf[j-1] = NULL;
	return(i+1);

}
void CPRISpectro::CalculateReferenceStatistics()
{
	//Reference data is located inside m_MeasureDataClass.m_ReferenceDataSet
	memset(&m_ReferenceStatisticsData, 0, sizeof m_ReferenceStatisticsData);
	m_ReferenceStatisticsData = m_MeasureDataClass.m_ReferenceDataSet[0];
	int iReps = m_MeasureDataClass.m_ReferenceDataSet[0].iReplicates;
	int i, j;
	double * CalcArray =  new double[iReps];  // allocate a data array for calcualtion of statistics; 
	double dMean;

	// Calculate the average spectral data arrays
	int iSpectralPoints = (int)((m_MeasureDataClass.m_ReferenceDataSet[0].DeviceDescriptor.dEndLamda -
		m_MeasureDataClass.m_ReferenceDataSet[0].DeviceDescriptor.dStartLamda) /
		m_MeasureDataClass.m_ReferenceDataSet[0].DeviceDescriptor.dLamdaIncrement);
	for (i = 0; i < iSpectralPoints; i++)
	{
		for (j = 0; j < iReps; j++)
			CalcArray[j] = m_MeasureDataClass.m_ReferenceDataSet[j].dNativeSpectrum[i];
		dMean = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
		m_ReferenceStatisticsData.dNativeSpectrum[i] = dMean;

	}
	//Calculate the mean and standard deviation of the XYZ and xy Data
	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].XYZdata.X;
	m_ReferenceStatisticsData.Xavg = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.Xstdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].XYZdata.Y;
	m_ReferenceStatisticsData.Yavg = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.Ystdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	//calculate in English units for 
	for(i = 0; i < iReps; i++)
	CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].XYZdata.Y / (10.76 / 3.14592654);
	m_ReferenceStatisticsData.dMeasuredLuminanceEnglish = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.dMeasuredLuminanceEnglishStdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].XYZdata.Z;
	m_ReferenceStatisticsData.Zavg = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.Zstdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].YxyData.x;
	m_ReferenceStatisticsData.xavg = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.xstdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].YxyData.y;
	m_ReferenceStatisticsData.yavg = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.ystdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].dRadiance;
	m_ReferenceStatisticsData.dRadiance = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.dRadianceStandardDeviation = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].dTargetLuminanceEnglish;
	m_ReferenceStatisticsData.dTargetLuminanceEnglish = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.dTargetLuminanceEnglishStdev = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);

	m_ReferenceStatisticsData.dLuminanceRatio = m_ReferenceStatisticsData.dMeasuredLuminanceEnglish / m_ReferenceStatisticsData.dTargetLuminanceEnglish;
	
	for (i = 0; i < iReps; i++)
		CalcArray[i] = m_MeasureDataClass.m_ReferenceDataSet[i].dResponsivity;
	m_ReferenceStatisticsData.dResponsivity = m_MeasureDataClass.ComputeMean(CalcArray, iReps);
	m_ReferenceStatisticsData.dStandardDeviationResponsivity = m_MeasureDataClass.ComputeStandardDeviation(CalcArray, iReps);


	delete[] CalcArray;

}

int  CPRISpectro::GetApertureList()
{
	
	/********************************************************************\
	Output Example:
	00000,0,2 deg,0.00
	00000,1,1 deg,0.00
	00000,2,0.2 deg,0.00
	00000,3,0.1 deg,0.00
	\********************************************************************/
	char  outBuffer[2048];
	char  *mp_cBuffer;
	int   iResponseLength,iCount,iOffset;
	int j;
	SendGetCommand(PRI_GET_APERTURE_LIST, outBuffer, LONG_TIMEOUT);
	//return data is in m_cResponse
	iResponseLength = strlen(m_cResponse);
	iCount = 0; 
	mp_cBuffer = m_cResponse;// virtualize m_cResponse 
	j = 0;
	
	while(mp_cBuffer[0] != 0)
	{ 
		iOffset = ParseToComma(mp_cBuffer, outBuffer);  //ignore first word 
		mp_cBuffer += iOffset; 
		iCount += iOffset;
		iOffset = ParseToComma(mp_cBuffer, outBuffer); // outbuffer should now be the index 
		mp_cBuffer += iOffset;
		iCount += iOffset;
		m_ApertureList.iIndex[j] = atoi(outBuffer);
		iOffset = ParseToComma(mp_cBuffer, outBuffer); // get degree string 
		mp_cBuffer += iOffset;
		iCount += iOffset;
		m_ApertureList.csApertureList[j]=outBuffer;
		iOffset = ParseToCR_LF(mp_cBuffer, outBuffer);
		mp_cBuffer += iOffset; 
		iCount += iOffset;
		j++;
	}
	m_ApertureList.ApertureListCount = j;

	return(m_ApertureList.ApertureListCount);

}
bool  CPRISpectro::TriggerMeasurement()
{
	SendGetCommand(PRI_TRIGGER,m_cResponse,SHORT_TIMEOUT);
	return true; 
	
	
};
bool  CPRISpectro::IsMeasurementComplete()
{
	SendGetCommand(PRI_MONITOR_PROCESS,m_cResponse,SHORT_TIMEOUT);
	bool bRet;
	// convert response to bool and return 
	if (strstr(m_cResponse,"1"))
		bRet = false;
	else 
		bRet = true;

	return bRet;

}
;
bool   CPRISpectro::AbortMeasurement()
{

	SendGetCommand(PRI_ABORT,m_cResponse,SHORT_TIMEOUT);

	return true;
};

bool   CPRISpectro::SetIntegrationTime(int iSecs)
{
	char cBuf[16],cBuf1[16];
	strcpy_s(cBuf, 16, csPRI_COMMAND[PRI_SELECT_EXPOSURE_TIME]);
	_itoa(iSecs, cBuf1, 10);
	strcat(cBuf, cBuf1);
	SendGetExplicitCommand(cBuf, m_cResponse, SHORT_TIMEOUT); 
	if (strstr(m_cResponse, "0000"))
		return true;
	else
		return false;

}