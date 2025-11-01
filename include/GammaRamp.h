#ifdef WIN32
#elif LINUX
#else
#include "fakeMacTypes.h"
#endif

#ifndef GAMMARAMP_H_INCLUDED
#define GAMMARAMP_H_INCLUDED
typedef unsigned short WORD;
#ifndef GAMMARAMP_TYPE // Type for each entry
#define GAMMARAMP_TYPE WORD
#endif

#ifndef GAMMARAMP_FACTOR 
//unsigned 16 bit LUT
#define GAMMARAMP_FACTOR 65535 
#endif

#ifndef GAMMARAMP_SIZE // Number of entries per color
#define GAMMARAMP_SIZE 256
#endif

#ifndef GAMMARAMP_MAXVAL // Highest allowable output value
#define GAMMARAMP_MAXVAL 255
#endif

#ifdef LINUX
#include "linuxTypes.h"
#endif

typedef struct _GammaRamp {
	GAMMARAMP_TYPE Red[GAMMARAMP_SIZE];
	GAMMARAMP_TYPE Green[GAMMARAMP_SIZE];
	GAMMARAMP_TYPE Blue[GAMMARAMP_SIZE];
}GammaRamp;

 
/*
  Expanded 10/24/02 to account for
  10 bit DAC in NVIDIA driver
*/
typedef struct _GammaRampEx {
  WORD wSize;
  WORD wMaxVal;
  GAMMARAMP_TYPE *Red;
  GAMMARAMP_TYPE *Green;
  GAMMARAMP_TYPE *Blue;

  /*GAMMARAMP_TYPE Red[1024];
  GAMMARAMP_TYPE Green[1024];
  GAMMARAMP_TYPE Blue[1024]; */

}GammaRampEx;

typedef enum {
  GAMMA_EXPAND,
  GAMMA_SHRINK
}GAMMA_DIRECTION;

class CSIGammaRamp
{
public:
	GammaRamp grData;
  GammaRampEx grDataEx;


	GAMMARAMP_TYPE GetRed(int idx) {return grData.Red[idx];}
	GAMMARAMP_TYPE GetGreen(int idx) {return grData.Green[idx];}
	GAMMARAMP_TYPE GetBlue(int idx) {return grData.Blue[idx];}

	void SetRed(int idx, GAMMARAMP_TYPE val) {grData.Red[idx] = val;}
	void SetGreen(int idx, GAMMARAMP_TYPE val) {grData.Green[idx] = val;}
	void SetBlue(int idx, GAMMARAMP_TYPE val) {grData.Blue[idx] = val;}

  void ResizeLUT(GAMMA_DIRECTION direction, WORD wMaxValueIn,
               WORD wMaxLengthIn, WORD wMaxValueOut, WORD wMaxLengthOut);
};
#endif
