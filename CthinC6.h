#pragma once
#include "i1d3SDK.h"

struct EDR_HEADER       // 600
{
	BYTE Signature[16]; // 0    - 16   "EDR DATA1"
	DWORD ProgramVer;   // 16   - 4    0001
	DWORD FileVer;      // 20   - 4    0001
	DWORD Date;         // 24   - 4    since epoch
	DWORD N1;           // 28   - 4
	BYTE Creator[64];   // 32   - 64   string
	BYTE Comment[256];  // 96   - 256  string
	DWORD Technology;   // 352  - 4    1-22
	DWORD Sets;         // 356  - 4    1-NN sets of DISPLAY_DATA/SPECTAL_DATA
	BYTE Model[64];     // 360  - 64   string
	BYTE Mfg[64];       // 424  - 64   string
	BYTE SN[64];        // 488  - 64   string
	DWORD Size;         // 552  - 4    not sure size of what ???
	WORD Display;       // 556  - 2    bit flag TRUE/FALSE
	WORD Spectral;      // 558  - 2    bit flag TRUE/FALSE
	double Start;       // 560  - 8    start of spd 380
	double End;         // 568  - 8    end of spd 780
	double Increment;   // 576  - 8    nm increment 1,2,3,5,10
	double D1;          // 584  - 8
	double D2;          // 592  - 8
};

struct DISPLAY_DATA     // 128
{
	BYTE Signature[16]; // 0    - 16  "DISPLAY DATA"
	BYTE Name[64];      // 16   - 64  string
	WORD Red;           // 80   - 2   red bit level 0-255, 0-1023
	WORD Green;         // 82   - 2   green bit level 0-255, 0-1023
	WORD Blue;          // 84   - 2   blue bit level 0-255, 0-1023
	WORD Type;          // 86   - 2   "x" ???
	double Y;           // 88   - 8   measured Y value 1931
	double x;           // 96   - 8   measured x value
	double y;           // 104  - 8   measured y value
	double D1;          // 112  - 8
	double D2;          // 120  - 8
};

struct SPECTRAL_DATA
{
	BYTE Signature[16]; // 0    - 16 "SPECTRAL DATA"
	DWORD Samples;      // 16   - 4  341,401, etc...
	DWORD N1;           // 20   - 4
	DWORD N2;           // 24   - 4
	// double data;        // 28   - 8 * Samples
};

