//siProfileMethods.h
bool siPMBuildProfile(si_ICCInputData *data, unsigned char * usBuffer, long lMaxBufSize);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile
unsigned char * usBuffer->	The buffer that the profile is written into
long lMaxBufSize ->			The Maximum size of the buffer that can be written

  This is the only function that user needs to call

\**************************************************************************************/

bool siPMBuildProfileHeader(si_ICCInputData *data, unsigned char * usBuffer);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile
unsigned char * usBuffer->	The buffer that the profile is written into

  This function generates the memeory image of the header and checks the size of the profile

\**************************************************************************************/

bool siPMBuildProfileTagTable(si_ICCInputData *data, unsigned char * usBuffer);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile
unsigned char * usBuffer->	The buffer that the profile is written into

  This function generates the memeory image of the header and checks the size of the profile

\**************************************************************************************/
bool siPMOpenAdaptationModel(si_ICCInputData *data);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile

  This functions builds the adaptation model matricies based upon the selection

\**************************************************************************************/

bool siPMCalcXYZvals( si_ICCInputData *data);

/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile

  This functions Calculates the data and formats for writing int the profile

\**************************************************************************************/

bool siPMLongRampData( si_ICCInputData *data);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile

  This functions Calculates the ramp data and formats for writing in the profile

\**************************************************************************************/
bool siPMPrintData(si_ICCInputData *data, char * filename);
/**************************************************************************************\
si_ICCInputData *data ->	The Input data used to generate the profile

  This functions Calculates the ramp data and formats for writing in the profile

\**************************************************************************************/


long	siPMlongValue(long in);
short	siPMshortValue(short in);
long	siPMRoundupTo4ByteBoundary(long lSize);
long    siPMDouble2s15_16(double inval);