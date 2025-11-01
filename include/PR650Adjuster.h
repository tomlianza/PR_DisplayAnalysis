#pragma once

// Utility class to support adjustment of luminance value measured by 
// PR650/655 to match a different standard.
//
// The reason for this is to allow differently-calibrated devices (PR-65x and
// i1PROs) which were calibrated against different standards to match.
//
// This class supports reading of luminance adjustment values (for each of 2
// 650/655 lenses) from a file. The file format is as follows:
//		<PR650SerialNumber>,<Adj 1>,<Adj 2>,<PR650SerialNumber>
// and it's name is "PR65XFactors.txt".
// Existance of the file is required unless the application is built with
// the compile flag "DONT_REQUIRE_PR65X_FACTORS". 
// 
// CPR650.OpenPR650() will return the following:
//	- If DONT_REQUIRE_PR65X_FACTORS not set and file not found ---> error.
//  - If DONT_REQUIRE_PR65X_FACTORS not set, file exists and 
//    serial number of current device not in file ---> error.
//  - If DONT_REQUIRE_PR65X_FACTORS not set and SN is in file return normal status.
//  - If DONT_REQUIRE_PR65X_FACTORS set, return normal open status.

// 

typedef enum {
	PR650AS_OK,					// This 650's SN and lum data were found.
	PR650AS_FILE_NOT_FOUND,		// File not found
	PR650AS_SN_NOT_FOUND,		// File found but didn't have this 650's SN
	PR650AS_PARSE_ERROR,		// File found with SN but corrupt data.
	PR650AS_BAD_VALUES,			// Error in factor values.
} PR650_ADJUSTER_STATUS;

#define PR650ADJUSTER_FILENAME "PR65XFactors.txt"

class CPR650Adjuster
{
public:
	CPR650Adjuster(void);
	~CPR650Adjuster(void);
	
	// Look for the file, parse for 'sn' and return two values if parsed okay.
	// This function opens and closes the file and leaves nothing active.
	PR650_ADJUSTER_STATUS GetValues(long sn, double *lensVal1, double *lensVal2);
};