typedef enum //from CalMANv6.h
{
	ERR_NONE,
	ERR_TYPE,		    // 1	"Meter or Source is not supported"
	ERR_DLL,		    // 2	"Dll was not found"
	ERR_WRONG,		    // 3	"Dll version is not suppoted"
	ERR_PROC,		    // 4	"Dll procedure address not found"
	ERR_METER,		    // 5	"Meter not found or connected"
	ERR_READ,		    // 6	"Read error"
	ERR_MODE,		    // 7	"Meter mode not supported"
	ERR_DARK,		    // 8	"Meter Dark Calibration failed"
	ERR_SOURCE,		    // 9	"Source not found, please reset the source device"
	ERR_SET,		    // 10	"Source patten set failed"
	ERR_COMM,		    // 11	"Comm port failed"
	ERR_DISPLAY,	    // 12	"Display not found"
	ERR_LICENSE,	    // 13	"Device not licensed"
	ERR_XML,		    // 14	"XML file load error"
	ERR_MISSING,	    // 15	"Missing a required argument"
	ERR_OLDDLL,		    // 16	"A newer DLL is required"
	ERR_NODARK,		    // 17	"Meter Dark Calibration Required"
	ERR_NOCRT,		    // 18	"Meter CRT Sync Required"
	ERR_IO,			    // 19	"Device IO failed"
	ERR_OBJECT,		    // 20	"Object pointer NULL"
	ERR_TABLE,		    // 21	"Missing Calibration Table"
	ERR_TIMEOUT,	    // 22	"Auto Sense Timeout"
	ERR_MAX,		    // 23	"Maximum light reading error"
	ERR_BATTERY,	    // 24	"Dead Battery"
	ERR_HOLD,		    // 25	"Meter on Hold"
	ERR_LICENSE_METER,	// 26	"Meter license not found; Defaulting to Simulated meter; To check your licenses click on about icon"
	ERR_LICENSE_SOURCE,	// 27	"Source license not found; Defaulting to Simulated source; To check your licenses click on the about icon"
	ERR_S3UTILITY,		// 28	"S3 Utility needs to be disabled"
	ERR_USB,			// 29	"USB comm failed, disconnect/reconnect"
	ERR_CR,				// 30	"Photo Research Cosine Receptor option not installed"
	ERR_LENS,			// 31	"Error selecting Photo Research Primary Lens"
	ERR_EXPIRED,		// 32	"All licenses have expired"
	ERR_DLL_CS200,		// 33	"Konica Minolta CS-200 DLL missing"
	ERR_POINTER,		// 34	"Pointer light is on"
	ERR_DIFFUSER,		// 35	"diffuser must be installed"
	ERR_NODIFFUSER,		// 36	"diffser must be removed"
	ERR_VP_FIRMWARE,	// 37	"VideoPro firmware not sencore"
	ERR_POWERCYCLE,		// 38	"Cycle the power off/on"
	ERR_SET_SENCORE,	// 39	"Sencore source patten set failed"
	ERR_BATTERY_LOW,	// 40	"Low Battery"
	ERR_FILE_ACCESS,	// 41	"Remote file access error"
	ERR_NOT_USED_X,		// 42	""
	ERR_LICENSE_DISPLAY,// 43	"Display license not found;"
	ERR_UIRT,			// 44	"USB-UIRT device not found, please reset the USB-UIRT device"
	ERR_READ_STOPPED,	// 45	"Reading stopped because of user interrupt by holding down the ESC key"
	ERR_PATTERN_STOPPED,// 46	"Pattern update stopped because of user interrupt by holding down the ESC key"
	ERR_DLL_CA210,		// 47	"Konica Minolta CA-210 DLL missing"
	ERR_SENCORE_ATSC,	// 48	"Pattern not supported by the VP403 in ATSC mode"
	ERR_TABLE_SENCORE,	// 49	"Missing Calibration Table, Contact Sencore"
	ERR_TABLE_CALMAN,	// 50	"Missing Calibration Table, Contact SpectraCal"
	ERR_CMS_DARK,		// 51	"ColorMunki Spectro dark calibrate error"
	ERR_CMS_POSITION,	// 52	"ColorMunki Spectro sensor selector position error"
	ERR_INSTANCE,		// 53	"Can't have more than one instance of the same meter"
	ERR_FIRMWARE,		// 54	"Device firmware not up todate"
	ERR_SOCKET,			// 55	"Socket failed"
	ERR_TABLE_EX,		// 56	"Missing external calibration table get from server"
	ERR_MODEL,			// 57	"Model not supported"
	ERR_PASSWORD,		// 58	"Password update failed"
	ERR_CONNECTION,	    // 59	"Display connection timed out"
	ERR_TABLE_INSTALL,	// 60	"Missing external calibration table from install"
	ERR_REMOTE_MODE,	// 61   "Error - Source not found. Need to enable 'Remote Ctrl' mode."
	ERR_SET_FRAME,		// 62	"Source frame set failed"
	ERR_CRT,			// 63	"CRT scan rate sync error"
	ERR_CRT_LOW,		// 64	"CRT scan rate sync 
	ERR_LICENSE_CLIENT,	// 65	"Client not licensed"
	ERR_SYNC,			// 66	"Sync error"
	ERR_INUSE,			// 67	"In use by another app"
	ERR_POWER,			// 68	"USB power error"
	ERR_LOCKED,			// 69	"Locked"
	ERR_ADMIN,			// 70	"Operation requires Administrator Privileges"
	ERR_FILE,			// 71	"General file read/write issue"
	ERR_LUT_SIZE,		// 72	"LUT size mismatch"
	ERR_LUT_POINTS,		// 73	"LUT points mismatch"
	ERR_LUT_DATA,		// 74	"LUT data error"
	ERR_LUT_HEADER,		// 75	"LUT header error"
	ERR_LUT,			// 76	"LUT not found"
	ERR_AUTO_SERIAL,	// 77	"Serial port auto discovery is no longer supported"
	ERR_LOADER,         // 78   "Loader Error, could be profile, LUTs or DATA"

	WRN_NONE = 1000,	// 1000	"First Warning"
	WRN_CRT,		    // 1001	"CRT scan rate sync warning"
	WRN_LOW,		    // 1002	"Low light reading warning"
	WRN_MAX,		    // 1003	"Maximum light reading warning"
	WRN_NODARK,		    // 1004	"Meter Dark Calibration Has Expired"
	WRN_RANGE,		    // 1005	"Values out of range"
	WRN_NITS,		    // 1006	"Should be in Nits or Foot Lamberts"
	WRN_LUX,		    // 1007	"Should be in Lux or Foot Candles"
	WRN_METER,		    // 1008	"Meter not found or connected"
	WRN_SOURCE,		    // 1009	"Source not found, please reset the source device"
	WRN_BATTERY,	    // 1010	"Low Battery"
	WRN_SYNC,		    // 1011	"Sync lost"
	WRN_ADAPTIVE,	    // 1012	"Adaptive exposure error"
	WRN_POINTER,	    // 1013	"Pointer light is on"
	WRN_RESYNC		    // 1014	"User sync prompt"
}ERRORS;

