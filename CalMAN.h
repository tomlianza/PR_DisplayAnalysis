/* CalMAN.h
 *
 * Copyright (c) 2005 - 2015 SpectraCal, LLC www.SpectraCal.com
 * Copyright (c) 2016 SpectraCal, Inc
 *
 * $History: CalMAN.h $
 *
 */

#pragma once

#ifndef AFX_CALMAN_H__20A005A9_8AB1_4341_807D_7CB9B59FF49A__INCLUDED_
#define AFX_CALMAN_H__20A005A9_8AB1_4341_807D_7CB9B59FF49A__INCLUDED_

#ifdef _WIN32
#define CMEXPORT __declspec(dllexport)
#else
#define EXPORT
#define __cdecl
#define __stdcall
#endif

#include "CM_Define.h"

#define PRODUCT_NAME   "CalMANv6"
#define COMPANY_NAME   "SpectraCal"
#define CALMAN_RELEASE TRUE
#define DATECODE_GUID  "{8C9FB95E-C3C6-4A63-823E-20C04C8AB028}"
#define CLIENT_GUID    "{5595714B-E1CB-4795-9FA4-726A9B4443AD}"

#define MINIMUM_Y  0.0001
#define MAX_SERIAL 4096

typedef enum
{
    METER_NONE,
    METER_S2,				// 01	ColorVision Spyder2, Spyder2Platinum
    METER_D2,				// 02	GretagMacbeth Display2, OEMed x-rite Gamma5
    METER_EYEONE,			// 03	GretagMacbeth i1Pro
    METER_DTP94,			// 04	x-rite DTP94
    METER_COLORPRO,			// 05	Sencore ColorPro II, OEMed SIP Chroma4
    METER_COLORPRO_III,		// 06	Sencore ColorPro III, OEMed SIP Chroma4
    METER_COLORPRO_IV,		// 07	Sencore ColorPro IV, OEMed SIP ChromaLCD
    METER_SIPCAL,			// 08	Generic SIPCAL from Sequal Imaging with no password protect
    METER_GAMMA5,			// 09	GretagMacbeth Display2 w/ CalMAN calibration tables
    METER_CHROMA5,			// 10	x-rite Chroma5 w/ CalMAN calibration tables
    METER_SIMULATED,		// 11	Simulated Test meter
    METER_PLC5,				// 12	Progressive Labs C5, OEMed x-rite Chroma5
    METER_XRC5,				// 13	x-rite Chroma5
    METER_COLORPRO_V,		// 14	Sencore ColorPro V, OEMed x-rite Chroma5
    METER_HUBBLE,			// 15	x-rite Hubble, Sencore OTC1000
    METER_MINOLTACM,		// 16	Minolta Chroma Meter CS-100A
    METER_CL200,			// 17	Minolta Light Meter CL-200
    METER_CS200,			// 18	Minolta Chroma Meter CS-200
    METER_CS1000,			// 19	Minolta Chroma Meter CS-1000
    METER_MONITOR,			// 20	GretagMacbeth i1 Monitor
    METER_S3,				// 21	DataColor Spyder3 Elite
    METER_PR,				// 22	Photo Research PR-650
    METER_PL6X,				// 23	Progressive Labs 6X, OEMed SIP Sigma RGB
    METER_CS2000,			// 24	Minolta Chroma Meter CS-2000
    METER_LX1108,			// 25	Lutron LX-105, LX-1108, Extech 407026 and others based on the same V1 or V2 protocol
    METER_LX1336,			// 26	Lutron LX-1336, TES-1336, Extech 401036 and others based on the same V3 protocol
    METER_PR655,			// 27	Photo Research PR-655
    METER_CMS,				// 28	Pantone Colormunki Spectro
    METER_USB4000,			// 29	Ocean Optics USB4000
    METER_PR670,			// 30	Photo Research PR-670
    METER_PR680,			// 31	Photo Research PR-680
    METER_CMT,				// 32	Pantone Colormunki TriStim
    METER_K10,				// 33	Klein Instruments K-1, K-8 and K-10
    METER_SP100,			// 34	Orb Optronix SP-100
    METER_PR705,			// 35	Photo Research PR-705
    METER_PR715,			// 36	Photo Research PR-715
    METER_SKYTV,			// 37	SkyTV OEM CalMAN G5 METER_GAMMA5
    METER_PR525,			// 38	Photo Research PR-525 with CS-525 or PR-523 lens
    METER_CA210,			// 39	Minolta Display Color Analyzer CA-210
    METER_LS100,			// 40	Minolta Light Meter LS-100
    METER_OTC1000,			// 41	Sencore OTC1000, OEMed x-rite Hubble
    METER_CES3,				// 42	CalMAN Enhanced S3 includes calibration tables
    METER_CEC5,				// 43	CalMAN Enhanced C5 includes LED table 4
    METER_SCRGB,			// 44	SipCal RGB
    METER_CECM,				// 45	CalMAN Enhanced ColorMunki Spectro includes LED table
    METER_CEI1,				// 46	CalMAN Enhanced i1Pro includes LED table
    METER_HUEY,				// 47	X-Rite Huey
    METER_SB1211,			// 48	Jeti Specbos 1211
    METER_BWTEK,			// 49	Base BW Tek Spectro
    METER_SP200,			// 50	Orb Optronix SP-200
    METER_SB1201,			// 51	Jeti Specbox 1201
    METER_PR701,			// 52	Photo Research PR-701
    METER_VIDEOSPEC,		// 53	AVF VideoSpec based on a BW Tek Spectro
    METER_SLS9400,			// 54	UDT Instruments SLS9400
    METER_CMX2,				// 55	CalMAN Enhanced Display2/Gamma5 X2 with 4 external cal tables
    METER_CMM2,				// 56	CalMAN Enhanced Display2/Gamma5 M2 with LED in place of CRT
    METER_LCDCAL,			// 57	Konica Minolta LCD Calibrator
    METER_D3,				// 58	X-Rite Display3 OEM
    METER_CEC6,				// 59	CalMAN Enhanced C6
    METER_DISCUS,			// 60	Discus
    METER_D3R,				// 61	X-Rite Display Pro Retail
    METER_S4,				// 62	DataColor Spyder4
    METER_EYEONE_G2,		// 63	X-Rite i1Pro G2
    METER_CEI1_G2,			// 64	CalMAN Enhanced i1Pro G2 includes LED table
    METER_CES4,				// 65	CalMAN Enhanced DataColor Spyder4

    METER_C3 = 67,			// 67	SpectraCal OEM of ColorMunki Smile for Tutorial
    METER_C3RGB,			// 68	SpectraCal OEM of ColorMunki Smile for RGB
    METER_PR740,			// 69	Photo Research PR-740
    METER_C3SKY,			// 70	SpectraCal OEM of ColorMunki Smile for SkyTV
    METER_EIZO,				// 71	Built in Eizo Calibrator
    METER_D3CM,				// 72	X-Rite ColorMunki Display (DEV TESTING ONLY)
    METER_C3CM,				// 73	X-Rite ColorMunki Smile (DEV TESTING ONLY)
    METER_CR100,			// 74	Colorimetry Research 100 (tristim)
    METER_CR250,			// 75	Colorimetry Research 250 (spectro)
    METER_D3HP,				// 76	X-Rite Display3 HP (DEV TESTING ONLY)
    METER_PR6AQL,			// 77	Photo Research PR-6AQL
    METER_GOSSEN,			// 78	Gossen light meter
    METER_CEC3, 			// 79	SpectraCal Enhanced C3
    METER_SV,               // 80   Jeti SpectraVal 15xx
    METER_D3NEC,			// 81	X-Rite Display3 NEC
	METER_BM7A,             // 82   Topcon BM-7A
	METER_SR3AR,            // 83   Topcon SR-3AR
	METER_PR730,            // 84   Photo Research 730/735

    METER_LAST,             // 85	not to be greater than 89
    METER_BETA = 90,        // 90
}METERS;

