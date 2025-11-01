#pragma once
// CConvertHTML2PDF /****
/********************************************************************************\
This file depends upon the program wkhtml2pdf.exe to be in the working directory 
\*********************************************************************************/
#define BUFSIZE 4096
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

class CConvertHTML2PDF
{
public:
	char *m_inHTMFileName;
	char *m_outPDFFileName;
	char  m_ErrorText[2048];
	bool  m_bConversionComplete;

	CConvertHTML2PDF();
	

	~CConvertHTML2PDF();
	

	bool ConvertHTML2PDF(); // uses member function 
	bool ConvertHTML2PDF(char *inHTML, char*outPDF); // explicit call 

private:
	HANDLE g_hChildStd_IN_Rd = NULL;
	HANDLE g_hChildStd_IN_Wr = NULL;
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;
	HANDLE g_hInputFile = NULL;

	void CreateChildProcess();
	void WriteToPipe(void);
	void ReadFromPipe(void);
	void ErrorExit(char *ErrorText);

};