typedef enum
{
	LOADER_NONE = 1,
	LOADER_NAME,			// 02 "Exe name"
	LOADER_PATH,			// 03 "Application path"
	LOADER_USER,			// 04 "User name"
	LOADER_XML_CREATE,		// 05 "Base XML object failed create"
	LOADER_XML_LOAD,		// 06 "Base XMLs loading failed"
	LOADER_XML_USER,		// 07 "User XMLs loading failed"
	LOADER_LOGGING,			// 08 "Logging failed"
	LOADER_PROFILE,			// 09 "Profiles failed"
	LOADER_LUTS,			// 10 "LUTs failed"
	LOADER_LICENSE,			// 11 "Licenses failed"
	LOADER_DATA,			// 12 "Data path"
	LOADER_U3,				// 13 "U3 object failed"
	LOADER_DLL              // 14 "DLL failed"
}LOADER;
typedef enum  // from SCsensor.h
{
	MODE_NONE,
	MODE_CRT_DIRECT,				// 01	scan rate sync
	MODE_CRT_FRONT_PROJECTOR,		// 02	use a CRT cal table with no scan rate sync
	MODE_CRT_REAR_PROJECTOR,		// 03	scan rate sync
	MODE_PLASMA,					// 04	use a CRT cal table with no scan rate sync
	MODE_LCD_DIRECT,				// 05	LCD direct view
	MODE_AMBIENT,					// 06	i1Pro and i1Display2 only
	MODE_FRONT_PROJECTOR,			// 07	LCD or DLP
	MODE_REAR_PROJECTOR,			// 08	LCD or DLP
	MODE_REFLECTANCE,				// 09	i1Pro only
	MODE_LUMINANCE,					// 10	SIP Wideband Luminance
	MODE_CRT_FRONT_SCREEN,			// 11	CRT Facing screen
	MODE_FRONT_SCREEN,				// 12	LCD or DLP Facing screen
	MODE_ALL_TYPES,					// 13	All display types
	MODE_TEST,						// 14	Test mode for simulated meter
	MODE_MERCURY_LAMP,				// 15	Projectors with a Mercury Lamp
	MODE_PHOSPHOR,					// 16	Phosphor based display CRT and Plasma
	MODE_CAL_TABLE_0,				// 17	Direct access to Calibration matrix # 0
	MODE_CAL_TABLE_1,				// 18	Direct access to Calibration matrix # 1
	MODE_CAL_TABLE_2,				// 19	Direct access to Calibration matrix # 2
	MODE_CAL_TABLE_3,				// 20	Direct access to Calibration matrix # 3
	MODE_CAL_TABLE_4,				// 21	Direct access to Calibration matrix # 4
	MODE_CAL_TABLE_5,				// 22	Direct access to Calibration matrix # 5
	MODE_CAL_TABLE_6,				// 23	Direct access to Calibration matrix # 6
	MODE_CAL_TABLE_7,				// 24	Direct access to Calibration matrix # 7
	MODE_CAL_TABLE_8,				// 25	Direct access to Calibration matrix # 8
	MODE_CAL_TABLE_9,				// 26	Direct access to Calibration matrix # 9
	MODE_LED_BACKLIGHT,				// 27	White LED backlight direct view
	MODE_LED_PROJECTOR_SCREEN,		// 28	White LED lamp projector facing screen
	MODE_UNIT_TEST,					// 29	Unit testing
	MODE_WIDE_CCFL,					// 30	Wide Gamut CCFL LCD (Used in the Display3)
	MODE_RGB_BACKLIGHT,				// 31	RGB LED backlight direct view
	MODE_RGB_PROJECTOR_SCREEN,		// 32	RGB LED lamp projector facing screen
	MODE_PLASMA_60,					// 33	Plasma at 60hz
	MODE_PLASMA_50,					// 34	Plasma at 50hz
	MODE_SYNC,						// 35	Sync Mode (enable sync detector)
	MODE_PLASMA_48,					// 36	Plasma at 48hz
	MODE_PLASMA_72,					// 37	Plasma at 48hz
	MODE_PLASMA_96,					// 38	Plasma at 96hz
	MODE_LCD_100,					// 39	LCD at 100hz
	MODE_FRONT_SCREEN_SYNC,			// 40	DLP Facing screen with sync enabled
	MODE_LCD_120,					// 41	LCD at 120hz
	MODE_SYNC_AUTO,					// 42	Sync Mode (Auto detect)
	MODE_LCD_240,					// 43	LCD at 240hz
	MODE_PLASMA_120,				// 44	Plasma at 120hz
	MODE_RGBY_BACKLIGHT,			// 45	RGBY LED backlight direct view
	MODE_LED_PROJECTOR,				// 46	White LED lamp projector facing projector
	MODE_RGB_PROJECTOR,				// 47	RGB LED lamp projector facing projector
	MODE_LED_REAR_PROJECTOR,		// 48	White LED lamp rear projector
	MODE_WIDE_LED,					// 49	Wide Gamut White LED backlight direct view
	MODE_CAL_TABLE_10,				// 50	Direct access to Calibration matrix # 10
	MODE_CAL_TABLE_11,				// 51	Direct access to Calibration matrix # 11
	MODE_CAL_TABLE_12,				// 52	Direct access to Calibration matrix # 12
	MODE_CAL_TABLE_13,				// 53	Direct access to Calibration matrix # 13
	MODE_CAL_TABLE_14,				// 54	Direct access to Calibration matrix # 14
	MODE_CAL_TABLE_15,				// 55	Direct access to Calibration matrix # 15
	MODE_CAL_TABLE_16,				// 56	Direct access to Calibration matrix # 16
	MODE_CAL_TABLE_17,				// 57	Direct access to Calibration matrix # 17
	MODE_CAL_TABLE_18,				// 58	Direct access to Calibration matrix # 18
	MODE_CAL_TABLE_19,				// 59	Direct access to Calibration matrix # 19
	MODE_CAL_TABLE_20,				// 60	Direct access to Calibration matrix # 20
	MODE_CAL_TABLE_21,				// 61	Direct access to Calibration matrix # 21
	MODE_CAL_TABLE_22,				// 62	Direct access to Calibration matrix # 22
	MODE_CAL_TABLE_23,				// 63	Direct access to Calibration matrix # 23
	MODE_CAL_TABLE_24,				// 64	Direct access to Calibration matrix # 24
	MODE_CAL_TABLE_25,				// 65	Direct access to Calibration matrix # 25
	MODE_CAL_TABLE_26,				// 66	Direct access to Calibration matrix # 26
	MODE_CAL_TABLE_27,				// 67	Direct access to Calibration matrix # 27
	MODE_CAL_TABLE_28,				// 68	Direct access to Calibration matrix # 28
	MODE_CAL_TABLE_29,				// 69	Direct access to Calibration matrix # 29
	MODE_CAL_TABLE_30,				// 70	Direct access to Calibration matrix # 30
	MODE_CAL_TABLE_31,				// 71	Direct access to Calibration matrix # 31
	MODE_CAL_TABLE_32,				// 72	Direct access to Calibration matrix # 32
	MODE_CAL_TABLE_33,				// 73	Direct access to Calibration matrix # 33
	MODE_CAL_TABLE_34,				// 74	Direct access to Calibration matrix # 34
	MODE_CAL_TABLE_35,				// 75	Direct access to Calibration matrix # 35
	MODE_CAL_TABLE_36,				// 76	Direct access to Calibration matrix # 36
	MODE_CAL_TABLE_37,				// 77	Direct access to Calibration matrix # 37
	MODE_CAL_TABLE_38,				// 78	Direct access to Calibration matrix # 38
	MODE_CAL_TABLE_39,				// 79	Direct access to Calibration matrix # 39
	MODE_OLED_DIRECT,				// 80	Direct drive OLED
	MODE_OLED_RGB,					// 81	Backlight RGB OLED
	MODE_OLED_WHITE,				// 82	Backlight White OLED
	MODE_P3_CCFL,					// 83	P3 Gamut CCFL
	MODE_GB_BACKLIGHT,				// 84	Green/Blue LED backlight
	MODE_WIDE_RGB_BACKLIGHT,		// 85	LCD RGB WIDE
	MODE_RANDOM_TEST,				// 86	Randon unit testing
	MODE_BG_BACKLIGHT,				// 87	LCD BG LED
	MODE_EQUAL_TEST,				// 88	Equal Energy testing
	MODE_ZBOOK,                     // 89   HP zBook Dreamcolor
	MODE_WHITE_OLED,                // 90   LG White OLED
	MODE_QD,                        // 91   Visio QD
	MODE_PFS,                       // 92   PFS LED (potassium fluorosilicate)
	MODE_PJ_LASER_RZ12K,            // 93   Panasonic-RZ12K-LaserPhosphor
	MODE_PJ_LASER_RZ970,            // 94   Panisonic-RZ970-LaserPhosphor
	MODE_PJ_XENON,                  // 95   Barco-HDXW20-Xenon
	MODE_QD_SAMSUNG15,              // 96   Samsung 2015 QD
	MODE_QD_SAMSUNG16,              // 97   Samsung 2016 QD
	MODE_QD_SAMSUNG17,              // 98   Samsung 2017 QD
	MODE_HPDC3,                     // 99   HP DreamColor III
	MODE_ZBOOK_G5,					// 100  HP DreamColor zBook G5 EDR (2018) 
	MODE_CAL_TABLE_40 = 101,		// 100	Direct access to Calibration matrix # 40
	MODE_CAL_TABLE_41,				// 101	Direct access to Calibration matrix # 41
	MODE_CAL_TABLE_42,				// 102	Direct access to Calibration matrix # 42
	MODE_CAL_TABLE_43,				// 103	Direct access to Calibration matrix # 43
	MODE_CAL_TABLE_44,				// 104	Direct access to Calibration matrix # 44
	MODE_CAL_TABLE_45,				// 105	Direct access to Calibration matrix # 45
	MODE_CAL_TABLE_46,				// 106	Direct access to Calibration matrix # 46
	MODE_CAL_TABLE_47,				// 107	Direct access to Calibration matrix # 47
	MODE_CAL_TABLE_48,				// 108	Direct access to Calibration matrix # 48
	MODE_CAL_TABLE_49,				// 109	Direct access to Calibration matrix # 49
	MODE_CAL_TABLE_50,				// 110	Direct access to Calibration matrix # 50
	MODE_CAL_TABLE_51,				// 111	Direct access to Calibration matrix # 51
	MODE_CAL_TABLE_52,				// 112	Direct access to Calibration matrix # 52
	MODE_CAL_TABLE_53,				// 113	Direct access to Calibration matrix # 53
	MODE_CAL_TABLE_54,				// 114	Direct access to Calibration matrix # 54
	MODE_CAL_TABLE_55,				// 115	Direct access to Calibration matrix # 55
	MODE_CAL_TABLE_56,				// 116	Direct access to Calibration matrix # 56
	MODE_CAL_TABLE_57,				// 117	Direct access to Calibration matrix # 57
	MODE_CAL_TABLE_58,				// 118	Direct access to Calibration matrix # 58
	MODE_CAL_TABLE_59,				// 119	Direct access to Calibration matrix # 59
	MODE_CAL_TABLE_60,				// 120	Direct access to Calibration matrix # 60
	MODE_CAL_TABLE_61,				// 121	Direct access to Calibration matrix # 61
	MODE_CAL_TABLE_62,				// 122	Direct access to Calibration matrix # 62
	MODE_CAL_TABLE_63,				// 123	Direct access to Calibration matrix # 63
	MODE_CAL_TABLE_64,				// 124	Direct access to Calibration matrix # 64
	MODE_CAL_TABLE_65,				// 125	Direct access to Calibration matrix # 65
	MODE_CAL_TABLE_66,				// 126	Direct access to Calibration matrix # 66
	MODE_CAL_TABLE_67,				// 127	Direct access to Calibration matrix # 67
	MODE_CAL_TABLE_68,				// 128	Direct access to Calibration matrix # 68
	MODE_CAL_TABLE_69,				// 129	Direct access to Calibration matrix # 69
	MODE_CAL_TABLE_70,				// 130	Direct access to Calibration matrix # 70
	MODE_CAL_TABLE_71,				// 131	Direct access to Calibration matrix # 71
	MODE_CAL_TABLE_72,				// 132	Direct access to Calibration matrix # 72
	MODE_CAL_TABLE_73,				// 133	Direct access to Calibration matrix # 73
	MODE_CAL_TABLE_74,				// 134	Direct access to Calibration matrix # 74
	MODE_CAL_TABLE_75,				// 135	Direct access to Calibration matrix # 75
	MODE_CAL_TABLE_76,				// 136	Direct access to Calibration matrix # 76
	MODE_CAL_TABLE_77,				// 137	Direct access to Calibration matrix # 77
	MODE_CAL_TABLE_78,				// 138	Direct access to Calibration matrix # 78
	MODE_CAL_TABLE_79,				// 139	Direct access to Calibration matrix # 79
	MODE_CAL_TABLE_80,				// 140	Direct access to Calibration matrix # 80
	MODE_CAL_TABLE_81,				// 141	Direct access to Calibration matrix # 81
	MODE_CAL_TABLE_82,				// 142	Direct access to Calibration matrix # 82
	MODE_CAL_TABLE_83,				// 143	Direct access to Calibration matrix # 83
	MODE_CAL_TABLE_84,				// 144	Direct access to Calibration matrix # 84
	MODE_CAL_TABLE_85,				// 145	Direct access to Calibration matrix # 85
	MODE_CAL_TABLE_86,				// 146	Direct access to Calibration matrix # 86
	MODE_CAL_TABLE_87,				// 147	Direct access to Calibration matrix # 87
	MODE_CAL_TABLE_88,				// 148	Direct access to Calibration matrix # 88
	MODE_CAL_TABLE_89,				// 149	Direct access to Calibration matrix # 89
	MODE_CAL_TABLE_90,				// 150	Direct access to Calibration matrix # 90
	MODE_CAL_TABLE_91,				// 151	Direct access to Calibration matrix # 91
	MODE_CAL_TABLE_92,				// 152	Direct access to Calibration matrix # 92
	MODE_CAL_TABLE_93,				// 153	Direct access to Calibration matrix # 93
	MODE_CAL_TABLE_94,				// 154	Direct access to Calibration matrix # 94
	MODE_CAL_TABLE_95,				// 155	Direct access to Calibration matrix # 95
	MODE_CAL_TABLE_96,				// 156	Direct access to Calibration matrix # 96
	MODE_CAL_TABLE_97,				// 157	Direct access to Calibration matrix # 97
	MODE_CAL_TABLE_98,				// 158	Direct access to Calibration matrix # 98
	MODE_CAL_TABLE_99,				// 159	Direct access to Calibration matrix # 99

	MODE_LAST						// 160
} METERMODES;
#if 0 // captured from CDA 2