typedef enum
{
    DISPLAY_NONE,
    DISPLAY_SIMULATED,			// 01	CalMAN simulated display

    DISPLAY_UNUSED_02,			// 02
    DISPLAY_RADIANCE,			// 03	Lumagen Radiance XS/XD/XE
    DISPLAY_DHD3,				// 04	Runco DHD3
    DISPLAY_EQBASIC,			// 05	AVF videoEQ Basic (Grayscale,Gamma)
    DISPLAY_EQPRO,				// 06	AVF videoEQ Pro (Grayscale,Gamma,Gamut)
    DISPLAY_UNUSED_07,			// 07
    DISPLAY_MARSHALL,			// 08	Marshall Displays with MEI
    DISPLAY_DUO_CMS,			// 09	DVDO Duo with full CMS
    DISPLAY_CALMAN,				// 10	CalMAN client running on local PC
    DISPLAY_PANA_PRO,			// 11	Panasonic Pro VX100 series
    DISPLAY_PANA_CONSUMER,		// 12	Panasonic Consumer series
    DISPLAY_LG,					// 13	LG displays
    DISPLAY_FPS,				// 14	FPS video processors
    DISPLAY_VIVITEK,			// 15	Vivitek LED light engines
    DISPLAY_UNUSED_16,			// 16
    DISPLAY_Q750,				// 17	Runco Q750
    DISPLAY_BOLAND,				// 18	Boland Displays with RemCode10
    DISPLAY_CALMAN_MONO,		// 19	CalMAN client running on local PC in Monochrome mode
    DISPLAY_UNUSED_20,			// 20
    DISPLAY_SONY_BRAVIA,		// 21	Sony Bravia XBR-46HX909
    DISPLAY_ANTHEM_RC,			// 22	Anthem 50V Room Correction
    DISPLAY_JVC_RS,				// 23	JVC RS Series Projectors RS40/50/60
    DISPLAY_TITAN,				// 24	Titan 1080p-700
    DISPLAY_PANA_P2011,			// 25	Panasonic 2011 Pro series
    DISPLAY_PANA_C2011EU,		// 26	Panasonic 2011 Consumer series (EU Models)
    DISPLAY_SONY_VW90ES,		// 27	Sony VPL-VW90ES projector
    DISPLAY_SHARP_PNV,			// 28	Sharp PNV601 Display wall
    DISPLAY_PANA_C2011US,		// 29	Panasonic 2011 Consumer series (US Models)
    DISPLAY_EE_COLOR,			// 30	EE Color Processor
    DISPLAY_SHARP_ELITE,		// 31	Sharp Elite
    DISPLAY_CHRISTIE_FHD,		// 32	Christie FHD
    DISPLAY_DIGITAL_VIEW,		// 33	Digital View LCD Contollers
    DISPLAY_CALMED,				// 34	CalMED client
    DISPLAY_JVC_RSX5,			// 35	JVC RSx5 Series
    DISPLAY_HDLINK_PRO,			// 36	Black Magic HDLink Pro
    DISPLAY_DAVIO,				// 37	Davio I/II
    DISPLAY_CLIENT_3,			// 38   Client III
    DISPLAY_COLORBOX,			// 39   ColorBox
    DISPLAY_RADIANCE_LUT,		// 40	Lumagen Radiance XS/XD/XE w/ 5^3 LUT
    DISPLAY_CUBE,				// 41	Generic Cube (3D LUT) Generator
    DISPLAY_PLUTO,				// 42	Pandora Pluto
    DISPLAY_PANA_C2013,			// 43	Panasonic 2013 Consumer series (US - ZT60/VT/WT/DT) (EU - ZT60/VT/GT/WT/DT/FT) (Asia - ZT60/WT/DT)
    DISPLAY_ISMINI,				// 44	FujiFilm IS-Mini LUT box
    DISPLAY_JVC_RSX6,			// 45	JVC RSx6 Series
    DISPLAY_SHARP_PNK,			// 46	Sharp PNK321 4k Monitor
    DISPLAY_HP_DREAMCOLOR,		// 47	HP DreamColor I
    DISPLAY_HP_DREAMCOLOR_II,	// 48	HP DreamColor II
    DISPLAY_EIZO,				// 49	All Eizo display models (1D LUT)
    DISPLAY_JVC_UHD,			// 50	JVC 4k panel
    DISPLAY_EIZO_3D,			// 51	All Eizo display models (3D LUT)
    DISPLAY_TVLOGIC,			// 52	All TVLogic displays wiht 3D LUTs
    DISPLAY_PANA_BT4,			// 53	Panasonic BT4 (1D LUT)
    DISPLAY_PANA_BT4_3D,		// 54	Panasonic BT4 (3D LUT)
    DISPLAY_RESOLVE,			// 55	DaVinci Resolve (.cube)
    DISPLAY_PANA_LFV,			// 56	Panasonic LFV
    DISPLAY_FSI,				// 57	Flanders (.dat .cfe)
    DISPLAY_PANA_C2014,			// 58	Panasonic 2014 Consumer series AS800, AX800, AX900
    DISPLAY_RUIGE,				// 59	Ruige
    DISPLAY_DOLBY,				// 60	Dolby PRM
    DISPLAY_JVC_RSX7,			// 61	JVC RSx7 Series
    DISPLAY_CALMED_3,			// 62   CalMED III
    DISPLAY_OSEE,				// 63	OSEE
    DISPLAY_HATTELAND,			// 64	Hatteland
    DISPLAY_COLORCHECKER,		// 65	No file for ColorChecker eval license
    DISPLAY_MADVR,				// 66	Enth (madVR)
    DISPLAY_ULMPI,              // 67   Unified LUT Management Protocol Interface
    DISPLAY_PLANAR_G2,          // 68   Planar Clarity Matrix G2 Architecture
    DISPLAY_PANA_C2015,			// 69	Panasonic 2015 Consumer series CR,CX,CZ
    DISPLAY_SAMSUNG_MDC,        // 70   Samsung MDC
    DISPLAY_PRISMA,             // 71

    DISPLAY_LAST				// 72	Last
}DISPLAYS;

