#ifndef SICM_CALLBACKS_H_INCLUDED
#define SICM_CALLBACKS_H_INCLUDED

class CProgressList;

// Defined callback types known to SICMProcesses
typedef enum {
    SICM_CALLBACK_SHOW_STRING,		// String sent back for display
	SICM_CALLBACK_SHOW_STRING_WAIT,	// Show string and wait for response.
    SICM_CALLBACK_THREAD_COMPLETE,	// Calibration thread done.
	SICM_CALLBACK_SHOW_TARGET,		// CalTargetDisplay replacement/hook
	SICM_CALLBACK_STATUS_UPDATE,	// Status Reporting
	SICM_CALLBACK_EXCEPTION,		// Exception reporting.
	SICM_CALLBACK_PROGRESS_PERCENT,	// For a progress bar if needed.
	SICM_CALLBACK_SHOW_WARNING,		// For a warning message box
	SICM_CALLBACK_SHOW_ERROR,		// For an error warning box.
	SICM_CALLBACK_LOAD_STRING,		// To get a string from an ID.
	SICM_CALLBACK_FILEOP_ERROR,		// To report file errors.
	SICM_CALLBACK_PRECAL_COLORTEMP,	// To have user adjust color temp
	SICM_CALLBACK_PRECAL_GAINS,		// To have user adjust RGB gains
	SICM_CALLBACK_SHOW_VISTARGET,	// Now a separate callback.
	SICM_CALLBACK_CALIBRATOR_CHECK,	// To report calibrator not on screen.
	SICM_CALLBACK_OVERLAY_OP,		// Interact with video overlay
    NUM_SICM_CALLBACK_TYPES
} SICM_CALLBACK_TYPE;

// Defined types of operation for SICM_CALLBACK_SHOW_TARGET ops.
typedef enum {
	SICM_TARGET_TYPE_NONE,
	SICM_TARGET_PATCH,
	SICM_TARGET_VISTARGET,
	SICM_TARGET_BUILD_VALUES,
	NUM_SICM_TARGET_TYPES
} SICM_TARGET_TYPE;

// Defined exception types for SICM_CALLBACK_EXCEPTION
// and SICM_CALLBACK_FILEOP_ERROR reporting.
typedef enum {
	SICM_EXCEPTION_MAX_LUM,
	SICM_EXCEPTION_FILE_OPEN,
	SICM_EXCEPTION_FILE_WRITE,
	SICM_EXCEPTION_FILE_READ,
	SICM_EXCEPTION_FILE_CLOSE,
	NUM_SICM_EXCEPTION_TYPES
} SICM_EXCEPTION_TYPE;

// Defined directives for how/when to return from a callback
typedef enum {
	SICM_LOOPSTATE_WAIT,	// Don't return yet - poll at an interval for this to change.
	SICM_LOOPSTATE_DONE,	// Return with DONE status.
	SICM_LOOPSTATE_ABORT,	// Calling function should abort
	SICM_LOOPSTATE_CONTINUE	// Return with indicator to continue.
} SICM_LOOPSTATE_TYPE;

typedef enum {
	SICM_PRECAL_COLORTEMP,
	SICM_PRECAL_BRIGHTNESS,
	SICM_PRECAL_CONTRAST,
	SICM_PRECAL_GAINS
} SICM_PRECAL_TYPE;

typedef enum {
	SICM_OVERLAYOP_START,	// Do whatever is required to support use of video overlay
	SICM_OVERLAYOP_END,		// Finished using the overlay. Restore to previous state?
} SICM_OVERLAYOP_TYPE;

// Generic data structure for all callbacks
typedef struct {
	SICM_CALLBACK_TYPE cbType;
	SICM_LOOPSTATE_TYPE loopState;
	SICM_TARGET_TYPE type;
	union
	{
		struct {			// For SICM_CALLBACK_SHOW_TARGET with
			short R;		//     SICM_TARGET_PATCH operation.
			short G;
			short B;
		} colors;

		double gamma;		// For SICM_CALLBACK_SHOW_TARGET with
							//     SICM_TARGET_BUILD_VALUES operation.

		struct {			// For SICM_CALLBACK_STATUS_UPDATE
			CProgressList *progList;
		} progress;			// struct to allow for future expansion

		struct {			// For SICM_CALLBACK_LOAD_STRING
			int id;
			char *str;
		} string;

		struct {			// For SICM_CALLBACK_SHOW_ERROR, or ...SHOW_WARNING
			char *str;
		} warning_error;

		struct {			// For SICM_CALLBACK_FILEOP_ERROR
			char *fileName;
			SICM_EXCEPTION_TYPE type; // one of SICM_EXCEPTION_FILE_OPEN/CLOSE/WRITE/READ
		} fileOperation_error;

		struct {			// For SICM_OVERLAY_OP
			SICM_OVERLAYOP_TYPE type;
		} overlayOperation;

		struct {
			SICM_PRECAL_TYPE type;
			union
			{
				struct {			// For SICM_CALLBACK_PRECAL_COLORTEMP
					double desiredTemp;
					double currentTemp;
				} colorTemp;

				struct {			// For SICM_CALLBACK_PRECAL_GAINS
					double red;
					double green;
					double blue;
				} gains;
			};
		} precal_operation;

		struct {			// For SICM_CALLBACK_SHOW_STRING_WAIT
			char *str;
		} string_wait;
	} params;
} SICM_TARGET_STRUCT;

#endif