m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_0, L"Factory Raw RGB"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_1, L"Factory CMF 1932 2deg XYZ"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_2, L"First Loaded EDR"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_LCD_DIRECT, L"LCD CCFL"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_CCFL, L"LCD CCFL Wide"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_LED_BACKLIGHT, L"LCD White LED"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_RGB_BACKLIGHT, L"LCD RGB LED (HP DreamColor)"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_FRONT_SCREEN, L"Projector UHP"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CRT_DIRECT, L"CRT"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PLASMA, L"Plasma"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_LED_PROJECTOR_SCREEN, L"Projector White LED"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_RGB_PROJECTOR_SCREEN, L"Projector RGB LED"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_LED, L"LCD White LED Wide"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_OLED_DIRECT, L"OLED Direct Drive"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_P3_CCFL, L"DC/P3 CCFL (FSI)"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_RGB_BACKLIGHT, L"LCD RGB LED Wide"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_BG_BACKLIGHT, L"LCD BG LED Wide"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_ZBOOK, L"HP zBook"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WHITE_OLED, L"LG White OLED, ZBOOK"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_QD, L"Visio QD"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PFS, L"LED PFS"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PJ_LASER_RZ12K, L"Panasonic-RZ12K-LaserPhosphor"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PJ_LASER_RZ970, L"Panasonic-RZ970-LaserPhosphor"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PJ_XENON, L"Barco-HDXW20-Xenon"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_QD_SAMSUNG15, L"Samsung 15"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_QD_SAMSUNG16, L"Samsung 16"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_QD_SAMSUNG17, L"Samsung 17"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_HPDC3, L"HP DreamColor III"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_ZBOOK_G5, L"HP DreamColor zBook G5 EDR (2018)"));
m_C6Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_9, L"Test EDR"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_0, L"Factory Raw RGB"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_1, L"Factory CMF 1932 2deg XYZ"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_2, L"First Loaded EDR"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_LCD_DIRECT, L"LCD CCFL"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_CCFL, L"LCD CCFL Wide"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_LED_BACKLIGHT, L"LCD White LED"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_RGB_BACKLIGHT, L"LCD RGB LED "));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_FRONT_SCREEN, L"Projector UHP"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CRT_DIRECT, L"CRT"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_PLASMA, L"Plasma"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_LED, L"LCD White LED Wide"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_OLED_DIRECT, L"OLED Direct Drive"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_WIDE_RGB_BACKLIGHT, L"LCD RGB LED Wide"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_BG_BACKLIGHT, L"LCD BG LED Wide"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_ZBOOK, L"HP zBook"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_HPDC3, L"HP DreamColor III"));
m_I1Edrs.push_back(std::pair<int, std::wstring>(CalSensor::MODE_CAL_TABLE_9, L"Test EDR"));
#endif
typedef struct EDR_LIST_ELEMENT
{
	int EDR_ENUM;
	char *EDR_NAME;

}EDR_LIST_VALUE;



 static int EDRVALUE[] = {
		MODE_CAL_TABLE_0,
		MODE_CAL_TABLE_1,
		MODE_CAL_TABLE_2,
		MODE_LCD_DIRECT,
		MODE_WIDE_CCFL,
		MODE_LED_BACKLIGHT,
		MODE_RGB_BACKLIGHT,
		MODE_FRONT_SCREEN,
		MODE_CRT_DIRECT,
		MODE_PLASMA,
		MODE_LED_PROJECTOR_SCREEN,
		MODE_RGB_PROJECTOR_SCREEN,
		MODE_WIDE_LED,
		MODE_OLED_DIRECT,
		MODE_P3_CCFL,
		MODE_WIDE_RGB_BACKLIGHT,
		MODE_BG_BACKLIGHT,
		MODE_ZBOOK,
		MODE_WHITE_OLED,
		MODE_QD,
		MODE_PFS,
		MODE_PJ_LASER_RZ12K,
		MODE_PJ_LASER_RZ970,
		MODE_PJ_XENON,
		MODE_QD_SAMSUNG15,
		MODE_QD_SAMSUNG16,
		MODE_QD_SAMSUNG17,
		MODE_HPDC3,
		MODE_ZBOOK_G5,
		MODE_CAL_TABLE_9,
		MODE_CAL_TABLE_0,
		MODE_CAL_TABLE_1,
		MODE_CAL_TABLE_2,
		MODE_LCD_DIRECT,
		MODE_WIDE_CCFL,
		MODE_LED_BACKLIGHT,
		MODE_RGB_BACKLIGHT,
		MODE_FRONT_SCREEN,
		MODE_CRT_DIRECT,
		MODE_PLASMA,
		MODE_WIDE_LED,
		MODE_OLED_DIRECT,
		MODE_WIDE_RGB_BACKLIGHT,
		MODE_BG_BACKLIGHT,
		MODE_ZBOOK,
		MODE_HPDC3,
		MODE_CAL_TABLE_9,
};
 /*<Mode Key="MODE_LCD_DIRECT"        Name="LCD (CCFL)" Value="5" />
			<Mode Key="MODE_WIDE_CCFL"         Name="LCD (CCFL Wide Gamut)" Value="30" />
			<Mode Key="MODE_LED_BACKLIGHT"     Name="LCD (LED)" Value="27" />
			<Mode Key="MODE_RGB_BACKLIGHT"     Name="LCD (LED RGB)" Value="31" />
      <Mode Key="MODE_BG_BACKLIGHT"      Name="LCD (LED Blue Green)" Value="87" />
      <Mode Key="MODE_CRT_DIRECT"        Name="CRT" Value="1" />
			<Mode Key="MODE_OLED_DIRECT"       Name="OLED" Value="80" />
			<Mode Key="MODE_PLASMA_60"         Name="Plasma" Value="33" />
			<Mode Key="MODE_CRT_REAR"          Name="Rear Projector (CRT)" Value="3" />
			<Mode Key="MODE_REAR_PROJECTOR"    Name="Rear Projector (UHP)" Value="8" />
			<Mode Key="MODE_CRT_SCREEN"        Name="Front Projector (CRT)" Value="11" />
			<Mode Key="MODE_FRONT_SCREEN_SYNC" Name="Front Projector (UHP)" Value="40" />
			<Mode Key="MODE_CAL_TABLE_1"       Name="Raw XYZ" Value="18" />*/
 static char *EDRNAME[] = {

	"Factory Raw RGB", 
	"Factory CMF 1932 2deg XYZ"
	,"First Loaded EDR"
	,"LCD CCFL"
	,"LCD CCFL Wide"
	,"LCD White LED"
	"HP DreamCol"
	 ,"Projector UHP"
	,"CRT"
	,"Plasma"
	,"Projector White LED"
	,"Projector RGB LED"
	,"LCD White LED Wide"
	,"OLED Direct Drive"
	,"DC/P3 CCFL (FSI)"
	,"LCD RGB LED Wide"
	,"LCD BG LED Wide"
	,"HP zBook"
	,"LG White OLED, ZBOOK"
	,"Visio QD"
	,"LED PFS"
	,"Panasonic-RZ12K-LaserPhosphor"
	,"Panasonic-RZ970-LaserPhosphor"
	,"Barco-HDXW20-Xenon"
	,"Samsung 15"
	,"Samsung 16"
	,"Samsung 17"
	,"HP DreamColor III"
	,"HP DreamColor zBook G5 EDR (2018)"
	,"Test EDR"
	,"Factory Raw RGB"
	,"Factory CMF 1932 2deg XYZ"
	,"First Loaded EDR"
	,"LCD CCFL"
	,"LCD CCFL Wide"
	,"LCD White LED"
	,"LCD RGB LED "
	,"Projector UHP"
	,"CRT"
	,"Plasma"
	,"LCD White LED Wide"
	,"OLED Direct Drive"
	,"LCD RGB LED Wide"
	,"LCD BG LED Wide"
	,"HP zBook"
	, "HP DreamColor III"
	, "Test EDR"
};
 
