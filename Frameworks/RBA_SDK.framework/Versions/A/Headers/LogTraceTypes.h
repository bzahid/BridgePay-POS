#pragma once

/** \addtogroup sdk_c_api
 *  @{
 */
    
/**
    A pointer to a message callback function that the \libraryName calls to provide logging information to your application.
	
	\warning The library can call callback functions on a different thread from 
	the main application thread.
	
	\aboutLogging
	
    \param[in] logText - The message from the library that should be logged in the application.
	
	\sa RBA_SDK_SetDefaultLogLevel
    \sa RBA_SDK_SetLogCallBack
	\sa RBA_SDK_SetModuleLogLevel
	\sa RBA_SDK_SetTraceOutputFormatOption
 */
typedef void (*LOUT)(const char *logText);

/**
	The level of detail of information to be logged.
	
	\aboutLogging
	
	\sa RBA_SDK_SetDefaultLogLevel
	\sa RBA_SDK_SetModuleLogLevel
 */
typedef enum {
	//! No logging.
	LTL_NONE=-1, 
	//! Errors only.
	LTL_ERROR=0, 
	//! Errors and warnings.
	LTL_WARNING, 
	//! Errors, warnings, and general information.
	LTL_INFO, 
	//! Errors, warnings, general information, and trace information.
	LTL_TRACE, 
	//! Errors, warnings, general information, trace information, and debugging information.
	LTL_DEBUG} LOG_LEVEL;

/**
	Options to define what appears in the logging output.
	
	\aboutLogging
	
	\sa RBA_SDK_SetTraceOutputFormatOption
 */
typedef enum {
    //! Date is included	
    LOFO_ADD_DATE,
	//! Date is not included
    LOFO_NO_DATE,
	//! Module name is included	
    LOFO_ADD_MODULE_NAME,
	//! Module name is not included.
    LOFO_NO_MODULE_NAME,
	//! Severity of the information is not included.
    LOFO_NO_SEVERITY,
	//! Severity of the information is not included.
    LOFO_ADD_SEVERITY,
	//! ID for the instance is included.
    LOFO_ADD_INSTANCE_ID,
	//! ID for the instance is not included.
    LOFO_NO_INSTANCE_ID
} LOG_OUTPUT_FORMAT_OPTIONS;
/** @} */
