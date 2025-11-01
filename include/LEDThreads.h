/*
 *  LEDThreads.h
 *  CirrusAmbientMonitor
 *
 *  Created by Ben Guthro on Wed Mar 02 2005.
 *  Copyright (c) 2005 gmb. All rights reserved.
 *
 */
#ifndef __LEDTHREADS_H__
#define __LEDTHREADS_H__
#include "LEDControl.h"
class CGenericCalibrator;

bool startLEDAnimationThread(CGenericCalibrator *cal, ALED_ANIMATION whichAnim,  ALED_ANIM_SPEED howFast);
bool stopLEDAnimationThread();

#endif