#define N_EDRS		46

 /*<Device Key="METER_D3CM" Manufacture="X-Rite" Model="ColorMunki Display (DEV ONLY)" Value="72" SerialKey="" Dll="i1d3.dll">
		<Setup  Dx="-0.00476" Dy="-0.00417" DY="4.244" Ymin="0.0001" Ymax="10000" Emin="0.1" Emax="5"
		  Notes="If you are getting readings that are inconsistent try enabling or disabling meter Sync. By default we set the sync by display type but we do find the need to explicitly to enable or disable as needed."/>

		<Type Instance="DISPLAY3" Luminance="0" Tristimulus="1" Spectrometer="0" Button="0" Sync="3"/>
		<Modes>
			<Mode Key="MODE_LCD_DIRECT"        Name="LCD (CCFL)" Value="5" />
			<Mode Key="MODE_WIDE_CCFL"         Name="LCD (CCFL Wide Gamut)" Value="30" />
			<Mode Key="MODE_LED_BACKLIGHT"     Name="LCD (LED)" Value="27" />
			<Mode Key="MODE_RGB_BACKLIGHT"     Name="LCD (LED RGB)" Value="31" />
			<Mode Key="MODE_CRT_DIRECT"        Name="CRT" Value="1" />
			<Mode Key="MODE_OLED_DIRECT"       Name="OLED" Value="80" />
			<Mode Key="MODE_PLASMA_60"         Name="Plasma" Value="33" />
			<Mode Key="MODE_CRT_REAR"          Name="Rear Projector (CRT)" Value="3" />
			<Mode Key="MODE_REAR_PROJECTOR"    Name="Rear Projector (UHP)" Value="8" />
			<Mode Key="MODE_CRT_SCREEN"        Name="Front Projector (CRT)" Value="11" />
			<Mode Key="MODE_FRONT_SCREEN_SYNC" Name="Front Projector (UHP)" Value="40" />
			<Mode Key="MODE_CAL_TABLE_1"       Name="Raw XYZ" Value="18" />*/
 typedef BOOL(__stdcall *DecryptToCallback)(char *, char *);
 extern DecryptToCallback DecryptTo;

