#ifndef CSIREGISTERACCESSATI_H_INCLUDED
#define CSIREGISTERACCESSATI_H_INCLUDED

#include "CSIRegisterAccess.h"


#define R300_OV0_GAMMA_0_F				  0x0d40
#define R300_OV0_GAMMA_10_1F			  0x0d44
#define R300_OV0_GAMMA_20_3F			  0x0d48
#define R300_OV0_GAMMA_40_7F			  0x0d4c
#define R300_OV0_GAMMA_80_BF			  0x0e00
#define R300_OV0_GAMMA_C0_FF			  0x0e04
#define R300_OV0_GAMMA_100_13F			  0x0e08
#define R300_OV0_GAMMA_140_17F			  0x0e0c
#define R300_OV0_GAMMA_180_1BF			  0x0e10
#define R300_OV0_GAMMA_1C0_1FF			  0x0e14
#define R300_OV0_GAMMA_200_23F			  0x0e18
#define R300_OV0_GAMMA_240_27F			  0x0e1c
#define R300_OV0_GAMMA_280_2BF			  0x0e20
#define R300_OV0_GAMMA_2C0_2FF			  0x0e24
#define R300_OV0_GAMMA_300_33F			  0x0e28
#define R300_OV0_GAMMA_340_37F			  0x0e2c
#define R300_OV0_GAMMA_380_3BF			  0x0d50
#define R300_OV0_GAMMA_3C0_3FF			  0x0d54

#define NUM_GAMMA_REGS 18
#define NUM_TRANSFORM_REGS 6
#define FIRST_TRANSFORM_REG 18

#define R300_OV0_LIN_TRANS_A			  0x0d20
#define R300_OV0_LIN_TRANS_B			  0x0d24
#define R300_OV0_LIN_TRANS_C			  0x0d28
#define R300_OV0_LIN_TRANS_D			  0x0d2c
#define R300_OV0_LIN_TRANS_E			  0x0d30
#define R300_OV0_LIN_TRANS_F			  0x0d34

enum {NUM_ATI_REGS = 24};

typedef unsigned long ATI_REG_VALUE;
typedef enum ATI_REG_CODING
{
	LIN_TRANS1,			// 31:17, 15:1
	LIN_TRANS2,			// 31:17, 12:0
	GAMMA1,				// 26:16, 8:0
	GAMMA2,				// 25:16, 9:0
	GAMMA3				// 24:16, 10:0
} ATI_REG_CODING;

typedef struct
{
	double offset;
	double minOffset;
	double maxOffset;
	double slope;
	double minSlope;
	double maxSlope;
} ATI_GAMMA_SETTING;

typedef struct
{
	double Cb_current;
	double Cb_min;
	double Cb_max;

	double Y_current;
	double Y_min;
	double Y_max;

	double offset_current;
	double offset_min;
	double offset_max;

	double Cr_current;
	double Cr_min;
	double Cr_max;
} ATI_LINEAR_SETTING;

typedef struct
{
	ATI_GAMMA_SETTING gammaSettings[NUM_GAMMA_REGS];
} ATI_GAMMA_ARRAY;

typedef struct
{
	ATI_LINEAR_SETTING linearSettings[3];
} ATI_LINEAR_ARRAY;

typedef struct
{
	unsigned long offset;		// Offset from base memory address
	char *name;					// Text representation of the register
	ATI_REG_CODING codingType;	// Which bits mean what.
	ATI_REG_VALUE rawValue;		// Register contents (not decoded)
	double valH;					// (High-end) decoded value
	double valL;					// (Low-end) decoded value
	double minValH;				// Minimum value for the high control
	double maxValH;				// Maximum value for the high control
	double minValL;				// Minumum value for the low control
	double maxValL;				// Maximum value for the low control
	ATI_REG_VALUE desiredRawValue; // Holding place for value we want in the register
	long hexValH;				// Temporary-use storage of shifted and masked values
	long hexValL;				// ... for high and low values
} ATI_REG_DESCRIPTOR;

extern ATI_REG_DESCRIPTOR regs[NUM_ATI_REGS];

class CSIRegisterAccessATI : public CSIRegisterAccess
{
public:
	enum {VID = 0x1002};
	enum {PID = 0x4E48};
	CSIRegisterAccessATI() {};
	virtual ~CSIRegisterAccessATI() {}
	virtual long GetBaseAddress();
	virtual bool IsATI9800();
	virtual PCI_COMMON_CONFIG *GetHeader(int vid = VID, int pid = PID);
	virtual bool SetBaseAddress();
	virtual char *MapMemory(long mmBase, int length);
	virtual void UnmapMemory(long mmBase=0, int length=0x1000);

private:
	char *m_baseAddress; // Base address mapped by driver.
	char *m_unmappedBaseAddress; // Base address TO BE mapped

public:
	virtual long GetLong(long base, int offset);
	virtual short GetShort(long base, int offset);
	virtual unsigned char GetByte(long base, int offset);
	virtual bool SetLong(long base, int offset, long value);
	virtual bool SetShort(long base, int offset, short value);
	virtual bool SetByte(long base, int offset, unsigned char value);
	virtual bool Decode(ATI_REG_DESCRIPTOR *reg);
	virtual bool Encode(ATI_REG_DESCRIPTOR *reg);
	virtual bool GetGammaSettings(ATI_GAMMA_ARRAY *array, bool readFromDevice = true);
	virtual bool SetGammaSettings(ATI_GAMMA_ARRAY *array, bool writeToDevice = true);

	virtual bool GetLinearSettings(ATI_LINEAR_ARRAY *array, bool readFromDevice = true);
	virtual bool SetLinearSettings(ATI_LINEAR_ARRAY *array, bool writeToDevice = true);


	// Utility routines to encode and decode hex fields into doubles.
	double DecodeXdot8(unsigned long arg);		// unsigned x bit integer with 8 bits of fraction
	double DecodeXdot1(unsigned long arg);		// unsigned x bit integer with 1 bits of fraction
	double DecodeS3dot11(unsigned long arg);		// sign bit, 3 bit integer with 11 bits of fraction
	double DecodeS11dot1(unsigned long arg);		// sign bit, 11 bit integer with 1 bit of fraction
	unsigned long EncodeXdot8 (double arg);
	unsigned long EncodeXdot1 (double arg);
	unsigned long EncodeS3dot11 (double arg);
	unsigned long EncodeS11dot1 (double arg);

	bool SaveValuesToDisk();
	bool GetValuesFromDisk();

	bool RewriteRegs(bool allofthem = false); // If false, only ones that have changed

};
#endif