/**************************************************************************
 *  THIS IS AUTO-GENERATED FILE. DO NOT EDIT
 *  INSTEAD OF THIS EDIT rba_sdk.xml and run XML2RBA_SDK.pl
 **************************************************************************/
//! \addtogroup	sdk_c_api
//!@{

//GENERAL ERRORS
//!\def	RESULT_SUCCESS
//!\brief		Operation was successful
//!\details No errors occurred during the requested operation.
//!\def	RESULT_ERROR
//!\brief		A general error has occurred
//!\details Please review the log for further details on this error.
//!\def	RESULT_ERROR_NOT_AVAILABLE
//!\brief		Operation is not available at this time
//!\details Attempting to perform the requested operation resulted in an error.  This could be based on the state of the device or the SDK.  Please review the log for further details on this error.
//!\def	RESULT_ERROR_UNSUPPORTED
//!\brief		Operation is not supported
//!\details The requested operation is not supported by the SDK. Review the SDK documentation for a list of features tha are supported in your environment (platform, device, communication interface, or programming language).

//RBA SDK ERRORS
//!\def	RESULT_ERROR_NOT_INITIALIZED
//!\brief		SDK is not initialized
//!\details The SDK must be initialized before any other API's are called.

//COMMUNICATION ERRORS
//!\def	RESULT_ERROR_IO_COMMUNICATION
//!\brief		Error in communication I/O.
//!\details 
//!\def	RESULT_ERROR_TIMEOUT
//!\brief		Operation timed out
//!\details 
//!\def	RESULT_ERROR_NOT_PAIRED
//!\brief		Device is not paired
//!\details 
//!\def	RESULT_ERROR_NOT_CONNECTED
//!\brief		Device is not connected
//!\details 
//!\def	RESULT_ERROR_ALREADY_CONNECTED
//!\brief		Device is already connected
//!\details Try to disconnect first

//MESSAGE PROCESS ERRORS
//!\def	RESULT_ERROR_INVALID_RESPONSE
//!\brief		Response received is not valid
//!\details Please review the log for further details on this error.
//!\def	RESULT_ERROR_BUFFER_SIZE
//!\brief		Buffer size is too big
//!\details Unable to process message because the total buffer size is too big.  Please review the size of the parameters that have been set for this message.
//!\def	RESULT_ERROR_PARAMETER
//!\brief		Invalid message parameter
//!\details Please review the log for further details on this error.
//!\def	RESULT_ERROR_TERMINAL_LOCKED
//!\brief		Terminal is in a locked state
//!\details 
//!\def	RESULT_ERROR_PARAMETER_LEN
//!\brief		Invalid length of message parameter
//!\details The lenght of parameter is invalid

//SYSTEM ERRORS
//!\def	RESULT_ERROR_MEMORY
//!\brief		Memory error occurred
//!\details 
//!\def	RESULT_ERROR_FILE_OPERATION
//!\brief		File operation failed
//!\details 

//JVM ERRORS
//!\def	RESULT_ERROR_JVM
//!\brief		Java VM error
//!\details Operation resulted in an error that is related to the Java Virtual Machine.  Please review the log for further details on this error.
//! \cond PRIVATE

//Internal RBA_SDK Result
//!\def	RESULT_FORCE_UNSOLICITED_MSG
//!\brief		
//!\details 
//! \endcond
//!@}

//GENERAL ERRORS
#define RESULT_SUCCESS		0
#define RESULT_ERROR		-1
#define RESULT_ERROR_NOT_AVAILABLE		-2
#define RESULT_ERROR_UNSUPPORTED		-3

//RBA SDK ERRORS
#define RESULT_ERROR_NOT_INITIALIZED		-50

//COMMUNICATION ERRORS
#define RESULT_ERROR_IO_COMMUNICATION		-100
#define RESULT_ERROR_TIMEOUT		-101
#define RESULT_ERROR_NOT_PAIRED		-102
#define RESULT_ERROR_NOT_CONNECTED		-103
#define RESULT_ERROR_ALREADY_CONNECTED		-104

//MESSAGE PROCESS ERRORS
#define RESULT_ERROR_INVALID_RESPONSE		-150
#define RESULT_ERROR_BUFFER_SIZE		-151
#define RESULT_ERROR_PARAMETER		-152
#define RESULT_ERROR_TERMINAL_LOCKED		-153
#define RESULT_ERROR_PARAMETER_LEN		-154

//SYSTEM ERRORS
#define RESULT_ERROR_MEMORY		-200
#define RESULT_ERROR_FILE_OPERATION		-201

//JVM ERRORS
#define RESULT_ERROR_JVM		-250
//! \cond PRIVATE

//Internal RBA_SDK Result
#define RESULT_FORCE_UNSOLICITED_MSG		-1000
//! \endcond