class CthinC6
{
public:
	i1d3Handle		m_devHndl;
	i1d3Status_t		m_i1d3Status;
	i1d3XYZ_t			m_XYZdata;
	char			DataPath[MAX_PATH];
	char			m_cSN[64];
	long			m_lSN; 

	bool			m_bInitialized;
	int				m_iEDRvalue;
// functions 
					CthinC6();
					bool C6Initialize();
					bool C6Close();
	i1d3XYZ_t		C6MeasureXYZ();
	bool			C6GetSerialNumber();

	EDR_LIST_VALUE	m_EDR_LIST[64];
	
	i1d3CALIBRATION_ENTRY m_currentEntry;
	int					  m_numCals;
	i1d3CALIBRATION_LIST *m_calList;
	EDR_HEADER				m_EDRheader;

	bool			C6SetCalibrationEntry();
	bool			C6SetCalibrationEntry(unsigned char * cEDRFilePathsandName,char * key,short DisplayTypeEnum);
	bool			C6MSetEDR();
	bool			C6MSetEDRFile(unsigned char * cEDRFilePathsandName);
	bool            C6MSetEDR(BYTE* cEDRImage, ULONG ulLength);
	bool			C6MSetEDR(int whichEDR);
	
	int				C6MGetEDR();
	
	int EDR_WriteString(char *pEDRloc, char * cStringToWrite);
private:
	bool SetError(int whichError);
	bool LogWriteInfo(int value);
	bool RandomChar(unsigned char *inArray, int iLength);
	long status;
	bool DecryptTo;

	

};