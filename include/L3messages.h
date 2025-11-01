//L3messages.h
#ifndef WM_USER
#define WM_USER 0x100
#endif


// define user window messages

#define STRING_MESSAGE_PENDING  (WM_USER + 0x0100) // this is the message that will be sent to indicate a string is pending
#define THREAD_COMPLETION_MSG   (WM_USER + 0x0101) // this is the message that a functional thread is complete. 

#define WM_USER_UPDATE_DATA		(WM_USER + 0x0111) // this message is sent to update calibrate dialog


typedef enum {

	L3M_OSD_CLOSED = WM_USER + 0x0200, // sent to the opening window to indicate that the panel has been closed
	L3M_OSD_ADJUST_SET, // this means that a user has elected to adjust the controls.
	L3M_OSD_DATA_UPDATE  // this message indicates that either the sicm or osd has changed a variable.  
}L3MESSAGE;