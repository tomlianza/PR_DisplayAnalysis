#ifndef CMDFPARSER_H_INCLUDED
#define CMDFPARSER_H_INCLUDED

#include "CVesaMonitor.h"
#include "CSequelXMLParser.h"

class CMDFParser : public CSequelXMLParser
{
public:
	CMDFParser();
	virtual ~CMDFParser();

	enum {MAX_VCP_STRING_LENGTH = 32};

	typedef struct {
		int code;		// VCP command code
		char stringName[MAX_VCP_STRING_LENGTH];
		int minVal;
		int maxVal;
		// ADD OTHER FIELDS LATER AS NEEDED
	} VCPInfoStruct;

	typedef struct {
		int code;		// VCPEx command code
		char stringName[MAX_VCP_STRING_LENGTH];
		int minVal;
		int maxVal;
		int type;
		// ADD OTHER FIELDS LATER AS NEEDED
	} VCPExInfoStruct;

	PARSE_STATUS GetVCPCommand(char **startPoint, VCPInfoStruct *v);
	PARSE_STATUS GetVCPExCommand(char **startPoint, VCPExInfoStruct *v);
	PARSE_STATUS GetChromaticityValues(char **startPoint, float **vals);
	PARSE_STATUS GetColorPresetInfo(char **startPoint, MAX_GAIN_BIAS_DATA *d);
	PARSE_STATUS GetDDCCommandOffset(char **startPoint, int *cmd, int *offset);
	PARSE_STATUS GetDDCMapping(char **startPoint, int *oldVal, int *newVal);
};
#endif

