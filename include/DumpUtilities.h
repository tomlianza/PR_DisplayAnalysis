#ifndef DUMPUTILITIES_H_INCLUDED
#define DUMPUTILITIES_H_INCLUDED

static char dumpString[1024];
#ifdef DEBUG_DUMP

#ifndef DUMPFILE
#error symbol 'DUMPFILE' must be defined!
#endif

static FILE *dumpFile;
#define INITDUMPFILE InitDumpFile()
#define DUMPSTRING0(x) {sprintf(dumpString, x); DumpString(dumpString);}
#define DUMPSTRING(x,y) {sprintf (dumpString, x, y); DumpString(dumpString);}
#define DUMPSTRING2(x,y,z) {sprintf (dumpString, x, y, z); DumpString(dumpString);}
#define DUMPSTRING3(w,x,y,z) {sprintf (dumpString, w, x, y, z); DumpString(dumpString);}

static void InitDumpFile()
{
	dumpFile = fopen(DUMPFILE, "w");

	char logString[256];
	CTime now = CTime::GetCurrentTime();
	
	sprintf (logString, "%02d/%02d/%4d %02d:%02d:%02d\n",
		now.GetMonth(), now.GetDay(), now.GetYear(),
		now.GetHour(), now.GetMinute(), now.GetSecond());

	fprintf(dumpFile, logString);
	fclose(dumpFile);
}

static void DumpString(char *s)
{
	dumpFile = fopen (DUMPFILE, "a");
	fprintf(dumpFile, s);
	fclose(dumpFile);
}

#else
#define DUMPSTRING0(x)
#define INITDUMPFILE
#define DUMPSTRING(x,y)
#define DUMPSTRING2(x,y,z)
#define DUMPSTRING3(w,x,y,z)
#endif

#endif // DUMPUTILITIES_H_INCLUDED