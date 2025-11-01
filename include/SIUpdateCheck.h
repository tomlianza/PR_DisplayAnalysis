#ifndef __SIUPDATECHECK__

#define SI_UPDATE_AVAILABLE 1
#define SI_NO_UPDATE_AVAILABLE 2

short SISoftwareUpdateAvailable (char *curVersion, char *sourceURL, 
								char *newVersion, char *downloadURL, char *fileSpec);
#define __SIUPDATECHECK__
#endif