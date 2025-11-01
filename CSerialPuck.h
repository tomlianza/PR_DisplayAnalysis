#pragma once
#define NotSkinny 1



/*•	SCP <gain> <index> - set calibration parameter
o	The gain is an index into which gain's parameters you want to access
o	The index is the index into the list of cal params
•	GCP - get calibration parameters. First is the current gain, the second is the current index
•	SCCE <CCM value> - set color cal entry, as a float.  This command always increments the index variable
o	First 9 entries are a11, a12, a13, a21,  etc.  The last 3 are offsets for removing channel dark offsets.   
•	GCCE <gain> <index> <CCM value> - get color cal entry as a float  This command always increments the index variable
E.g., to load an identity matrix into the gain 3 parameters:
SCP 3 0        set internal variables to gain=3, and index to 0
SCCE 1.0        a11 = 1.0 and index++
SCCE 0.0        a12 = 0.0 and index++
SCCE 0.0        s13    ...etc.
SCCE 0.0        s21
SCCE 1.0        a22
SCCE 0.0        a23
SCCE 0.0        a31
SCCE 0.0        a32
SCCE 1.0        a33
SCCE 0.0        r offset
SCCE 0.0        g offset
SCCE 0.0        b offset
•	The firmware uses gains 0 to 4 for the ambient readings.  I left the strobe gain params, 5 to 7, as extra space.  You can use them to store your cal data.  
•	You MUST make the offsets between -10 and -80.  If they aren't, the firmware will decide the calibration data is corrupt and overwrite it all with defaults.  With theAS73211, the offset should be 0.0.  So that's a firmware bug...
#define    CAL_CTRLR_CCM_CHECK_LIMIT_UPPER                 10.0f
#define    CAL_CTRLR_CCM_CHECK_LIMIT_LOWER                -10.0f
#define    CAL_CTRLR_CCM_OFFSET_CHECK_LIMIT_UPPER        -10.0f
#define    CAL_CTRLR_CCM_OFFSET_CHECK_LIMIT_LOWER        -80.0f


*/







typedef enum SG_Enums {
	G1 = 0,
	G2,
	G4,
	G8,
	G16,
	G32,
	G64,
	G128,
	G256,
	G512,
	G1024,
	G2048,
	GNUM
}SG_ENUM;
typedef enum ST_Enums {
	IT_0 = 0,// 1ms
	IT_1,
	IT_2,
	IT_3,
	IT_4,  //16 ms 2^IT_4
	IT_5,
	IT_6,
	IT_7,
	IT_8,
	IT_9,
	IT_10,
	//IT_11, ///
	IT_NUM
	
}ST_ENUM;

typedef enum CommandStringEnum
{
	cs_tar = 0,
	cs_nra,
	cs_grdn,
	cs_sste,
	cs_gste,
	cs_ssr,
	cs_gsr,
	cs_sagc,
	cs_gagc,
	cs_gnagi,
	cs_sg,
	cs_gg,
	cs_gngl,
	cs_st,
	cs_gt,
	cs_gnitl,
	cs_scp,
	cs_gcp,
	cs_scce,
	cs_gcce



}CMDSTRENUM;




typedef enum AutoCalLightLightLevel
{
		AC_LOW = 0,
		AC_MEDIUM = 1,
		AC_HIGH = 2

}AUTOLIGHTLEVEL;

class CSerialPuck
{
public:
	// High level functions

	bool OpenCommPort(int PortNumber);
	bool Get3DecimalData();// Raw data , use low level commands to set gain and intTime data is not altered by gain and int time.  
	bool Get3DecimalAutoRangeData();  // this takes two measurements to determine the best gain and intime from the hard coded values data is normalized by gain and int time. 
	bool GetYxyData();
	bool GetXYZData();
	


		// High level data arrays 
	double m_dOutValues[3];// raw device data , un normalized when Get3DecimalData is called. normalized when the AutoRangeData is called 
	double m_dXYZdata[3]; // processed by matrix mult 
	double m_dYxydata[3];
	char   m_cInOutBuffer[1024];  // used for debugging this shows the output text from the puck
	// data used for calculation of High Level arrays listed above. 