typedef enum
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
}MODES;

typedef	enum
{
    SOURCE_NONE = 0,
    SOURCE_PRONTO,					// 01	Pronto IR Control
    SOURCE_AVSBR,					// 02	AVS Blu-Ray calibration discs
    SOURCE_AVSHD,					// 03	AVS HD-DVD calibration discs
    SOURCE_CALMAN,					// 04	CalMAN basic calibration DVD
    SOURCE_VP4_ATSC,				// 05	Sencore VP403 in ATSC mode
    SOURCE_MARSHALL,				// 06	Marshall Broadcast Monitor
    SOURCE_WDLIVE_IR,				// 07	Western Digital HD Media Player (Live)
    SOURCE_S802,					// 08	Sencore 802 series
    SOURCE_QD780,					// 09	Quantum Data 780 series
    SOURCE_DVDOV2,					// 10	Dvdo V2 support for addtional grayscale/saturation patterns
    SOURCE_QD701,					// 11	Quantum Data 701 with FW 2.310 or later
    SOURCE_VIDEOFORGE,				// 12	AV Foundry VideoForge (HDMI)
    SOURCE_CPG,						// 13	CalMAN Pattern Generator v2 (PC)
    SOURCE_DUO_IR,					// 14	DVDO Duo IR
    SOURCE_PHABRIX,					// 15	Phabrix Sx (SDI)
    SOURCE_SOAPBOX,					// 16	SoapBox XXX (SDI)
    SOURCE_CHROMA,					// 17	Chroma ATE Pattern Generator
    SOURCE_LYNX,					// 18	LYNX Testor (SDI)
    SOURCE_QD804,					// 19	Quantum Data 804 series
    SOURCE_WDPLUS_IR,				// 20	Western Digital HD Media Player (Plus)
    SOURCE_CALMED,					// 21	CalMED Client
    SOURCE_DAVIO,					// 22	Cine-tal Davio
    SOURCE_AP5000,					// 23	AccuPel DVG-5000
    SOURCE_JVC,						// 24	JVC Internal Pattern Generator
    SOURCE_UPGCI,					// 25	Unified Pattern Generator Control Interface
    SOURCE_CLIENT3,					// 26   Client 3
    SOURCE_PLUTO,					// 27	Pandora Pluto
    SOURCE_SM,						// 28	S&M HD Benchmark 2nd Edition (Blu-Ray)
    SOURCE_CALMED3,					// 29   CalMED 3
    SOURCE_ISMINI,					// 30   FujiFlim IS-Mini
    SOURCE_HP_DREAMCOLOR,			// 31	HP DreamColor I
    SOURCE_HP_DREAMCOLOR_II,		// 32	HP DreamColor II
    SOURCE_EIZO,					// 33	Built in pattern generator
    SOURCE_RESOLVE,					// 34	DaVinci Resolve pattern generator
    SOURCE_DVDO_TPG,				// 35	DVDO TPG
    SOURCE_RUIGE,					// 36	Ruige built in
    SOURCE_DOLBY,					// 37	Dolby PRM
    SOURCE_MEDIAFORGE,				// 38	SpectraCal MediaVorge
    SOURCE_OSEE,					// 39	OSEE built in
    SOURCE_SCRATCH,                 // 40   Assimilate Scratch pattern generator
    SOURCE_MADVR,                   // 41   madTPG
    SOURCE_MOBILEFORGE,				// 42	MobileForge
    SOURCE_PRISMA,                  // 43   Qinc Prisma
    SOURCE_MURIDEO,                 // 44   Murideo Generator
    SOURCE_ASTRO,                   // 45   Astro Generator

    SOURCE_ACCUPEL = 51,				// 51	AccuPel HDG-3000
    SOURCE_COLORFACTS,				// 52	ColorFacts Version 6
    SOURCE_VP30,					// 53	DVDO VP30 prior to v1.14
    SOURCE_VP50,					// 54	DVDO VP Series
    SOURCE_LUMAGEN,					// 55   Lumagen HD Series
    SOURCE_VIDEOPRO,				// 56	Sencore 400 series
    SOURCE_HTPC,					// 57   CalMAN HTPC Pattern Generator
    SOURCE_AVIA,					// 58   DVD SD Version
    SOURCE_DVE,						// 59   DVD SD Version
    SOURCE_GETGRAY,					// 60   DVD SD Version
    SOURCE_DVD,						// 61   Generic DVD or standalone VTG
    SOURCE_QUANTUMDATA,				// 62	Quantum Data801G series				
    SOURCE_DVEHD,					// 63   DVE HD-DVD
    SOURCE_EXTRON,					// 64   Extron VTG-400D
    SOURCE_QD700,					// 65	Quantum Data 700 series NOT supported, does not support setting IRE levels for grayscale
    SOURCE_QD802,					// 66	Quantum Data 802 series
    SOURCE_VP300,					// 67	Sencore 300 series
    SOURCE_QD600,					// 68	Quantum Data 600 series NOT supported, does not support setting IRE levels for grayscale
    SOURCE_CII,						// 69	CrystalIO II
    SOURCE_AP4000,					// 70	AccuPel HDG-4000
    SOURCE_QD880,					// 71	Quantum Data 880 series
    SOURCE_MP500,					// 72	Sencore MP500
    SOURCE_XD,						// 73   Lumagen XD Series
    SOURCE_AVIA_II,					// 74	Avia II
    SOURCE_DVEBR,					// 75   DVE Blu-Ray
    SOURCE_EDGE,					// 76   DVDO Edge
    SOURCE_DVDO_IR,					// 77	DVDO VP / Edge IR
    SOURCE_WDHD_IR,					// 78	Western Digital HD Media Player
    SOURCE_HDG8000,					// 79	DTRO Vision HDG-8000
    SOURCE_VIDEOFORGE_II,			// 80	AV Foundry VideoForge II SDI/HDMI
    SOURCE_VIDEOFORGE_VPD,			// 81	AV Foundry VideoForge VOD "Video Playback Device"
    SOURCE_VIRTUALFORGE_PRO,		// 82	SpectraCal VirtualForge PRO
    SOURCE_VIRTUALFORGE,		    // 83	SpectraCal VirtualForge
    SOURCE_QD980,                   // 84   Quantum Data 980 series
    SOURCE_PLANAR_G2,               // 85   Planar Clarity Matrix G2
    SOURCE_SAMSUNG_MDC,             // 86   Samsung

    SOURCE_LAST						// 87
}SOURCES;

