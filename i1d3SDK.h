/**
* \mainpage
 <pre>
@author X-Rite Inc.

@section USB Driver Installation

The i1Display3 is an HID device. The USB driver is part of the operating system.
No driver is supplied with this SDK.

@section Software Library

The i1d3SDK library contains software that interfaces to the i1Display3.


These files are necessary to build an application that uses the i1Display3 under MacOSX:

    - i1d3SDK.H
    - i1d3SDK.framework

    The i1d3SDK.framework must be put in the Frameworks folder inside the application bundle.


These files are necessary to build an application that uses the i1Display3 under Windows:

    - i1d3SDK.H
    - i1d3SDK.LIB

    The following file is necessary to execute the application and must be included in
    the same folder as the application or placed in the Windows path:

    - i1d3SDK.DLL





* ******************************************************************************
* *                         C O P Y R I G H T
* ******************************************************************************
* *
* *     Copyright (c) 2010-2013 X-Rite Inc.
* *            THIS INFORMATION IS COMPANY CONFIDENTIAL
* *
* * NOTICE:  This material is a confidential trade secret and proprietary
* * information of X-Rite Inc. which may not be reproduced, used,
* * sold, or transferred to any third party without the prior written consent
* * of Xrite Inc.  This material is also copyrighted as an unpublished work
* * under sections 104 and 408 of Title 17 of the United States Code.
* * Unauthorized use, copying, or other unauthorized reproduction of any form
* * is prohibited.
* *

 </pre>

******************************************************************************/
#pragma once
#include <time.h>

#ifndef __I1D3_SDK_H__
#define __I1D3_SDK_H__
/*
* Note: This header has been formatted for documentation generation by doxygen
*
*/