	int		m_iCurrentMatrix;  // generally points to 1 of 3 arrays stored at offset 5,6,7 in the puck.  
	double m_CurrentIntTime;  // set by AutoRange Fucnction
	double m_CurrentGain;		// Set by AutoRange function 
	
	double m_3X3_RAW2XYZ[3][9];//calibration matricies from puck 
	//int    m_MatrixChannel; // note this is scaled 0->2 in the interface but physically stored in loc 5 to 7 in the puck 
	double m_CurrentRaw2XYZmatrix[9];

	ST_ENUM	m_STintegrationTime;
	SG_ENUM	m_SGgain;

	int     m_iIntegrationTimeNStrings;
	int     m_iGainNStrings;

	
	bool		m_bMeasurementError; 
	char		m_ErrorMessage[1024];
	char		m_cDebugMessage[2048];
	bool		m_bComPortOpen;
	HANDLE		m_HComPort;
	
	CSerialPuck();
	
	void Set3X3Matrix(int channel, double * d3X3Matrix);  // channel 5 6 or 7
	void Get3X3Matrix(int channel, double * d3X3Matrix);  // channel 5 6 7
	void TriggerMeasurement();
	bool IsMeasurementComplete();
	void DisableAutoGain();// this disables the auto gain function in firmware.  
	bool SendGet(char * cInOutBuffer);
	bool SendGet(char * cInOutBuffer,int delayMS);

	// TBD void SendGet(CMDSTRENUM whichCMD, char *cInOutBuffer, int i_apendedArgument);
	
	bool CommErrorDisplay(char * cErrorMessage);
	
	// low level control functions 
	void SetGainTimeCombo(AUTOLIGHTLEVEL whichLevel);
	void SetGain(char *cGain);  // a character to append to command 
	void SetGain(int  iGain); // integer input to append 
	void SetGain(SG_ENUM whichGain);// enumeration converts to char and then uses the SetGain(char) function 

	void SetIntTime(char *cTime);// as with the gain command 
	void SetIntTime(ST_ENUM whichIntTime);
	void SetIntTime(int iTime);
	// data definitions 

	 double dGain[12] = {
		1.,2.,4.,8.,16.,32.,64.,128.,256.,512.,1024.,2048.
	};

	 double dIntTimeMS[11] = {
		1.,2.,4.,8.,16.,32.,64.,128.,256.,512.,1024.
	};
#if NotSkinny
	char *cIntTimeStrings[11] =
	{
		"1ms",
		"2ms",
		"4ms",
		"8ms",
		"16ms",
		"32ms",
		"64ms",
		"128ms",
		"256ms",
		"512ms",
		"1024ms",
		//"2048ms"

	};

	char *cGainStrings[12] =// these strings can be used for pull down menus, the string points to enumeration 
	{
		"1" ,
		"2",
		"4",
		"8",
		"16",
		"32",
		"64",
		"128",
		"256",
		"512",
		"1024",
		"2048"
	};
#endif
private:
	bool					AutoRange();// this routine will find the best gain and int time combination from the three 
	void                    ReorderOutVals(); // this puts the data into XYZ order 
	
	CFile					m_cfDebug;
	CFileException			m_cfex;
	typedef struct GainIntTime // index to double arrays of gain and int time 
	{
		int GainIndex;
		int IntTimeIndex;

	}GAININTTIME;

	typedef struct dGainIntTime  // physical values for gain and int time
	{
		double dGain;
		double dIntTime;

	}DGAININTTIME;


	// this is initialized in the constructor;
	DGAININTTIME	m_dAutoRange[3];  // these values are the physical double gain and intime values used to produce the calibration matrix. 
	GAININTTIME		m_AutoRange[3];  // these are the index into the gain and intTime arrays

	
	
	

	char * Parse2Character(char * ch, char** cPtrInString);
	void ParseDvaluesFromString(char * cPtrInString);
	int MatMult(double *, int, int, double *, int, int, double *);

};