typedef enum
{
    DVD_NONE,						// 00

    DVD_LG_BDP,						// 01	LG Blu-ray players
    DVD_PIONEER_BDP,				// 02	Pioneer Blu-ray players
    DVD_SONY_SD,					// 03	Sony DVD players
    DVD_TOSHIBA_SD,					// 04	Toshiba DVD players
    DVD_TOSHIBA_HDP,				// 05	Toshiba HD-DVD players
    DVD_PANASONIC_BDP,				// 06	Panasonic Blu-ray players
    DVD_SONY_BDP,					// 07	Sony Blu-ray players
    DVD_OPPO_BDP,					// 08	Oppo Blu-ray players
    DVD_MICROSOFT_MEDIA,			// 09	Microsoft Media Center
    DVD_SAMSUNG_BDP,				// 10	Samsung Blu-ray players

    DVD_USER1 = 100,					// 100	User defined 1

    DVD_LAST = 999					// 999
}DVDS;

typedef enum
{
    FRAME_NONE,						// 0

    FRAME_480,						// 1  - 480 NTSC  59p
    FRAME_576,						// 2  - 576 PAL   50p
    FRAME_720,						// 3  - 720 HD    59p
    FRAME_1080,						// 4  - 1080 HD   59p
    FRAME_480i,						// 5  - 480i NTSC 29i
    FRAME_576i,						// 6  - 576i PAL  25i
    FRAME_1080i,					// 7  - 1080i HD  29i
    FRAME_2K,						// 8  - 2K 24
    FRAME_4K,						// 9  - 4K 24
    FRAME_3D,						// 10 - 3D 23 FP

    FRAME_LAST						// 11
}FRAMES;

