/*Meters.h
 *
 * Copyright (c) 2005 - 2015 SpectraCal, LLC www.SpectraCal.com
 * Copyright (c) 2016 SpectraCal, Inc
 *
 * $History: Meters.h $
 * 
 */

#pragma once

#ifndef AFX_METERS_H__E2E8F1BA_6657_4B42_ABA6_C733CB7CE713__INCLUDED_
#define AFX_METERS_H__E2E8F1BA_6657_4B42_ABA6_C733CB7CE713__INCLUDED_

#include "./libCommon/Logging.h"
#include "./libCommon/XYZ.h"
#include "./libCommon/RawRGB.h"
#include "./libCommon/Spectrum.h"
#include "./libCommon/tmat.h"   // Matrix STL Class

extern char *DllPath;
extern char *ProfilePath;
extern char *DataPath;

extern DecryptToCallback DecryptTo;

#define MAX_METERS 32
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

extern unsigned short MeterButton;

#ifndef _WIN32
#include <sys/sem.h>
#include <sys/stat.h>

union semun 
{
    int                 val;    // value for SETVAL
    struct semid_ds    *buf;    // buffer for IPC_STAT, IPC_SE
    unsigned short     *array;  // array for GETALL, SETALL
    struct seminfo    __buf;    // buffer for IPC info
};
#endif

class Meters : public Logging
{
public:
    ERRORS SetError(ERRORS error);

    static Meters *Create(METERS m, ERRORS *err = 0);

    static UINT32 Enum(DeviceEnum *de, UINT32 size, METER_MANUFACTURES manufactures = MANUFACTURER_NONE, UINT32 port = 0);
    static const char *Inventory(char *buffer, UINT32 size, METER_MANUFACTURES manufactures = MANUFACTURER_NONE, UINT32 port = 0);

    virtual BOOL Load(char *dll = 0) = 0;
    virtual BOOL Unload() = 0;

    virtual BOOL List(DeviceEnum *de, UINT32 *count, BOOL serial = FALSE, UINT32 ports = 0) = 0;

    virtual BOOL Startup(UINT32 serialNumber = 0) = 0;
    virtual BOOL Shutdown() = 0;

    virtual BOOL Mode(MODES mode = MODE_NONE) = 0;
    virtual BOOL DarkCalibrate() = 0;
    virtual BOOL CRTSync() = 0;	// sync function itself

    virtual BOOL   ReadXYZ(UINT32 seconds = 0)  = 0;
    virtual double ReadY(UINT32 milliseconds)   = 0;
    virtual BOOL   ReadSpectrum(UINT32 seconds  = 0)  { SetError(ERR_MODE); return FALSE; };
    virtual BOOL   ReadRGB(UINT32 seconds       = 0)  { SetError(ERR_MODE); return FALSE; };

    virtual BOOL IsButtonPressed()      { return FALSE; };
    virtual BOOL HasButton()            { return FALSE; };
    virtual BOOL IsLuminance()          { return FALSE; };
    virtual BOOL IsTristimulus()        { return TRUE;  };
    virtual BOOL IsSpectrometer()       { return FALSE; };
    virtual BOOL IsRGB()                { return FALSE; };
    virtual BOOL IsUserSync()           { return FALSE; };
    virtual BOOL HasCalibrationTables() { return FALSE; };
    
    virtual const char *GetDarkMessage() = 0;
    virtual const char *GetCRTMessage()  = 0;

    double ReadDrift(UINT32 seconds = 30);
    BOOL ReadTrigger(UINT32 seconds, double targetY);

    const char *GetName()               { return Name;               };
    const char *GetDll()                { return Dll;                };
    const char *GetVersion()            { return Version;            };
    const char *GetVersion2()           { return Version2;           };
    const char *GetVersion3()           { return Version3;           };
    const char *GetSerialNumber()       { return SerialNumber;       };
    const char *GetDeviceSerialNumber() { return DeviceSerialNumber; };
    const char *GetInstance()           { return Instance;           };

    virtual UINT32 NextCalibration();
    virtual UINT32 MaxCalibration();

    virtual double GetRefreshRate()           { return RefreshRate;    };
    virtual void SetRefreshRate(double rate)  { RefreshRate = rate;    };

    BOOL IsConnected()                        { return Connected;      };
    void SetConnected(BOOL connected)         { Connected = connected; };

