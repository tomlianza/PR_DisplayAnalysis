#ifndef CSEQUELXMLPARSER_H_INCLUDED
#define CSEQUELXMLPARSER_H_INCLUDED


class CSequelXMLParser
{
public:
	CSequelXMLParser();
	virtual ~CSequelXMLParser();
	#ifdef OS9_DRIVER
	bool LoadFromFile(char *fname, FSSpec *spec);
	#else
	bool LoadFromFile(char *fname);
	
	#endif

	char *xmlData;

	typedef enum { // <0 implies error.
		PARSE_ERROR = -3,
		PARSE_END_OF_FILE = -2,
		PARSE_SIZE_ERROR = -1,
		PARSE_OPEN_TAG,
		PARSE_CLOSE_TAG,
		PARSE_NONTAG
	} PARSE_STATUS;

	PARSE_STATUS GetToken(char **startPoint, char *token, unsigned int maxSize);
	PARSE_STATUS GetTagContents(char **startPoint, char *searchTag, char *buf);
	PARSE_STATUS GetStringValue(char **startPoint, char *searchTag, char *result);
	PARSE_STATUS GetIntegerValue(char **startPoint, char *searchTag, int *result);
	PARSE_STATUS GetIntegerValue(char **startPoint, char *searchTag, short *result);
	PARSE_STATUS GetFloatValue(char **startPoint, char *searchTag, float *result);
};


#endif



