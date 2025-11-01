#ifndef CALIBRATIONINFO_H_INCLUDED
#define CALIBRATIONINFO_H_INCLUDED

typedef enum
{
	whichappNOT_SET = 0,
	whichappLEVEL_1,
	whichappLEVEL_2,
	whichappLEVEL_3,
	whichappLEVEL_4
}WHICH_APP;

typedef enum
{
	remREMINDER_OFF = 0,
	remDAILY,
	remWEEKLY,
	remMONTHLY,
	remEVERY_MONDAY,
	remEVERY_TUESDAY,
	remEVERY_WEDNESDAY,
	remEVERY_THURSDAY,
	remEVERY_FRIDAY,
	remEVERY_SATURDAY,
	remEVERY_SUNDAY,
	remEVERY_OTHER_DAY,
	remEVERY_OTHER_WEEK
}REMINDER_FREQ;


typedef struct CalibrationInfo
{
	time_t			LastCal;
	bool				bReminderOn;
	REMINDER_FREQ	RemFreq;
} CalibrationInfo;

#endif