#ifdef __cplusplus
extern "C" {
#endif

    /**
    * \defgroup meas_types Measurement Header Data Types
    *  data types specific to a measurement header type
    */
    /*@{*/


    /*****************************************************************************/
    /*! \var i1d3ColorSpace_t
    *	\brief Color Space
    *
    *	This emumeration is used to specify the color space
    */
    /*****************************************************************************/
    typedef enum {
        i1d3ColorSpaceYxy,					/**< Yxy Color Space		*/
        i1d3ColorSpaceXYZ,					/**< XYZ Color Space		*/
        i1d3ColorSpaceRGB,					/**< Raw RGB Color Space		*/
    }i1d3ColorSpace_t;

    /*****************************************************************************/
    /*! \var i1d3MeasMode_t
    *	\brief Measurement mode
    *
    *	This emumeration is used to specify the different types of measurement modes
    */
    /*****************************************************************************/
    typedef enum {
        i1d3MeasModeCRT = 0,				/**< CRT Measurement mode		*/
        i1d3MeasModeLCD = 1,					/**< LCD Measurement mode		*/

        // Following modes not supported - maintained for X-Rite internal use only
        i1d3MeasModeLCDsim = 2,				/**< unsupported-for X-Rite internal use only*/
        i1d3MeasModeLCDseq = 3,				/**< unsupported-for X-Rite internal use only*/
        i1d3MeasModeCRTFixed = 4,			/**< unsupported-for X-Rite internal use only*/
        i1d3MeasModeCRTAutoDark = 5,		/**< unsupported-for X-Rite internal use only*/
        i1d3MeasModeLCDsimFixed = 6,		/**< unsupported-for X-Rite internal use only*/

        // New mode added 20Mar12 for plasmas and other pulsing displays
        i1d3MeasModeBurst = 7,				/**<
                                            Burst mode should be used for measuring plasma,
                                            CRTs and other pulsating displays. It provides more
                                            accurate results than standard CRT measurement mode
                                            especially on darker color patches.*/

                                            // New measurement mode added 17Apr14 for i1Display3 devices with firmware v2.28 and later
        i1d3MeasModeAIO = 8                 /**<
                                            AIO (All In One) mode provides better and faster results on any given
                                            display type. However it can only be used with firmware v2.16 (and later).
                                            For backward compatibility the old modes will still work. However using
                                            AIO mode is recommended for use with all display types. AIO mode is available
                                            as of firmware v2.28 (and later). AIO mode will also consider the integration
                                            time that has been set.

                                            \attention If i1d3MeasModeAIO is used with firmware prior to v2.28
                                            i1d3ErrFunctionNotAvailable will be returned.*/

    }i1d3MeasMode_t;

    /*****************************************************************************/
    /*! \var i1d3LumUnits_t
    *	\brief Luminance units
    *
    *	This emumeration is used to distinguish luminance measurement unit types
    */
    /*****************************************************************************/
    typedef enum {
        i1d3LumUnitsFootLts,					/**< Foot Lamberts		*/
        i1d3LumUnitsNits						/**< Candelas/m^2		*/
    }i1d3LumUnits_t;

    //end measurement header
    /*@}*/


    /**
    * \defgroup cir_types Data Types and Structures
    */
    /*@{*/

    /*****************************************************************************/
    /*!	\brief LED Control states
    *
    *	An enumeration that describes the available behaviours of the LED.
    */
    /*****************************************************************************/
    typedef enum {
        // LED Control states
        i1d3LED_OFF = 0,				/**< LEDs are off */
        i1d3LED_FLASH = 1,				/**< LEDs flash */
        i1d3LED_PULSE = 3				/**< LEDs pulse */
    } i1d3LED_Control;


    /*****************************************************************************/
    /*!	\brief Measurement control states for backlight synchronization
    *
    *	An enumeration that describes the available options that allow to choose
    *   between a normal measurement and a measurement that is synchronized to the
    *   display's backlight frequency. In some cases a synchronized measurement might
    *   yield better results.
    *
    *   \see i1d3SetBacklightFreqSync()
    *   \see i1d3SetBacklightFreq()
    */
    /*****************************************************************************/
    enum {
        //measurement control states
        backlightSyncOff = 0, /**< Measure with backlight frequency synchronization off */
        backlightSyncOn = 1	  /**< Measure with backlight frequency synchronization on */
    }; typedef unsigned char i1d3BacklightFreqSyncOption_t;

    /*****************************************************************************/
    /*!	\brief Defines the maximum value for the backlight frequency that can be
    *          set with i1d3SetBacklightFreq()
    */
    /*****************************************************************************/
#define MAX_BACKLIGHT_FREQ 32767

/*****************************************************************************/
/*! \var i1d3Status_t
*	\brief SDK return status
*
*	This emumeration will be returned by all functions in this SDK to indicate
*	return status of the function call.
*/
/*****************************************************************************/
    typedef enum {
        i1d3Success = 0,		/**< Function Succeeded 		*/
        i1d3Err = -100,	/**< Nonspecific error 			*/
        i1d3ErrInvalidDevicePtr = -101,	/**< Device pointer is NULL		*/
        i1d3ErrNoDeviceFound = -102,	/**< No device found			*/

        // Errors passed through from calibrator class
        i1d3ErrFunctionNotAvailable = -504,	/**< The requested Function is not supported by this device */
        i1d3ErrLockedCalibrator = -505,	/**< The device is password-locked */
        i1d3ErrCalibratorAlreadyOpen = -508,	/**< The device is currently initialized */
        i1d3ErrCalibratorNotOpen = -509,	/**< No device is currently initialized */
        i1d3ErrTransactionError = -510,	/**< The communications are out of sync  */
        i1d3ErrWrongDiffuserPosition = -512,	/**< The diffuser arm is in the wrong position for measurement */
        i1d3ErrIncorrectChecksum = -513,	/**< The calculated checksum is incorrect */
        i1d3ErrInvalidParameter = -517,	/**< An invalid parameter was passed into the routine */
        i1d3ErrCalibratorError = -519,	/**< The device returned an error */
        i1d3ErrObsoleteFirmware = -520,	/**< The firmware is obsolete */
        i1d3ErrCouldNotEnterBLMode = -521,   /**< Error entering bootloader mode */
        i1d3ErrUSBTimeout = -522,	/**< USB timed out waiting for response from device */
        i1d3ErrUSBCommError = -523,	/**< USB communication error */
        i1d3ErrEEPROMWriteProtected = -524,	/**< EEPROM-write protection error */

        // Errors passed through from matrix generator class
        i1d3ErrMGBadFile = -600,	/**< Couldn't open file */
        i1d3ErrMGTooFewColors = -601,	/**< Must have at least 3 colors in EDR file.*/
        i1d3ErrMGBadWavelengthIncrement = -602,	/**< Currently we require 1nm wavelength increment*/
        i1d3ErrMGBadWavelengthEnd = -603,	/**< Currently we require up to at least 730nm.*/
        i1d3ErrMGBadWavelengthStart = -604,	/**< Currently we require start at 380nm.*/
        i1d3ErrNoCMFFile = -605,	/**< Couldn't open CMF data file */
        i1d3ErrCMFFormatError = -606,	/**< Couldn't parse CMF data file */

        // Errors passed through from EDR Support class
        i1d3ErrEDRFileNotOpen = -700,	/**< Must open file before making other requests. */
        i1d3ErrEDRFileAlreadyOpen = -701,	/**< File already opened, close to open another file. */
        i1d3ErrEDRFileNotFound = -702,	/**< File not found. */
        i1d3ErrEDRSizeError = -703,	/**< File too short. */
        i1d3ErrEDRHeaderError = -704,	/**< Header didn't have correct signature or file too short. */
        i1d3ErrEDRDataError = -705,	/**< Data didn't load properly. */
        i1d3ErrEDRDataSignatureError = -706,	/**< Signature didn't match - corrupted file? */
        i1d3ErrEDRSpectralDataSignatureError = -707,	/**< Signature didn't match - corrupted file? */
        i1d3ErrEDRIndexTooHigh = -708,	/**< Requested more color data than available */
        i1d3ErrEDRNoYxyData = -709,	/**< Can't request tri-stimulus */
        i1d3ErrEDRNoSpectralData = -710,	/**< Can't request spectral data in file without it. */
        i1d3ErrEDRNoWavelengthData = -711,	/**< No spectral data in file - in response to GetWavelengths */
        i1d3ErrEDRFixedWavelengths = -712,	/**< Evenly-spaced wavelengths */
        i1d3ErrEDRWavelengthTable = -713,	/**< Wavelengths are from table */
        i1d3ErrEDRParameterError = -714,	/**< Probably a null pointer to a call */

        // Errors returned from i1Display3 devices
        i1d3ErrHW_Locked = 16,		/**< i1Display3 is Locked */							//0x10
        i1d3ErrHW_I2CLowClock = 80,		/**< EEPROM access error: clock is low */				//0x50
        i1d3ErrHW_NACKReceived = 81,		/**< EEPROM access error: NACK received */				//0x51
        i1d3ErrHW_EEAddressInvalid = 96,		/**< Invalid EEPROM address */							//0x60
        i1d3ErrHW_InvalidCommand = 128,	/**< Invalid command to i1Display3 */					//0x80
        i1d3ErrHW_WrongDiffuserPosition = 129,	/**< Diffuser is in wrong positon for measurement */	//0x81

        // Errors returned from i1Display3 Rev. B devices / i1d3DC devices
        i1d3ErrHW_InvalidParameter = 130,    /**< Invalid parameter passed to device */              //0x82
        i1d3ErrHW_PeriodeTimeOut = 131,    /**< Period measurement timed out */                    //0x83
        i1d3ErrHW_InvalidMeasurement = 132,    /**< No valid measurement data for get Yxy function */  //0x84
        i1d3ErrHW_MatrixChecksum = 144,    /**< Matrix is missing or corrupt */                    //0x90
        i1d3ErrHW_MatrixAmbient = 145     /**< Ambient matrix is missing or corrupt */            //0x91

    }i1d3Status_t;


    /*****************************************************************************/
    /*!	\brief CIE Yxy data
    *
    *	A structure to encapsulate a CIE Y,x,y data point
    */
    /*****************************************************************************/
    typedef struct {
        double Y;		/**< Y luminance data in Cd/m2, or Lux */
        double x;		/**< x chrominance data */
        double y;		/**< y chrominance data */
        double z;		/**< z (internal use for computation purposes - Applications should not rely on this element to always be valid) */
    } i1d3Yxy_t;


    /*****************************************************************************/
    /*!	\brief Calibrator raw RGB data
    *
    *	A structure to encapsulate raw, unscaled RGB data from the device.<BR>
    *   This data is uncalibrated, and sensor S/N specific.
    */
    /*****************************************************************************/
    typedef struct {
        double R;		/**< Red unscaled raw data 	*/
        double G;		/**< Green unscaled raw data */
        double B;		/**< Blue unscaled raw data */
    } i1d3RGB_t;


    /*****************************************************************************/
    /*!	\brief Calibrator XYZ data
    *
    *	A structure to encapsulate XYZ data from the device
    */
    /*****************************************************************************/
    typedef struct {
        double X;		/**< X tristimulus value (1931 CIE Standard Observer) 	*/
        double Y;		/**< Y tristimulus value (1931 CIE Standard Observer) */
        double Z;		/**< Z tristimulus value (1931 CIE Standard Observer) */
    } i1d3XYZ_t;


    /*****************************************************************************/
    /*!  \var typedef void* i1d3Handle
    *	 \brief Handle type to device
    *    \see i1d3GetDeviceHandle()
    *
    *     Used as input to functions
    */
    /*****************************************************************************/
    typedef void* i1d3Handle;

    /*****************************************************************************/
    /*!	\brief Calibration source type
    *
    *	An enumeration that describes the source of a calculated calibration matrix.
    */
    /*****************************************************************************/
    typedef enum {
        // Calibration data sources
        CS_FACTORY = 0,					/**< Calibration from conventional cal. station (named calibration) */
        CS_GENERIC_CMF = 1,				/**< matrix from combination of spectral data and internal CMF data */
        CS_CUSTOM_CMF = 2,				/**< matrix from user-supplied CMF data file */
        CS_GENERIC_DISPLAY = 3,			/**< matrix calculated from SDK-supplied EDR file for generic display type */
        CS_USER_SUPPLIED = 4			/**< matrix calculated from user-supplied EDR file. */
    } i1d3CALIBRATION_SOURCE;

    /*****************************************************************************/
    /*!	\brief Calibration entry
    *
    *	A structure that encapsulates all information about a calibration to support
    *	programatic selection.
    */
    /*****************************************************************************/
    typedef struct
    {
        union
        {
            i1d3CALIBRATION_SOURCE calSource; /**< see above */
            unsigned char padding1[8];
        };

        union
        {
            time_t calTime;				/**< time-stamp of calibration for internal or from within EDR file */
            unsigned char padding2[8];
        };

        char fileName[512];				/**< blank for internal or CMF matrix. File name of EDR file otherwise.*/
        char displayName[64];			/**< from EDR file - will be something like "Generic CCFL" for such files.*/
        char displayMfg[64];			/**< from EDR file*/
        char displayModel[64];			/**< from EDR file*/
        char key[32];					/**< name of calibration for internal matrices, "CMF" for computed matrix,*/
                                        /**< something like "_CCFL_" for generic display EDR file,*/
                                        /**< composed from 3 character mfg code and model number for user-supplied EDR*/
        short edrDisplayType;			/**< enumeration value from EDR*/
    } i1d3CALIBRATION_ENTRY;

    /*****************************************************************************/
    /*!	\brief i1d3CALIBRATION_LIST
    *
    *	A list of all currently-available calibrations, for possible selection.
    */
    /*****************************************************************************/
#define MAX_I1D3CALIBRATION_ENTRIES 64

    typedef struct
    {
        i1d3CALIBRATION_ENTRY *cals[MAX_I1D3CALIBRATION_ENTRIES];
    } i1d3CALIBRATION_LIST;


    /*****************************************************************************/
    /*!	\brief Device info
    *
    *	A structure that define information about the device.
    */
    /*****************************************************************************/
    typedef struct
    {
        char			strProductName[32];
        unsigned short	usProductType;
        char			strFirmwareVersion[32];
        char			strFirmwareDate[32];
        unsigned char	ucIsLocked;
    } i1d3DEVICE_INFO;


    // end Data Types and Structures
    /*@}*/

#ifndef SDK_DATATYPES_ONLY
/*
    The main API
*/

/**
*	\defgroup api i1d3 SDK API functions
*/
/*@{*/


// declare exported functions
#if !defined(PDEC)
#if defined(_WIN32) || defined(__CYGWIN__)
#define PDEC extern __declspec(dllimport)
#else
#define PDEC
#endif
#endif



/** @name Global API functions
 *  These functions are used to open and close the i1d3 SDK, as well as obtaining a
 *   handle to a specific device and open and close that device.
 */
 /*@{*/

 /*****************************************************************************/
 /** 	\fn i1d3Status_t i1d3Initialize()
 *		\brief Initializes the SDK
 *
 *		This function initializes the SDK. This call must be called before any
 *		other i1d3 SDK calls. It must be paired with a call to i1d3Destroy.
 */
 /*****************************************************************************/
    PDEC i1d3Status_t i1d3Initialize();

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3Destroy()
    *		\brief Closes the SDK
    *
    *		This function cleans up the SDK; closing any open devices, and cleans up
    *		allocated memory.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3Destroy();


    /*****************************************************************************/
    /** 	\fn unsigned int i1d3GetNumberOfDevices()
    *		\brief Returns the number of devices attached and enumerated on USB
    *
    */
    /*****************************************************************************/
    PDEC unsigned int i1d3GetNumberOfDevices();

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetDeviceHandle(unsigned int whichDevice, i1d3Handle *devHndl)
    *		\brief Gets a pointer to the device
    *		\param whichDevice which i1d3 device to use (only one supported currently)
    *		\param devHndl a handle to the device returned
    *
    *		Returns the device handle.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetDeviceHandle(unsigned int whichDevice, i1d3Handle *devHndl);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3OverrideDeviceDefaults(unsigned int vid,unsigned int pid,unsigned char* productkey)
    *		\brief Overrides the SDK defaults when opening a device.
    *		\param vid Vendor ID to look for on the USB bus
    *		\param pid Product ID to look for on the USB bus
    *		\param productkey Product Key to use to unlock the device
    *
    *		In normal use this function should not be necessary. It is provided for use of OEM development
    *		 and factory calibrations.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3OverrideDeviceDefaults(unsigned int vid, unsigned int pid, unsigned char* productkey);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3DeviceOpen(i1d3Handle devHndl)
    *		\brief Opens a device
    *		\param devHndl handle to the device
    *		\see i1d3GetDeviceHandle()
    *
    *		This function opens a device via a handle received from i1d3GetDeviceHandle()
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3DeviceOpen(i1d3Handle devHndl);


    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3DeviceClose(i1d3Handle devHndl)
    *		\brief Closes a device
    *		\param devHndl handle to the device
    *		\see i1d3GetDeviceHandle()
    *
    *		This function closes a device via a handle recieved from i1d3GetDeviceHandle()
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3DeviceClose(i1d3Handle devHndl);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3DeviceQuickOpen(i1d3Handle devHndl)
    *		\brief Get info from device without full open
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\see i1d3GetDeviceHandle()
    *
    *		This function identifies the device type via a handle recieved from i1d3GetDeviceHandle()
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3DeviceQuickOpen(i1d3Handle devHndl);


    //end global functions
    /*@}*/


    /** @name Information functions
     *  These functions return information about the library and device.
     */
     /*@{*/

     /*****************************************************************************/
     /** 	\fn char* i1d3GetToolkitVersion(char *ver)
     *		\brief Returns the version string of the i1d3 toolkit
     *		\param ver if not NULL, copies version into ver
     */
     /*****************************************************************************/
    PDEC char* i1d3GetToolkitVersion(char *ver);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetDeviceInfo ( i1d3Handle devHndl, i1d3DEVICE_INFO *infostruct )
    *		\brief Returns the a structure with information about the device
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param infostruct info returned in structure
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetDeviceInfo(i1d3Handle devHndl, i1d3DEVICE_INFO *infostruct);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetSerialNumber ( i1d3Handle devHndl, char *sn )
    *		\brief Returns the serial number of the device.
    *		\param devHndl devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param sn serial number string returned. Buffer size 21 minimum.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetSerialNumber(i1d3Handle devHndl, char *sn);



    //end Information functions
    /*@}*/









    /** @name Calibration functions
     *  These functions are used to retrieve available calibration data and select one to use.
     */
     /*@{*/

     /*****************************************************************************/
     /** 	\fn long i1d3GetCalibrationList(i1d3Handle devHndl, int *numCals, i1d3CALIBRATION_LIST **cals)
     *		\brief Return a pointer to a list of all available calibrations.
     *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
     *		\param numCals number of valid calibration matrices
     *		\param **cals location at which the pointer to the list is to be delivered.
     *
     *		On Open call, we generate a list of all of the calibrations we know about. This
     *		includes all of  the type 0, 1, 2, 3 CALIBRATION_SOURCE entries as well as
     *		the last user-specified (type 4) entry. (CS_FACTORY ones are the internal ones,
     *		CS_CMF is the one calculated from the current CMF data, and CS_GENERIC_DISPLAY
     *		are the ones (specified in a control file) corresponding to the generic display
     *		EDRs we have.
     *
     *		The caller may access each of the calibrations in the list by accessing the
     *		list's 'cals' member data. (Such as calList->cals[i].)
     */
     /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetCalibrationList(i1d3Handle devHndl, int *numCals, i1d3CALIBRATION_LIST **cals);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetCalibrationFromFile (i1d3Handle devHndl, unsigned char *EDRFileName)
    *		\brief Calculate calibration matrix from spectral data within an EDR file.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param *EDRFileName Fully-qualified path to the file.
    *
    *		Spectral data is read from a monitor-specific EDR file and used to calculate
    *		the matrix to be used for measurement purposes.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetCalibrationFromFile(i1d3Handle devHndl, unsigned char *EDRFileName);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetCalibrationFromBuffer (i1d3Handle devHndl, unsigned char *buffer, int bufferSize)
    *		\brief Calculate calibration matrix from spectral data within an EDR file.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param *buffer buffer containing entire EDR file contents
    *		\param bufferSize size of the buffer in bytes
    *
    *		Spectral data is read from a buffer containing monitor-specific EDR file data
    *       (presumably read by an application or utility program) and used to calculate
    *		the matrix to be used for measurement purposes.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetCalibrationFromBuffer(i1d3Handle devHndl, unsigned char *buffer, int bufferSize);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3LoadCMFDataFile (i1d3Handle devHndl, const char *CMFFileName, short type)
    *		\brief Override internal CMF data with user-supplied CMF data in file.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param *CMFFileName Fully-qualified path to the file.
    *		\param type 1: Override for monitor measurements, 2: For ambient, 3: for both
    *
    *		An array of elements of CMF data file is read from the specified file.
    *		(The format of this file is supplied in a separate document).
    *
    *		NOTE: After replacing the CMF data, the previous CMF and EDR-based matrices
    *		must be recalculated using the new CMF data. This is done automatically
    *		by the SDK but requires that the last EDR file specified by the caller
    *		(in the i1d3SetCalibrationFromFile() call) still be accessible. (If the
    *		caller had not previously called that function, there is no issue.)
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3LoadCMFDataFile(i1d3Handle devHndl, const char *CMFFileName, short type);


    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetSupportFilePath (i1d3Handle devHndl, const char *path)
    *		\brief Specifies file path where SDK looks for support files.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param *path - Path to directory.
    *
    *		This data includes a mapping file that specifies the names of EDR files
    *		that provide spectral sensitivity data for displays of a specific generic type as
    *		well as the files which include that data.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetSupportFilePath(i1d3Handle devHndl, const char *path);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetCalibration(i1d3Handle devHndl, i1d3CALIBRATION_ENTRY *calToUse)
    *		\brief Selects the active calibration in the device to use for measurements
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param calToUse pointer to the calibration to be selected.
    *		\see i1d3GetDeviceHandle()
    *
    *		This function selects which stored calibration to use for measurements.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetCalibration(i1d3Handle devHndl, i1d3CALIBRATION_ENTRY *calToUse);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetCalibration(i1d3Handle devHndl, i1d3CALIBRATION_ENTRY **cal);
    *		\brief Returns the active calibration
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param cal pointer to receive address of calibration entry for current matrix.
    *		\see i1d3GetDeviceHandle()
    *
    *		This function returns the active calibration matrix.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetCalibration(i1d3Handle devHndl, i1d3CALIBRATION_ENTRY **cal);

    //end Calibration functions
    /*@}*/


    /** @name Measurement Setup functions
     *  These functions are used to setup and view measurement parameters.
     */
     /*@{*/

     /*****************************************************************************/
     /** 	\fn i1d3Status_t i1d3SetMeasurementMode(i1d3Handle devHndl, i1d3MeasMode_t measMode)
     *		\brief Sets the measurement mode of the device
     *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
     *		\param measMode which measurement mode to select in the device.
     *
     *		This function sets the measurement mode in the device.
     */
     /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetMeasurementMode(i1d3Handle devHndl, i1d3MeasMode_t measMode);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetMeasurementMode(i1d3Handle devHndl, i1d3MeasMode_t *measMode)
    *		\brief Returns the current measurement mode
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param measMode measurement mode returned.
    *
    *		This function returns the current measurement mode used for measurements.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetMeasurementMode(i1d3Handle devHndl, i1d3MeasMode_t *measMode);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3Status_t i1d3SetLuminanceUnits(i1d3Handle devHndl, i1d3LumUnits_t lumUnits)
    *		\brief Sets the standard luminance unit
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param lumUnits standard luminance unit to be set.
    *		\see i1d3GetDeviceHandle()
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetLuminanceUnits(i1d3Handle devHndl, i1d3LumUnits_t lumUnits);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3Status_t i1d3GetLuminanceUnits(i1d3Handle devHndl, i1d3LumUnits_t lumUnits)
    *		\brief Gets the standard luminance unit
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param lumUnits standard luminance unit returned.
    *		\see i1d3GetDeviceHandle()
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetLuminanceUnits(i1d3Handle devHndl, i1d3LumUnits_t *lumUnits);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetIntegrationTime(i1d3Handle devHndl, double dSeconds)
    *		\brief Sets the integration time used for measurements in CRT mode
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dSeconds Integration time in seconds.
    *		\see i1d3GetDeviceHandle()
    *
    *		This function sets the integration time used for measurements in CRT mode.
    *		The value must be > 0.0 seconds. Default is 0.2 seconds.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetIntegrationTime(i1d3Handle devHndl, double dSeconds);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetIntegrationTime(i1d3Handle devHndl, double *dSeconds)
    *		\brief Gets the integration time currently set
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dSeconds Integration time in seconds returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function gets the integration time currently set in the device
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetIntegrationTime(i1d3Handle devHndl, double *dSeconds);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetTargetLCDTime(i1d3Handle devHndl, double dSeconds)
    *		\brief Sets the Target measurement time in seconds used in LCD mode
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dSeconds Number of seconds device will attempt to integrate for.
    *		\see i1d3GetDeviceHandle()
    *
    *		This function sets the target time in seconds to use for measurements in LCD mode.
    *		Default is 0.2 seconds.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetTargetLCDTime(i1d3Handle devHndl, double dSeconds);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetTargetLCDTime(i1d3Handle devHndl, double *dSeconds)
    *		\brief Gets the Target measurement time currently set
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dSeconds LCD Target time returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function returns the target LCD time to use when measuring in LCD mode.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetTargetLCDTime(i1d3Handle devHndl, double *dSeconds);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SupportsAIOMode(i1d3Handle devHndl)
    *		\brief Returns i1d3Success if device supports i1d3MeasModeAIO,
    *              i1d3ErrFunctionNotAvailable otherwise.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SupportsAIOMode(i1d3Handle devHndl);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetBacklightFreq(i1d3Handle devHndl, unsigned short freqHz)
    *		\brief Sets the backlight frequency. The default value is 60 (Hz).
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param freqHz backlight frequency to be set. The maximum value that can be set
    *              is defined by MAX_BACKLIGHT_FREQ. If the value for freqHz exceeds
    *              this limit an i1d3ErrInvalidParameter error will be returned.
    *
    *       \note This setting affects AIO measurement mode only
    *       \see i1d3MeasureBacklightFrequency()
    *       \see i1d3SetBacklightFreqSync()
    *
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetBacklightFreq(i1d3Handle devHndl, unsigned short freqHz);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetBacklightFreq(i1d3Handle devHndl, unsigned short *freqHz)
    *		\brief Returns the current backlight frequency
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param freqHz current backlight frequency returned.
    *
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetBacklightFreq(i1d3Handle devHndl, unsigned short *freqHz);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetBacklightFreqSync(i1d3Handle devHndl, i1d3BacklightFreqSyncOption_t option)
    *		\brief Sets the backlight frequency synchronization option.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param option backlight frequency sync option to be set.
    *
    *       \note This setting affects AIO measurement mode only
    *
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetBacklightFreqSync(i1d3Handle devHndl, i1d3BacklightFreqSyncOption_t option);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetBacklightFreqSync(i1d3Handle devHndl, i1d3BacklightFreqSyncOption_t *option)
    *		\brief Returns current backlight frequency synchronization option.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param option current backlight frequency sync option returned.
    *
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetBacklightFreqSync(i1d3Handle devHndl, i1d3BacklightFreqSyncOption_t *option);


    //end Measurement Setup functions
    /*@}*/


    /** @name Measurement functions
     *  These functions are used to invoke a measurement from the device, and return data
     */
     /*@{*/

     /*****************************************************************************/
     /** 	\fn i1d3Status_t i1d3MeasureRGB(i1d3Handle devHndl, i1d3RGB_t *dRGBMeas)
     *		\brief Measures and returns RGB data
     *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
     *		\param dRGBMeas measurement result returned
     *		\see i1d3GetDeviceHandle()
     *
     *		This function takes a measurement using the current measurement configuration, and returns the raw RGB data in
     * 		 a i1d3RGB_t structure.
     */
     /*****************************************************************************/
    PDEC i1d3Status_t i1d3MeasureRGB(i1d3Handle devHndl, i1d3RGB_t *dRGBMeas);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3MeasureXYZ(i1d3Handle devHndl, i1d3XYZ_t *dXYZmeas)
    *		\brief Takes a measurement using the current configuration and returns XYZ data
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dXYZmeas measured XYZ data returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function takes a measurement using the current configuration, and returns
    *		XYZ values.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3MeasureXYZ(i1d3Handle devHndl, i1d3XYZ_t *dXYZmeas);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3MeasureYxy(i1d3Handle devHndl, i1d3Yxy_t *dYxy)
    *		\brief Takes a measurement using the current configuration and returns Yxy data
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dYxy measured Yxy data returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function takes a measurement using the current configuration, and returns
    *		the Yxy luminance and chrominance values.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3MeasureYxy(i1d3Handle devHndl, i1d3Yxy_t *dYxy);


    /*****************************************************************************/
    /** 	\fn PDEC i1d3Status_t i1d3Measure(
                                        i1d3Handle		devHndl,
                                        i1d3LumUnits_t	units,
                                        i1d3MeasMode_t	measType,
                                        i1d3Yxy_t			*dYxyMeas)

    *		\brief Takes a measurement using the parameters and returns Yxy data
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param units Obsolete
    *		\param measType the type of measurement to take
    *		\param dYxyMeas Yxy measurement data returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function takes a measurement using the parameters and returns the
    *		Yxy luminance and chrominance values.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3Measure(
        i1d3Handle		devHndl,
        i1d3LumUnits_t	units,
        i1d3MeasMode_t	measType,
        i1d3Yxy_t			*dYxyMeas);


    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3MeasureAmbient(i1d3Handle devHndl, i1d3Yxy_t *dYxy)
    *		\brief Takes a measurement of ambient light using the current configuration
    *			and returns Yxy data. (Y is in units of lux.)
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param dYxy measured Yxy data returned
    *		\see i1d3GetDeviceHandle()
    *
    *		This function takes a measurement of ambient light using the current
    *		configuration, and returns the Yxy luminance and chrominance values.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3MeasureAmbient(i1d3Handle devHndl, i1d3Yxy_t *dYxy);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetLastMeasurement(i1d3Handle devHndl, i1d3ColorSpace_t space, i1d3LumUnits_t	units, void *resultPtr)
    *		\brief Returns measurement data from the last measurement
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param space color space to convert measurement result
    *		\param units luminance units for result
    *		\param resultPtr measurement data returned in the requested color space and units
    *
    *		This function does not take a measurement, but returns data from the last measurement
    *		in the color space and luminance units requested.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetLastMeasurement(i1d3Handle devHndl, i1d3ColorSpace_t space, i1d3LumUnits_t	units, void *resultPtr);



    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3MeasureBacklightFrequency(i1d3Handle devHndl, unsigned short *freqHz)
    *		\brief Measures the display's backlight frequency
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param freqHz measured backlight frequency, 0 if the backlight frequency is stable or 1 if the backlight
    *              is too dark and its frequency cannot be measured.
    *		\see i1d3GetDeviceHandle()
    *       \see i1d3SetBacklightFreq()
    *       \see i1d3SetBacklightFreqSync()
    *
    *		\note The function measures the display's backlight frequency with an estimated drift of 1%. Please refer
    *             to additionally available application note on the new backlight frequency feature
    *
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3MeasureBacklightFrequency(i1d3Handle devHndl, unsigned short *freqHz);



    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3ReadDiffuserPosition(i1d3Handle devHndl, unsigned char *ucDiffPos)
    *		\brief Returns the position of the diffuser arm.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param ucDiffPos current position of diffuser: 0=OFF, 1=ON
    *		\see i1d3GetDeviceHandle()
    *
    *		This function returns the current position of the diffuser.
    *			0 = OFF
    *			1 = ON
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3ReadDiffuserPosition(i1d3Handle devHndl, unsigned char *ucDiffPos);

    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3SetLEDControl(i1d3Handle devHndl, i1d3LED_Control LEDconfig, double dOffTime, double dOnTime, unsigned char ucCount)
    *		\brief Sets the LED parameters.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param LEDconfig define type
    *		\param dOffTime off time in seconds
    *		\param dOnTime on time in seconds
    *		\param ucCount number of event repetitions
    *		\see i1d3GetDeviceHandle()
    *
    *		This function immediately sets the behaviour of the LEDs when the device is idle (i.e. not measuring).
    *		The LED functions are paused during measurements.
    *
    *		Available config states are Off, Flash and Pulse
    *		Valid Off Times are 0 - 11.15 seconds
    *		Valid On Times for Flash mode are 0 - 11.15 seconds
    *		Valid On Times for Pulse mode are 0 -
    *
    *		Resolution for Off Time and Flash Mode On Time - 0.043690667
    *		Resolution for Pulse Mode On Time - 0.699050667
    *
    *		Valid range for number of repetitions: 1 - 127 (128 - 255 repeats indefinitely)
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3SetLEDControl(i1d3Handle devHndl, i1d3LED_Control LEDconfig, double dOffTime, double dOnTime, unsigned char ucCount);


    /*****************************************************************************/
    /** 	\fn i1d3Status_t i1d3GetLEDControlSettings(i1d3Handle devHndl, i1d3LED_Control *LEDconfig, double *dOffTime, double *dOnTime, unsigned char *ucCount)
    *		\brief Returns the current LED parameters.
    *		\param devHndl handle to the device returned from i1d3GetDeviceHandle()
    *		\param *LEDconfig define type
    *		\param *dOffTime off time in seconds
    *		\param *dOnTime on time in seconds
    *		\param *ucCount number of event repetitions
    *		\see i1d3GetDeviceHandle()
    *
    *		This function returns the current LED settings.
    */
    /*****************************************************************************/
    PDEC i1d3Status_t i1d3GetLEDControlSettings(i1d3Handle devHndl, i1d3LED_Control *LEDconfig, double *dOffTime, double *dOnTime, unsigned char *ucCount);


    // end Measurement functions
    /*@}*/



    // end i1d3 SDK API functions
    /*@}*/




#ifdef __cplusplus
}
#endif

#endif //SDK_DATATYPES_ONLY

#endif //__I1D3_SDK_H__
