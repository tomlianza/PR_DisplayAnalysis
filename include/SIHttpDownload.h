#ifndef __SIHTTPDOWNLOAD__
enum {
	SI_NO_ERROR = 0,
	SI_ARG_ERROR = -1,
	SI_NETWORK_ERROR = -2
};

#ifdef WIN32
#define SIFileRef FILE *
#define SIFileSpec char*
#else
// Add Mac File spec stuff here?
#endif

short SISplitURLToServerAndResource(const char *URL, char *serverName, int serverNameSize, char *resourceName, int resourceNameSize);
short SIHttpDownloadToFileSpec(const char *URL, const SIFileSpec targetFileSpec, int port);
bool SILaunchURL(char *url);
#define __SIHTTPDOWNLOAD__
#endif