typedef enum
{
    USB,
    COM1,
    COM2,
    COM3,
    COM4,
    COM5,
    COM6,
    COM7,
    COM8,
    COM9,
    COM10,
    COM11,
    COM12,
    COM13,
    COM14,
    COM15,
    COM16
}COMMS;

/* See Formulas.h
typedef enum
{
}DeltaE; */

/* See Formulas.h
typedef enum
{
}GAMMA_FORMULAS; */

typedef enum
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

typedef enum
{
    LEVEL_STIM,
    LEVEL_IRE
} IRE;

struct DeviceEnum
{
    UINT32  serialNumber;
    METERS  meter;
    SOURCES source;
};

typedef enum
{
    METER_UNIT_NITS,	// 0 Nits - cd/m^2
    METER_UNIT_FL,		// 1 Foot Lamberts - cd/ft^2
    METER_UNIT_LUX,		// 2 Lux - lm/m^2
    METER_UNIT_FC		// 3 Foot Candles - lm/ft^2
}METER_UNITS;

typedef enum
{
    METER_SO_1931 = 0,	// Standard Observer 1931
    METER_SO_1964		// 1964
}METER_SO;

typedef enum
{
    METER_SYNC_OFF,			// 0
    METER_SYNC_ON,			// 1
    METER_SYNC_AUTO,		// 2
    METER_SYNC_BOTH,		// 3 on/auto
    METER_SYNC_EXTERNAL		// 4 external
}METER_SYNC;

