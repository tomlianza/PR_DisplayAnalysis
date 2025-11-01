//
//  PresetUtil.h
//

extern void QuoteSpaces(char *src, char*dst, int n);

extern char * GetDefaultPresetSource(char *c);

#ifdef MAC_KIT
extern  char * GetPresetSourceFromBundle(char *c);
extern  char * GetPresetSourceFromPath(char *c, char *path);

extern  int ConvertTempGammaPopupToSingle(int tempTag, int gammaTag);
extern  int ConvertSinglePopupToTemp(int index);
extern  int ConvertSinglePopupToGamma(int index);
#endif

#define PRESET_FOLDER "Presets"
#define MAX_PRESET_PATH 2048

#ifndef DEFAULT_PRESET_GROUP
#define DEFAULT_PRESET_GROUP "Medium"
#endif