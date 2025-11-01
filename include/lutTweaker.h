/* LutTweaker.h 

While potentially the most dangerous piece of code ever released into the system, 
the tweaker serves to make modifications to luts based upon input of absolute 
illuminance information.   


*/
#ifndef __LUTTWEAKER_H__
#define __LUTTWEAKER_H__
#include "GammaRamp.h"


/*Note that this function REQURIES and application to form a GammaRampEx structure.  This data 
is then modified in the tweaker code. */

bool LutTweakerAbsolute(double incidentLux, GammaRampEx * grExtendedData);
	/* iWeight is assumed to vary between 0 and 100 */
bool LutTweakerFuzzy(int iWeight,GammaRampEx * grExtendedData);

double LutTweakerGetGammaFactor (double incidentLux);

#endif