typedef enum
{
    MATRIX_NONE,		// 0 None
    MATRIX_GRAYSCALE,	// 1 Grayscale matrix
    MATRIX_COLOR,		// 2 Color matrix
    MATRIX_BOTH			// 3 Both types
}MATRIX_TYPES;

typedef enum
{
    MANUFACTURER_NONE        = 0x0,
    MANUFACTURER_SIP         = 0x1,			// 1			All SIP based meters
    MANUFACTURER_EXTECH      = 0x2,			// 2			Extech or Lutron light meters
    MANUFACTURER_MINOLTA     = 0x4,			// 4			Konica Minolta RS-232
    MANUFACTURER_PR6         = 0x8,			// 8			Photo Research 6xx series RS-232
    MANUFACTURER_PR5         = 0x10,		// 16			Photo Research 5xx series
    MANUFACTURER_MINLOTA_USB = 0x20,	    // 32			Konica Minolta CS-200, CA-210 USB
    MANUFACTURER_KLEIN       = 0x40,		// 64			Klein Instruments
    MANUFACTURER_ORB         = 0x80,		// 128			ORB Optronix
    MANUFACTURER_PR700       = 0x100,		// 256			Photo Research 7xx series
    MANUFACTURER_MINOLTA_CS1 = 0x200,	    // 512			Konica Minolta CS-1000
    MANUFACTURER_PR_USB      = 0x400,		// 1024			Photo Research 6xx series USB, Bluetooth
    MANUFACTURER_MINOLTA_CS2 = 0x800,	    // 2048			Konica Minolta CS-2000
    MANUFACTURER_JETI        = 0x1000,		// 4096			Jeti Specbos
    MANUFACTURER_BWTEK       = 0x2000,		// 8192			BW Tek Spectros
    MANUFACTURER_AVF         = 0x4000,		// 16384		AVF Spectros
    MANUFACTURER_UDT         = 0x8000,		// 32768		UDT Instruments
    MANUFACTURER_PR740       = 0x10000,		// 65536		Photo Research 74x series
    MANUFACTURER_LICENSE     = 0x20000,		// 131072		Devices used for licensing
    MANUFACTURER_EIZO        = 0x40000,		// 262144		Eizo displays with built in meter
    MANUFACTURER_CRI         = 0x80000,		// 524288		Colorimetry Research CR-100, CR-250
    MANUFACTURER_GOSSEN      = 0x100000,	// 1048576		Gossen light meter
    MANUFACTURER_USB         = 0x40000000,  // 1073741824   USB Devices
    MANUFACTURER_ALL         = 0x7FFFFFFF	// 2147483647   All
}METER_MANUFACTURES;