    BOOL IsProjector()                        { return Projector;      };	// Is this a proejctor
    void SetProjector(BOOL projector)         { Projector = projector; };

    BOOL IsScreen()                           { return Screen;         };	// If projector are we facing the screen or projector
    void SetScreen(BOOL screen)               { Screen = screen;       };

    BOOL IsNoise()                            { return Noise;          };	//
    void SetNoise(BOOL noise)                 { Noise = noise;         };

    BOOL IsDarkCalibrated()                   { return DarkCalibrated; };	// has the meter been dark calibrated
    void SetDarkCalibrated(BOOL dark)         { DarkCalibrated = dark; };

    BOOL IsCRTSynced()                        { return CRTSynced;      };	// has the CRT been synced with
    void SetCRTSynced(BOOL synced)            { CRTSynced = synced;    };

    BOOL IsSync()                             { return Sync;           };	// does the meter need CRT syncing
    void SetSync(BOOL sync)                   { Sync = sync;           };

    BOOL IsInit()                             { return Init;           };	// does the meter need a initial init "dark offset" or filters installed
    void SetInit(BOOL init)                   { Init = init;           };

    BOOL IsCRT()                              { return CRT;            };	// using CRT tables
    void SetCRT(BOOL crt)                     { CRT = crt;             };

    BOOL IsNits()                             { return Projector ? (Screen ? TRUE : FALSE) : TRUE; };	// Nits or Lux, Lux if we are facing the projector

    METER_UNITS GetUnit()                     { return UNIT;            };
    virtual void SetUnit(METER_UNITS unit)    { UNIT = unit;            };

    METER_SO GetSO()                          { return SO;              };
    virtual void SetSO(METER_SO so)           { SO = so;                };

    virtual METER_SYNC GetSyncType()          { return METER_SYNC_OFF;  };
    virtual BOOL SetSyncType(METER_SYNC sync) { return FALSE;           };

    BOOL IsLicensed()                         { return TRUE; };

    ERRORS GetError()                         { return Error; };
    BOOL License(BOOL lic = FALSE);

    virtual double GetMaxY();
    virtual double GetMinY();

    void SetMaxY(double max);
    void SetMinY(double min);

    virtual BOOL IsPointer()                  { return FALSE; };
    virtual BOOL SetPointer(BOOL pointer)     { return FALSE; };
    virtual BOOL GetPointer()                 { return FALSE; };

    virtual BOOL IsIndicator()                { return FALSE; };
    virtual BOOL SetIndicator(BOOL indicator) { return FALSE; };
    virtual BOOL GetIndicator()               { return FALSE; };

    // XYZ methods and properties
    BOOL SetPrecision(long precision, long lX, long lY, long lZ, BOOL profile);
    BOOL SetXYZ(double fX, double fY, double fZ, BOOL profile, double dx = 0, double dy = 0, double dY = 1);
    BOOL SetxyY(double fx, double fy, double fY, BOOL profile);

    void ZeroXYZ()        { return xyz->Zero();   };

    double GetX()         { return xyz->GetX();   };
    double GetY()         { return xyz->GetY();   };
    double GetZ()         { return xyz->GetZ();   };
    double Getx()         { return xyz->Getx();   };
    double Gety()         { return xyz->Gety();   };
    const char *GetXYZ()  { return xyz->GetXYZ(); };

    void SetLowLightHandler(BOOL llh)     { LLH = llh;  };
    BOOL GetLowLightHandler()             { return LLH; };

    void SetLowTrigger(double trigger)    { LowTrigger = trigger; };
    double GetLowTrigger()                { return LowTrigger;    };

    void SetLowExposure(double exposure)  { LowExposure = exposure; };
    double GetLowExposure()               { return LowExposure;     };

    void SetHighExposure(double exposure) { HighExposure = exposure; };
    double GetHighExposure()              { return HighExposure;     };

    BOOL IsPopulated()                    { return xyz->IsPopulated(); };

    void InitProfile();
    BOOL IsProfiled()                     { return Profiled; };
    void SetMatrix(double fX[4], double fY[4], double fZ[4], MATRIX_TYPES type);
    void SetOffset(double x, double y, double Y);
    void SetAmbient(double X, double Y, double Z);
    MATRIX_TYPES GetMatrixType() { return type; };

    BOOL SetButton(UINT32 button);
    
    BOOL IsDevice()                           { return Device ? TRUE : FALSE; };

    BOOL SetRGB(double R, double G, double B) { return rgb->Set(R, G, B);     };
    BOOL ZeroRGB()                            { return rgb->Zero();           };
    BOOL IsPopulatedRGB()                     { return rgb->IsPopulated();    };

    double GetR()                             { return rgb->GetR(); };
    double GetG()                             { return rgb->GetG(); };
    double GetB()                             { return rgb->GetB(); };

    virtual BOOL UpdateCalibrationTableRGB(double WRGB[3], double RRGB[3], double GRGB[3], double BRGB[3], double WxyYr[3], double RxyYr[3], double GxyYr[3], double BxyYr[3], UINT32 table, unsigned char *desc) { return FALSE; };
    virtual BOOL UpdateCalibrationTableXYZ(double WxyY[3], double RxyY[3], double GxyY[3], double BxyY[3], double WxyYr[3], double RxyYr[3], double GxyYr[3], double BxyYr[3], UINT32 table, unsigned char *desc) { return FALSE; };

    virtual BOOL CalibrationTable(UINT32 table = 0, UINT32 mode = 0) { return TRUE;  };
    virtual BOOL CalibrationFile(char *file, UINT32 mode = 0)        { return TRUE;  };
    virtual const char *CalibrationName(MODES mode)                  { return NULL;  };

    virtual BOOL IsPassword()                                        { return FALSE; };
    virtual BOOL SetPassword(char *password)                         { return FALSE; };

    BOOL Setup();	// used to call all global methods needed

    BOOL   RandomChar(unsigned char * string, UINT32 length);
    UINT32 GetMilliCount(void);

    //TODO: did not work right (CalMAN v5) so it was pulled for now
//	void SetVirtual(BOOL v=TRUE) {Virtual = v;};
//	BOOL IsVirtual() {return Virtual;};

    int GetETA()   { return ETA;           };
    int ResetETA() { ETA = -1; return ETA; };

    METERS GetMeter() { return Meter;          };

    Meters();
    virtual ~Meters();

    Spectrum *spectrum;

protected:
    BOOL SetMutex(UINT32 serialNumber);
    BOOL SetMutex(char *serialNumber = NULL);
    BOOL CheckMutex(UINT32 serialNumber);
    BOOL CheckMutex(char *serialNumber);

    BOOL ReleaseInstance();
    BOOL SetInstance();
    BOOL CheckInstance();

    BOOL Indicator;

    double GAMUTRGB[3][3];
    double GAMUTXYZ[3][3];

    METERS Meter;
    double RefreshRate;		        // measured CRT refresh rate

    double Ymax;
    double Ymin;

    char SerialNumber[256];
    char DeviceSerialNumber[256];	// used by mater calibration
    char Version[256];
    char Version2[256];
    char Version3[256];
    char Dll[256];
    char Name[256];
    char Message[256];
    char Temp[1024];
    char Instance[256];

    UINT32 ReCal;	// dark calibration timer
    UINT32 LastCal;	// last dark calibration

    void *hMod;

#ifdef _WIN32

    void *hMutex;
    void *hInstance;

#else

    int hMutex;
    int hInstance;

#endif

    void *hKeepAlive;

    METER_UNITS UNIT;
    METER_SO    SO;

    int ETA;

    void * IO;

    char Device[255];

private:
    XYZ    *xyz;
    RawRGB *rgb;

    tmat<double> matrix;
    BOOL         Profiled;
    MATRIX_TYPES type;

    struct OFFSET
    {
        double x;
        double y;
        double Y;
    } offset;

    struct AMBIENT
    {
        double X;
        double Y;
        double Z;
    } ambient;

    BOOL   LLH;
    double LowTrigger;
    double LowExposure;
    double HighExposure;

    BOOL Sync;	            // Needs initial CRT sync or not
    BOOL Init;	            // Needs initial init or not

    BOOL DarkCalibrated;	// has been dark calibrated
    BOOL CRTSynced;			// has been CRT synced with refresh rate

    BOOL Connected;
    BOOL CRT;				// use CRT calibration table
    BOOL Projector;			// is a projector
    BOOL Screen;			// is a projector facing the screen
    BOOL DriftInit;
    BOOL Noise;

    ERRORS Error;
    BOOL   Licensed;
};

#endif // !defined(AFX_METERS_H__E2E8F1BA_6657_4B42_ABA6_C733CB7CE713__INCLUDED_)