typedef enum
{
    COLOR_WHITE,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_YELLOW,
    COLOR_REF,
    COLOR_ORANGE,
    COLOR_LAST
}COLORS;

typedef enum
{
    GATE_BLUE = 1,
    GATE_GREEN,
    GATE_CYAN,
    GATE_RED,
    GATE_MAGENTA,
    GATE_YELLOW,
    GATE_WHITE,
}GATES;

typedef enum
{
    LUT_RED,
    LUT_GREEN,
    LUT_BLUE,
    LUT_LUMINANCE,
    LUT_DIRTY,
    LUT_LAST
}LUTS;

typedef BOOL(__stdcall *WriteLogCallback) (char *, int);
typedef BOOL(__stdcall *DecryptToCallback)(char *, char *);

struct INITIALIZE_CALMAN
{
    char Path[4096];
    char DllPath[4096];
    char ProfilePath[4096];
    char LutPath[4096];
    char DataPath[4096];
};

extern char *DllPath;
extern char *Version;
extern char *LastPattern;
extern char *ExeName;
extern char *ProfilePath;
extern char *LutPath;
extern char *DataPath;

#define PATTERN_STARTUP			"STARTUP\0"
#define PATTERN_EXIT			"EXIT\0"
#define PATTERN_OFF	            "OFF\0"

#define PATTERN_GRAYSCALE		"GRAYSCALE\0"
#define PATTERN_BRIGHTNESS		"BRIGHTNESS\0"
#define PATTERN_CONTRAST		"CONTRAST\0"
#define PATTERN_WHITE			"WHITE\0"
#define PATTERN_COLOR			"COLOR\0"
#define PATTERN_TINT			"TINT\0"
#define PATTERN_SHARPNESS		"SHARPNESS\0"
#define PATTERN_CHECKERBOARD	"CHECKERBOARD\0"
#define PATTERN_BLACK			"BLACK\0"
#define PATTERN_SMPTE			"SMPTE\0"

#define PATTERN_WHITE_WINDOW	"WW\0"
#define PATTERN_RED_WINDOW		"RW\0"
#define PATTERN_GREEN_WINDOW	"GW\0"
#define PATTERN_BLUE_WINDOW		"BW\0"
#define PATTERN_CYAN_WINDOW		"CW\0"
#define PATTERN_MAGENTA_WINDOW	"MW\0"
#define PATTERN_YELLOW_WINDOW	"YW\0"
#define PATTERN_WHITE_FIELD		"WF\0"
#define PATTERN_RED_FIELD		"RF\0"
#define PATTERN_GREEN_FIELD		"GF\0"
#define PATTERN_BLUE_FIELD		"BF\0"
#define PATTERN_CYAN_FIELD		"CF\0"
#define PATTERN_MAGENTA_FIELD	"MF\0"
#define PATTERN_YELLOW_FIELD	"YF\0"

// This class is exported from the CalMANv3.dll
class CalMAN
{
public:
    // displays
    enum { DISPLAY_NONE, DISPLAY_H7x, DISPLAY_UNKNOWN };
    enum { INPUT_NONE, INPUT_1 = 1, INPUT_2 = 2, INPUT_3 = 4, INPUT_4 = 8, INPUT_5 = 16, INPUT_6 = 32, INPUT_7 = 64, INPUT_8 = 128, INPUT_9 = 256, INPUT_ALL = 511 };

    static UINT32 LoadV6(INITIALIZE_CALMAN& Initialize, WriteLogCallback  WriteLogInit, DecryptToCallback DecryptToInit);
    static BOOL   Unload();
    static char  *GetVersion();
    static ERRORS GetError();
    
    CalMAN();
    virtual ~CalMAN();

private:
};

#endif