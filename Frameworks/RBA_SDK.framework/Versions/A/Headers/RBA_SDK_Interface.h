//!***************************************************************************************
//! 
//!
//!    Project: RBA SDK
//!
//!    Company: Ingenico
//!    
//!    Authors:  Gururajj narayanrao Kulkarni <gururajj.kulkarni@Indecomm.net>
//!              Anup Srikanth <Anup.Srikanth@Indecomm.net>
//!              Sergey Pjatkin <Sergejs.Pjatkins@Ingenico.com>
//!
//!    AppInterface.h Header file gives the application, an interface to the RBA SDK.
//!
//!******************************************************************************************

//! \todo Document the VID/PID values for the supported terminal types and update documentation for RBA_SDK_Initialize().

#pragma once

#include "CommSettings.h"
#include "LogTraceTypes.h"

#ifdef RBA_SDK_WIN32
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C"
{
#endif
        
    /** \addtogroup sdk_c_api
     *  @{
     */
        
    /**
		Gets the SDK version number of the \libraryName.
		
		\return A string that represents the library version number.
	 */
    DLLEXPORT const char*   RBA_SDK_GetVersion();

	/**
		Initializes the \libraryName.

		With the exception of the \ref RBA_SDK_SetDefaultLogLevel and \ref RBA_SDK_GetVersion functions, an application must call this function before it can call other functions in the library.

		\aboutInitializing

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa RBA_SDK_Connect
		\sa RBA_SDK_Shutdown
	 */
    DLLEXPORT int   RBA_SDK_Initialize();

    //! \cond INSTANCE_FUNCS
    //! ------------------------------------------------------------------------------------------
    //! Initializes the RBA SDK instance
    //!
    //!	This method initializes the RBA SDK instance.
    //!
    //!	\return     the Instance ID if successful, otherwise the error code defined in RBA_SDK_Errors.h
    //!				the Instance ID must be uses in RBA SDK functions where instance id required as input parameter.
    //!
    //! \remarks    This method must be called prior to using any other SDK API.
    //!
    //! \sa         RBA_SDK_Shutdown(); RBA_SDK_ShutdownInstance()
    //!
    //! \note		The \ref SETTINGS_COMMUNICATION used by your application must match the configuration
    //! 			of the device being used.  In other words, you cannot setup the RBA SDK to
    //!				communicate via Ethernet if the device is setup to use a serial connection.
    //!
    DLLEXPORT unsigned int RBA_SDK_InitializeInstance( const char* name );
    //! \endcond

    //! \cond INSTANCE_FUNCS
    //! ------------------------------------------------------------------------------------------
    //! Set the RBA SDK instance name
    //!
    //!	This method set/change the instance name.
    //!
    DLLEXPORT void RBA_SDK_SetInstanceName(unsigned int instanceId, const char* name );
    //! \endcond

    /**
		Prepares the the \libraryName to be unloaded by freeing all internal resources.

		This function frees all internal resources managed by the library, including message parameters, so that the application can unload the library from memory.

		\aboutInitializing

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa RBA_SDK_Disconnect
		\sa RBA_SDK_Initialize
	 */
    DLLEXPORT int   RBA_SDK_Shutdown( void );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_ShutdownInstance( unsigned int instanceId );
    //! \endcond

    /**
		Sets a parameter for a PIN pad request message.

		Use this function to provide the \libraryName with a value for each of the required parameters for a PIN pad message that is to be processed on the device. The library constructs a request messages for the device from the message ID and the associated parameter values.

		This function overwrites any previous value for the parameter. However, some parameters allow multiple values. To set multiple values on a parameter, use the \ref RBA_SDK_AddParam function.
		
		\aboutMessaging
		For information about specific messages and parameters, see the \baseGuide and the ref msgID.h file.

		\param[in]  id   The ID of parameter to set.
		\param[in]  data A pointer to a buffer that contains the value to which to set the parameter.
		\param[in]  len  The length of the source data in the buffer.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
RetValue = RBA_SDK_SetParam(P01_REQ_APPID, (char *) "0000", 4);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
[RBA_SDK SetParam:P01_REQ_APPID data:@"0000"];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
RBA_SDK_ERROR_ID ret = RBA_SDK_API.SetParam(RBA_SDK_PARAMETER_ID.P01_REQ_APPID, "0000");
		\endcode

		\sa RBA_SDK_AddParam
		\sa RBA_SDK_GetParam
		\sa RBA_SDK_ProcessMessage
		\sa RBA_SDK_ResetParam
	 */
    DLLEXPORT int   RBA_SDK_SetParam( int id, const char* data, int len );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SetParamFor( unsigned int instanceId, int id, const char* data, int len );
    //! \endcond

    /**
		Adds to or constructs an array of values for a parameter for a PIN pad request message.

		Call this function to build an array of values for a parameter to send to the connected device when your application calls the \ref RBA_SDK_ProcessMessage function.
		-# To set the first value, call the \ref RBA_SDK_SetParam function.
		-# Then call the \ref RBA_SDK_AddParam function to add subsequent values to the array.
		
		\note Any call to the \ref RBA_SDK_SetParam function overwrites any previous values that may have been set on the associated parameter.

		\warning When building an array of values for a specific \ref PARAMETER_ID, the order in which the application adds these values is significant.

		Only a few messages support a variable number of parameters.
		\aboutMessaging
		For more information about specific messages and parameters, see the \baseGuide.

		\param[in]  id   The ID of the value to add to the parameter value array.
		\param[in]  data A pointer to a buffer that contains the value to add to the parameter value array.
		\param[in]  len  The length of the source data in the buffer.
    
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
RetValue = RBA_SDK_SetParam(P13_REQ_AMOUNT, (char *) "100", 3);
RetValue = RBA_SDK_AddParam(P13_REQ_AMOUNT, (char *) "200", 3);
RetValue = RBA_SDK_AddParam(P13_REQ_AMOUNT, (char *) "3000", 4);
		\endcode

		\sa RBA_SDK_GetParam
		\sa RBA_SDK_ProcessMessage
		\sa RBA_SDK_SetParam
	 */
    DLLEXPORT int   RBA_SDK_AddParam( int id, const char* data, int len );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_AddParamFor( unsigned int instanceId, int id, const char* data, int len );
    //! \endcond

    /** 
	 *	Sends an RBA message to the device.
	 *
	 *	An application calls this function to send an RBA message to the device.  All
	 *	the low-level details related to the connection, protocol, and message 
	 *	acknowledgements are handled by the \libraryName.
	 *
	 *	\aboutMessaging
	 *
	 *	\note If the device responds immediately (synchronous mode has been set and the
	 *		message is blocking), then this method handles the response 
	 *		message from the device.
	 * 		If the device does not respond immediately (asynchronous mode has been set or the
	 *		message is non-blocking or callback only), then the message callback is called when the response is
	 *		ready. Use \ref RBA_SDK_SetMessageCallBack to set the message callback.
	 *
	 *	\param[in]  CommandID Unique Message ID defined in msgID.h to be processed
	 *
	 *	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.
	 *
	 * \sa RBA_SDK_SetParam
	 * \sa RBA_SDK_GetParam
	 * \sa RBA_SDK_SetProcessMessageSyncMode
	 * \sa RBA_SDK_SetProcessMessageAsyncMode
	 * \sa RBA_SDK_SetMessageCallBack        
	 */
    DLLEXPORT int   RBA_SDK_ProcessMessage( int CommandID );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_ProcessMessageFor( unsigned int instanceId, int CommandID );
    //! \endcond

    /** 
		Places the \libraryName in the asynchronous message processing mode.
		
		\note In asynchronous mode, all messages as asynchronous. When the message finishes processing, a call is made to a callback method, which is set using the \ref RBA_SDK_SetMessageCallBack function.
		
		\warning Using synchronous mode (see \ref RBA_SDK_SetProcessMessageSyncMode) is recommended over asynchronous mode. However, depending on the message ID, synchronous mode may result in blocking (synchronous) messages or non-blocking (asynchronous) messages.
		
		\aboutMessaging
	 
	 	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.
	 
	 	\sa         RBA_SDK_ProcessMessage
	 	\sa         RBA_SDK_SetProcessMessageSyncMode
		\sa			RBA_SDK_SetMessageCallBack
     */
    DLLEXPORT int   RBA_SDK_SetProcessMessageAsyncMode();
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SetProcessMessageAsyncModeFor( unsigned int instanceId );
    //! \endcond

    /** 
		Places the \libraryName in the synchronous message processing mode.
		
		\note Depending on the message ID, synchronous mode may result in blocking (synchronous) messages or non-blocking (asynchronous) messages.
		
		\note For non-blocking messages, when the message finishes processing, the library calls the application's \ref PinPadMessageCallBack callback function, which the application can set using the \ref RBA_SDK_SetMessageCallBack function.
		
		\aboutMessaging
		
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa PinPadMessageCallBack
		\sa RBA_SDK_ProcessMessage
		\sa RBA_SDK_SetProcessMessageAsyncMode
	 */
    DLLEXPORT int   RBA_SDK_SetProcessMessageSyncMode();
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SetProcessMessageSyncModeFor(unsigned int instanceId);
    //! \endcond

    /**
		Gets a parameter from a message that the \libraryName received from a PIN pad device.
		
		Use this function to retrieve the values for parameters for a PIN pad message that was sent from the device to the library. The library parses each message it receives from the device to extract the parameter values. To get the length of the data contained in a parameter, use the \ref RBA_SDK_GetParamLen function. To notify the library that it can free the memory for its copy of the parameter data, use the \ref RBA_SDK_ResetParam function.
		
		To send a message to the device, see the \ref RBA_SDK_ProcessMessage function. To register a callback function to receive messages from the device, see the \ref RBA_SDK_SetMessageCallBack function.
		
		\aboutMessaging

		\param[in]     id   The ID of the parameter value to get.
		\param[out]    data A pointer to the buffer to which the library can copy the parameter value.
		\param[in,out] len  When calling, set this to the size of the buffer, in bytes. When the function returns, this contains the length of the copied parameter data.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
char resonCode[P00_RES_REASON_CODE_SIZE+1];
memset(resonCode,0,sizeof(resonCode));
int len = sizeof(resonCode);
RBA_SDK_GetParam(P00_RES_REASON_CODE,resonCode,&len);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
NSString* data = [RBA_SDK GetParam:P00_RES_REASON_CODE];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
String data = RBA_SDK_API.GetParam(RBA_SDK_PARAMETER_ID.P00_RES_REASON_CODE);
		\endcode

		\sa RBA_SDK_GetParamLen
		\sa RBA_SDK_ProcessMessage
		\sa RBA_SDK_ResetParam
		\sa RBA_SDK_SetMessageCallBack
		\sa RBA_SDK_SetParam

		\todo We should consider having GetParam() return the value and automatically overwrite the value so it cannot be retrieved again by the application. This approach significantly reduces the possibility of an application leaving card holder data in memory for a longer period than necessary.
     */
    DLLEXPORT int   RBA_SDK_GetParam( int id, char* data, int* len );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetParamFor(unsigned int instanceId, int id, char* data, int* len );
    //! \endcond

    /**
		Returns the size in bytes required to store the current value of a specific parameter.
		
		\aboutMessaging

		\param[in] id	The ID of the parameter.
		\return			The size in bytes required to store the current value of the parameter, or one of the error codes defined in the \ref RBA_SDK_Errors.h file.
		
		\sa RBA_SDK_GetParam
     */
    DLLEXPORT int   RBA_SDK_GetParamLen(int id);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetParamLenFor(unsigned int instanceId, int id);
    //! \endcond

    /**
		Clears a parameter value stored by the \libraryName.

		This function notifies the library that it should clear and free the memory for its copy of the parameter data. This function can free memory for parameters that were set either by the application or by the library when it received a message from the device.
		
		\note Some parameters hold sensitive card holder information. An application should call this function as soon as the data is no longer needed.
		
		\aboutMessaging

		\param[in] id	The ID of the parameter, or -1, to clear library memory for all parameters.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa RBA_SDK_SetParam
		\sa RBA_SDK_GetParam
     */
    DLLEXPORT int   RBA_SDK_ResetParam( int id );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_ResetParamFor(unsigned int instanceId,  int id );
    //! \endcond

    /** 
	 *  Sets the communication timeout values used during communication with a device.
	 *  
	 *  Applications 
	 *  are expected to set proper values for the communication interface (see \ref InterfacesId.h) they are using.
	 *  If the value for a timeout interval is 0, then then the \libraryName will set the default  
	 *  value for this interval. If value is invalid, then the \libraryName
	 *  will set the minimum interval for the interface. 
	 *  
	 *  \note For all interfaces, the 
	 *  	\ref SETTINGS_COMM_TIMEOUTS.ReceiveTimeout value refers to the time it takes to receive each character, 
	 *  	not the time it takes to receive a full packet.
	 *  
	 *  \aboutConnecting
	 *  
	 *  \param[in]	timeoutsMSec The timeout values to be used during device communication.
	 *  
	 *  \returns	\ref RESULT_SUCCESS if successful, otherwise, and error code defined in RBA_SDK_Errors.h
	 */ 
    DLLEXPORT int   RBA_SDK_SetCommTimeouts(SETTINGS_COMM_TIMEOUTS timeoutsMSec);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SetCommTimeoutsFor(unsigned int instanceId, SETTINGS_COMM_TIMEOUTS timeoutsMSec);
    //! \endcond

    /**
		Initiates a connection to a device.

		\note The library must be properly initialized using the \ref RBA_SDK_Initialize function before calling this function.
		
		\note The communication settings used by your application must match the configuration of the device being used. In other words, you cannot configure the RBA SDK to communicate via Ethernet if the device is configured to use a serial connection.
		
		After the library establishes a connection and end to end and communication is possible, the library calls the application's connected callback function. For more information, see the \ref RBA_SDK_SetNotifyRbaConnected function and the \ref RbaConnectedCallBack type definition.

		\aboutConnecting

		\param[in] settings The communication settings for the connection.
		
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		Here are some examples of how to configure the library for some of the common communication interfaces.

		<b>C Ethernet Example:</b>
		\code {.cpp}
// Initializing for an Ethernet connection
comm_settings settings = {0};
char ipAddress[] = "192.168.0.1";
char port[] = "12000";

// Set the mode to the Ethernet interface
settings.mode = ETHERNET_INTERFACE;

// Setup the IP address and port to use
strncpy(settings.ip_config.IPAddress, ipAddress,sizeof(ipAddress));
strcpy(settings.ip_config.Port, port);

if (RBA_SDK_Connect(settings) == RESULT_SUCCESS) {
	// success
    // *** START SENDING RBA MESSAGES ***
}
else {
	// failure
}
		\endcode

		<b>C USB HID Example:</b>
		\code {.cpp}
// Initializing for a USB HID connection
comm_settings settings = {0};

settings.mode = USB_HID_INTERFACE;
settings.usbhid_config.autoDetect = AutoDetectON;

// Set the VID & PID for the terminal you are using
settings.usbhid_config.vendor_id = 0x0b00;
settings.usbhid_config.product_id = 0x0074;

if (RBA_SDK_Connect(settings) == RESULT_SUCCESS) {
	// success
    // *** START SENDING RBA MESSAGES ***
}
else {
	// failure
}
		\endcode

		<b>C Serial Example:</b>
		\code {.cpp}
// Initializing for a serial connection
comm_settings settings = {0};

settings.mode = SERIAL_INTERFACE;
strcpy((char*)settings.rs232_config.ComPort, "/dev/ttyACM0");
settings.rs232_config.AutoDetect = AutoDetectOFF;
settings.rs232_config.BaudRate = BaudRate_115200;
settings.rs232_config.DataBits = DataBits8;
settings.rs232_config.Parity = ParityNone;
settings.rs232_config.StopBits = StopBits1;
settings.rs232_config.FlowControl = FlowCtrl_None;

if (RBA_SDK_Connect(settings) == RESULT_SUCCESS) {
	// success
    // *** START SENDING RBA MESSAGES ***
}
else {
	// failure
}
		\endcode

		\sa RBA_SDK_Disconnect
		\sa RBA_SDK_GetConnectionStatus
		\sa RBA_SDK_Initialize
		\sa RBA_SDK_SetCommTimeouts
		\sa RBA_SDK_SetNotifyRbaConnected
	 */
    DLLEXPORT int   RBA_SDK_Connect(SETTINGS_COMMUNICATION  settings);
	
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_ConnectFor(unsigned int instanceId, SETTINGS_COMMUNICATION  settings);
    //! \endcond

	/**
		Reconnects to a device, using the previous communication settings.

		You can call this function to reestablish a connection with a device after the \ref RBA_SDK_Connect and \ref RBA_SDK_Disconnect functions were called.
		- If the application calls this function without previously calling the \ref RBA_SDK_Connect function, then this function tries to connect using the default settings, which are defined by the \ref SETTINGS_COMMUNICATION structure with all values set to binary zero.
		- If the device is already connected, then this function returns an \ref RESULT_ERROR_ALREADY_CONNECTED error.

		To conserve power if your application is running on a mobile or battery powered device, you can call the \ref RBA_SDK_Disconnect function between transactions or after a period of inactivity, and then call the RBA_SDK_Reconnect function before sending the next request.
		
		\aboutConnecting
		
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the \ref RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
// Initialize the connection for a USB HID device.
comm_settings settings = {0};
settings.mode = USB_HID_INTERFACE;
settings.usbhid_config.autoDetect = AutoDetectON;
if (RBA_SDK_Connect(settings) == RESULT_SUCCESS) {
    // successful
    // *** START SENDING RBA MESSAGES ***
}

RBA_SDK_Disconnect();

// Resstablish the connection using the previous settings (USB_HID_INTERFACE).
if (RBA_SDK_Reconnect() == RESULT_SUCCESS) {
    // successful
    // *** START SENDING RBA MESSAGES ***
}
else {
    // failure
}
		\endcode

		\sa RBA_SDK_Connect
		\sa RBA_SDK_Disconnect
		\sa RBA_SDK_Initialize
		\sa RBA_SDK_SetCommTimeouts
	 */
    DLLEXPORT int   RBA_SDK_Reconnect(void);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_ReconnectFor(unsigned int instanceId);
    //! \endcond
    
    /**
		A pointer to a callback function that the \libraryName calls once it has finished connecting to a device.
		
		After the library establishes a connection and end-to-end communication is possible, the library calls the application's connected callback function.
		
		The device is not ready for communication until the library calls the connected callback function or the library returns the \ref CONNECTED value from the \ref RBA_SDK_GetConnectionStatus function.
		
		\aboutConnecting
		
		\sa RBA_SDK_Connect
		\sa RBA_SDK_GetConnectionStatus
		\sa RBA_SDK_SetNotifyRbaConnected
     */
    typedef void (*RbaConnectedCallBack)();
    //! \cond INSTANCE_FUNCS
    typedef void (*RbaConnectedCallBackWithInstanceId)(unsigned int, void* userData);
    //! \endcond


	/** 
		Sets the function that the \libraryName calls when the library establishes a connection and end-to-end communication is possible with a PIN pad device.
		
		The device is not ready for communication until the library calls the connected callback function or the library returns the \ref CONNECTED value from the \ref RBA_SDK_GetConnectionStatus function.

		\cppThreadWarning
		
		Some versions of the library do not support the connected callback feature. If the version you are using does not support this feature, then the library returns the \ref RESULT_ERROR_UNSUPPORTED error code.
		
		\aboutConnecting

		\param[in] cbRbaIsReadyListener A pointer to the application's connected callback function.
		
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa RbaConnectedCallBack
		\sa RBA_SDK_Connect
		\sa RBA_SDK_GetConnectionStatus
	 */ 
    DLLEXPORT int RBA_SDK_SetNotifyRbaConnected(RbaConnectedCallBack cbRbaIsReadyListener);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int RBA_SDK_SetNotifyRbaConnectedFor(unsigned int instanceId, RbaConnectedCallBackWithInstanceId cbRbaIsReadyListener, void* userData);
    //! \endcond

	
	/**
		A pointer to a callback function that the \libraryName calls once it has discovered that the connection status changed from \ref CONNECTED to \ref  DISCONNECTED.
		
		\ref RBA_SDK_GetConnectionStatus function.
		
		\aboutConnecting
		
		\sa RBA_SDK_Connect
		\sa RBA_SDK_GetConnectionStatus
		\sa RBA_SDK_SetNotifyRbaDisconnected
     */
    typedef void (*RbaDisconnectedCallBack)();
    //! \cond INSTANCE_FUNCS
    typedef void (*RbaDisconnectedCallBackWithInstanceId)(unsigned int, void* userData);
    //! \endcond
	
		/** 
		Sets the function that the \libraryName calls when the library discovered that connection status changed to \ref DISCONNECTED and end-to-end communication is not possible with a PIN pad device.
		
		\aboutConnecting

		\param[in] cbRbaDisconnectedListener A pointer to the application's disconnected callback function.
		
		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		\sa RbaDisconnectedCallBack
		\sa RBA_SDK_GetConnectionStatus
	 */ 
	DLLEXPORT int RBA_SDK_SetNotifyRbaDisconnected(RbaDisconnectedCallBack cbRbaDisconnectedListener);
    //! \cond INSTANCE_FUNCS 
	DLLEXPORT int RBA_SDK_SetNotifyRbaDisconnectedFor(unsigned int instanceId, RbaDisconnectedCallBackWithInstanceId cbRbaDisconnectedListener, void* userData);
    //! \endcond
	
	
    /** 
	 *  Returns the connection status.
	 *
	 *	\aboutConnecting
	 *  
	 *  \return     The current state of the device connection (see \ref CONNECTION_STATUS).
	 *  
	 *  \sa         RBA_SDK_Connect(), RBA_SDK_Disconnect()
	 */
    DLLEXPORT int   RBA_SDK_GetConnectionStatus(void);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetConnectionStatusFor(unsigned int instanceId);
    //! \endcond

    /**
	 *  Closes the connection to the device.
	 *
	 * \aboutConnecting
	 *  
	 *  \return     \ref RESULT_SUCCESS if successful, otherwise, and error code defined in RBA_SDK_Errors.h
	 *  
	 *  \sa         RBA_SDK_Connect(), RBA_SDK_GetConnectionStatus()
	 */
    DLLEXPORT int   RBA_SDK_Disconnect(void);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_DisconnectFor(unsigned int instanceId);
    //! \endcond

    /** 
	 *  Sends a custom message of a type which is supported on the RBA (terminal), but not
	 *  yet supported by the \libraryName.
	 * 
	 *  If bWaitResponse is true, the message response will be handled as blocking (synchronous),
	 *  and the function will wait for the device to respond before returning. If bWaitResponse is false, the message
	 *  response will be handled as non-blocking (asynchronous), and the message response will be
	 *  returned in the message callback with a message ID of RAW_PINPAD_RESPONSE. The custom message
	 *  that is received can be read by using \ref RBA_SDK_GetParam with parameter ID of 
	 *  RAW_PINPAD_RESPONSE_DATA. 
	 *  
	 *  It is also possible to use <b>RBA_SDK_SendCustomMessage</b> to send a request for a supported message
	 *  ID to be received. In this case, the \libraryName will recognize the  response as a supported message.
     *  You can then use \ref RBA_SDK_GetParam to retrieve the parameters using the supported parameter IDs or RAW_PINPAD_RESPONSE_DATA.
	 *  
	 *	\aboutMessaging
	 *
	 *  \param[in]  RawData    The data to be sent to the terminal.
	 *  \param[in]  DataLength The number of characters to be sent.
	 *  \param[in]  bWaitResponse   <b>true</b> if the message response is handled as blocking;
	 *  		<b>false</b> if the message response is handled as non-blocking.
	 *  
	 *  \return     \ref RESULT_SUCCESS if successful; otherwise, and error code defined in RBA_SDK_Errors.h
	 *  
	 *  \sa RBA_SDK_SetProcessMessageSyncMode
     */
    DLLEXPORT int   RBA_SDK_SendCustomMessage( const char* RawData, int DataLength, bool bWaitResponse );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SendCustomMessageFor( unsigned int instanceId, const char* RawData, int DataLength, bool bWaitResponse );
    //! \endcond
    
    //! \cond INSTANCE_FUNCS
    //DLLEXPORT int   RBA_SDK_ParseRawResponse(char* rawData, int dataLength);
    //DLLEXPORT int   RBA_SDK_ParseRawResponseFor(unsigned int instanceId, char* rawData, int dataLength);
    //! \endcond
    
    /** @} */

    /** \addtogroup sdk_c_api
     *  @{
     */
    
    /**
        A pointer to a message callback function that supports asynchronous message handling.
		
        The \libraryName calls the application's message callback function to notify your application asynchronously that the library has processed
        a message from the PIN pad device and that any associated response parameters are available.
		
		\cppThreadWarning
		
        To retrieve information for a parameter associated with a specific message response, use the \ref RBA_SDK_GetParam function.
		
		\aboutMessaging
		
        \param[in] MessageId The ID of the message that the library processed.
		
	    \sa MESSAGE_ID
	    \sa RBA_SDK_GetParam
		\sa RBA_SDK_SetMessageCallBack
	 */
    typedef void (*PinPadMessageCallBack)(int);
    //! \cond INSTANCE_FUNCS
    typedef void (*PinPadMessageCallBackWithInstanceId)(unsigned int, int, void* userParam);
    //! \endcond

    /**
        Sets the function that the \libraryName calls to notify your application asynchronously that the library has processed a PIN pad device message.
		
        \cppThreadWarning

        After the library receives and parses a device message for which it will notify you application asynchronously, it calls the application's message callback function.
		
        To retrieve the response parameters associated with a device message, call the \ref RBA_SDK_GetParam function from within the application's message callback function.
		
		\aboutMessaging

		\param[in] cbMessageHandler A pointer to the application's PIN pad message callback function.
		
		\return \ref RESULT_SUCCESS if event driven message callbacks are enabled for the device; otherwise, \ref RESULT_ERROR_UNSUPPORTED.

		<b>C Example:</b>
		\code {.cpp}
{
    //...
    RetValue = RBA_SDK_SetMessageCallBack(PinPadMessageCallback);
    if(RetValue < RESULT_SUCCESS)
    {
        printf ("SetMessageCallBack Failed Error code =%d\n", RetValue);
    }
    //...
}

void PinPadMessageCallback(int msgId)
{
    switch(msgId)
    {
        case M00_OFFLINE:
        {
            char resonCode[P00_RES_REASON_CODE_SIZE+1];
            memset(resonCode,0,sizeof(resonCode));
            int len = sizeof(resonCode);
            RBA_SDK_GetParam(P00_RES_REASON_CODE,resonCode,&len);
            printf("   P00_RES_REASON_CODE=%s\n",resonCode);
            break;
        }
        case M50_AUTHORIZATION:
            break;
    }
}
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
@interface MyViewController : UIViewController <RBA_SDK_Event_support, LogTrace_support>
{
}

@implementation MyViewController
- (void)viewDidLoad
{
	[RBA_SDK SetDelegate:self];
}
-(void) ProcessPinPadParameters:(NSInteger) messageId
{
	switch([messageId intValue])
	{
		case M00_OFFLINE:
			NSLog(@"P00_RES_REASON_CODE=%@",[RBA_SDK GetParam:P00_RES_REASON_CODE]);
			break;
		default:
			break;
	}
}
@end
		\endcode

		\sa RBA_SDK_GetParam
		\sa RBA_SDK_ProcessMessage
		\sa RBA_SDK_SetProcessMessageAsyncMode
		\sa RBA_SDK_SetProcessMessageSyncMode
     */
    DLLEXPORT int   RBA_SDK_SetMessageCallBack(PinPadMessageCallBack cbMessageHandler);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_SetMessageCallBackWithInstanceId(unsigned int instanceId, PinPadMessageCallBackWithInstanceId cbMessageHandler, void* userParam);
    //! \endcond

    /**
		A function type definition for the battery level callback function.

		This callback is issued when the \libraryName wishes to notify the 
        terminal of the battery condition.
    
		Battery threshold is set by the \ref RBA_SDK_SetBatteryNotifyThreshold function.
	
	     \cppThreadWarning
	
         \param[out]  int                     Battery level as a percentage of full charge (0-100%)
         \param[out]  BATTERY_STATE           Indicates the battery is either charging or discharging.
         \param[out]  BATTERY_LEVEL_STATE     Indicates the battery is either above or below the threshold. 
    */
    typedef void (*BatteryLevelCallBack)(int, BATTERY_STATE, BATTERY_LEVEL_STATE);
    //! \cond INSTANCE_FUNCS
    typedef void (*BatteryLevelCallBackWithInstanceId)(unsigned int, int, BATTERY_STATE, BATTERY_LEVEL_STATE);
    //! \endcond

    // TODO: Move this into the Objective-C section
    // <b>Objective-C Example:</b>
    // \code
    //
    //     @interface MyViewController : UIViewController <RBA_SDK_Event_support, LogTrace_support>
    //     {
    //     }
    //
    //     @implementation MyViewController
    //     - (void)viewDidLoad
    //     {
    //         [[NSNotificationCenter defaultCenter] addObserver:self.viewController
    //                                                  selector:@selector(batteryLevel:)
    //                                                      name:kRBA_SDK_BatteryLevel
    //                                                    object:nil];
    //
    //         if( [RBA_SDK RBA_SDK_Initialize] == RESULT_SUCCESS ) {
    //             [RBA_SDK SetAttribute:BATTERY_TIMER_INTERVAL_MINUTES data:@"20"]; // default 5 min
    //             [RBA_SDK SetBatteryNotifyThreshold:10];
    //         }
    //     }
    //
    //     /* -----------------  Battery Level ------------------------------------------ */
    //     // here application received notification with full information
    //     // battery level     - 1-100%
    //     // battery status    - BS_CHARGING, BS_DISCHARGING
    //     // battery threshold - BL_LEVEL_IS_BELOW_THRESHOD, BL_LEVEL_IS_ABOVE_THRESHOLD
    //     - (void)batteryLevel:(NSNotification *)notification
    //     {
    //        // receive the notification with the barcode data
    //        NSDictionary *batteryData = [notification userInfo];
    //        if (batteryData && batteryData[@"level"] && batteryData[@"state"] && batteryData[@"levelState"])
    //        {
    //            int level = [batteryData[@"level"] intValue];
    //            BATTERY_STATE state = (BATTERY_STATE)[batteryData[@"state"] intValue];
    //            BATTERY_LEVEL_STATE levelState = (BATTERY_LEVEL_STATE)[batteryData[@"levelState"] intValue];
    //            NSLog(@"Battery level=%d",level);
    //            switch( state )
    //            {
    //                case BS_NA:          NSLog(@"Battery state=NotApplicable"); break;
    //                case BS_CHARGING:    NSLog(@"Battery state=Charging");      break;
    //                case BS_DISCHARGING: NSLog(@"Battery state=Discharging");   break;
    //            }
    //            switch( levelState )
    //            {
    //                case BL_NA:                      break;
    //                case BL_LEVEL_IS_BELOW_THRESHOD:  NSLog(@"Battery level is below threshold");      break;
    //                case BL_LEVEL_IS_ABOVE_THRESHOLD: NSLog(@"Battery level is above threshold");      break;
    //            }
    //        }
    //     }
    //
    //     @end
    //
    // \endcode
    //
    //
	// TODO: Add C/C++ example
	
    /** 
	 *	Sets the battery level threshold and subscribes to an event callback that is called 
	 *		from the \libraryName when the threshold is crossed.
	 *		
	 *	The library calls the \a cbBatteryListener callback when the battery level crosses the
	 *		threshold, either below or above.
	 *	
	 *	\cppThreadWarning
	 *			
	 *	\param[in]  threshold               Battery threshold as the percent of total battery capacity.
	 *  \param[in]  cbBatteryListener 		Pointer to callback function that is called when the 
	 *                         threshold is crossed.
	 *
	 *	\return     \ref RESULT_SUCCESS if callback is enabled, otherwise \ref RESULT_ERROR_UNSUPPORTED.
	 *
	 *  \sa BatteryLevelCallBack
	 */
	DLLEXPORT int RBA_SDK_SetBatteryNotifyThreshold(int threshold, BatteryLevelCallBack cbBatteryListener);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int RBA_SDK_SetBatteryNotifyThresholdFor(unsigned int instanceId, int threshold, BatteryLevelCallBackWithInstanceId cbBAtteryListener);
    //! \endcond


    /** @} */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    /** \addtogroup sdk_c_api
     *  @{
     */

    /**
		Sets an attribute of the \libraryName.
		
		Use this function to configure an attribute of the library. The attribute IDs are defined in the \ref RBA_SDK_ATTRIBUTE_ID enumeration.
		
		\note For numeric values, the value must be a positive integer, represented as a decimal string.

		\param[in] id The ID of the attribute to set.
		\param[in] value A pointer to a buffer that contains the value to which to set the attribute. 
		\param[in] len The length of the source data in the buffer.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
char *interval = "5";
int ret = RBA_SDK_SetAttribute(
    BATTERY_TIMER_INTERVAL_MINUTES, interval, strlen(interval));
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
[RBA_SDK RBA_SDK_SetAttribute:BATTERY_TIMER_INTERVAL_MINUTES data:@"5"];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
RBA_SDK_ERROR_ID ret = RBA_SDK_API.RBA_SDK_SetAttribute(
	RBA_SDK_ATTRIBUTE_ID.BATTERY_TIMER_INTERVAL_MINUTES, "5");
		\endcode

		\sa         RBA_SDK_GetAttribute()
     */
    DLLEXPORT int RBA_SDK_SetAttribute(int id, const char* value, int len);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int RBA_SDK_SetAttributeFor(unsigned int instanceId, int id, const char* value, int len );
    //! \endcond

    /**
		Gets an attribute of the \libraryName.
		
		Use this function to retrieve the current value of an attribute of the library. The attribute IDs are defined in the \ref RBA_SDK_ATTRIBUTE_ID enumeration.
		
		\note For numeric values, the value is a positive integer, represented as a decimal string.

		\param[in] id The ID of the attribute to get.
		\param[in] data A pointer to the buffer to which the library can copy the attribute value. 
		\param[in] len 	When calling, set this to the size of the buffer, in bytes. When the function returns, this contains the length of the copied attribute data.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
int len = RBA_SDK_GetLibAttributeLen(BATTERY_TIMER_INTERVAL_MINUTES);
char interval[len+1];
memset(interval,0,len+1);
RBA_SDK_GetLibAttribute(BATTERY_TIMER_INTERVAL_MINUTES,interval,&len);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
NSString* interval = [RBA_SDK GetAttribute:BATTERY_TIMER_INTERVAL_MINUTES];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
String interval = RBA_SDK_API.GetAttribute(
	RBA_SDK_ATTRIBUTE_ID.BATTERY_TIMER_INTERVAL_MINUTES);
		\endcode

		\sa RBA_SDK_GetAttributeLen
		\sa RBA_SDK_SetAttribute
     */
    DLLEXPORT int   RBA_SDK_GetAttribute( int id, char* data, int* len );
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetAttributeFor(unsigned int instanceId, int id, char * data, int *len );
    //! \endcond

    /**
		Returns the size in bytes required to store the current value of a specific \libraryName attribute. 

		\param[in] id The ID of the attribute.
		
		\return The size in bytes required to store the current value of the attribute, or one of the error codes defined in the \ref RBA_SDK_Errors.h file.

		\sa RBA_SDK_GetAttribute
     */
    DLLEXPORT int   RBA_SDK_GetAttributeLen(int id);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetAttributeLenFor(unsigned int instanceId, int id);
    //! \endcond

    /** @} */

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C"
{
#endif

    /** \addtogroup sdk_c_api
     *  @{
     */

    /**
		Adds to or constructs an array of values for the EMV tag data for an applicable PIN pad request message.
		
		Use the \ref RBA_SDK_ResetTagParam function to clear previous EMV tag data. Use this function to set the first and each additional tag parameter for an EMV message.
		
		\aboutMessaging

		\param[in]  msg     The ID of the message for which to include the tag parameter.
		\param[in]  tagId   The ID of the EMV tag parameter.
		\param[in]  data    A pointer to a buffer that contains the value for the EMV tag parameter.
		\param[in]  len     The length of the value data in the buffer.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
unsigned int tagId = 0x9f03;
RBA_SDK_AddTagParam(M33_00_EMV_TRANSACTION_INITIATION, tagId, (unsigned char*)"9f03-data", 9);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
[RBA_SDK AddTagParam:M33_04_EMV_AUTHORIZATION_RESPONSE tagid:0x1000 string:@"0x1000"];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
uint tagId = 0x1000;
bool emv_tag = true;
string tagData = "Text for tag:" + tagId;
RBA_SDK_API.AddTagParam(
	RBA_SDK_MSG_ID.M33_03_EMV_AUTHORIZATION_REQUEST, tagId, tagData);
		\endcode
		
		\sa RBA_SDK_GetTagParam
		\sa RBA_SDK_ResetTagParam
	 */
    DLLEXPORT int RBA_SDK_AddTagParam(int msg, int tagId, const unsigned char* data, int len);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int RBA_SDK_AddTagParamFor(unsigned int instanceId, int msg, int tagId, const unsigned char* data, int len);
    //! \endcond


    /**
		Gets the next tag parameter associated with an EMV message that the \libraryName received from a PIN pad device.

		Use this function to retrieve values for tag parameters that were provided by the device in an EMV response message. Messages can contain multiple tag parameters. Call this function multiple times to retrieve all of the tag parameters for the message.
		
		To get the length of the data contained in a tag parameter, use the \ref RBA_SDK_GetTagParamLen function. To notify the library that it can free the memory for its copy of the tag parameter data, use the \ref RBA_SDK_ResetTagParam function.
		
		Data for an individual tag can only be retrieved once, as  after providing the tag parameter value to the calling application, the library clears and frees the associated memory.
		
		\aboutMessaging

		\param[in] msg The ID of the EMV message.
		\param[out] data A pointer the buffer to which the library can copy the tag parameter value.
		\param[in,out] len When calling, set this to the size of the buffer, in bytes. When the function returns, this contains the length of the copied tag parameter data

		\return If successful, the ID of the EMV tag parameter; otherwise, one of the error codes defined in the \ref RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code {.cpp}
int len = RBA_SDK_GetTagParamLen(M33_05_EMV_AUTHORIZATION_CONFIRMATION);
if( len <= 0 )
	return RESULT_ERROR_PARAMETER;
char pData[len+1];
memset(pData,0,len+1);

unsigned int tagId = RBA_SDK_GetTagParam(M33_05_EMV_AUTHORIZATION_CONFIRMATION, (unsigned char*)pData, &len);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
NSData* data = nil;
while(true) {
	if( [RBA_SDK GetTagParamLen:M33_05_EMV_AUTHORIZATION_CONFIRMATION] <= 0 )
		break;
	unsigned int tagId = [RBA_SDK GetTagParam:M33_05_EMV_AUTHORIZATION_CONFIRMATION tagData:&data];
	NSString* strData = [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
}
		\endcode

		<b>C# Example:</b>
		\code {.cs}
string str = "";
uint tagId = RBA_SDK_API.GetTagParam(RBA_SDK_MSG_ID.M33_03_EMV_AUTHORIZATION_REQUEST, ref str);

byte[] bytes = new byte[1];
tagId = RBA_SDK_API.GetTagParam(RBA_SDK_MSG_ID.M33_03_EMV_AUTHORIZATION_REQUEST, ref bytes);
		\endcode

		\sa RBA_SDK_ResetTagParam
		\sa RBA_SDK_GetTagParamLen
	 */
    DLLEXPORT unsigned int RBA_SDK_GetTagParam(int msg, unsigned char* data, int*len);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT unsigned int RBA_SDK_GetTagParamFor(unsigned int instanceId, int msg, unsigned char* data, int*len);
    //! \endcond


    /**
		Returns the size in bytes required to store the next available value of an EMV tag parameter from the \libraryName.

		EMV messages can contain multiple tag parameters. To get the size of each EMV tag parameter, call this function each time before you call the \ref RBA_SDK_GetTagParam function.
		
		\note If the application has retrieved all of the available EMV tag parameters for the message, then a call to this function returns the \ref RESULT_ERROR_PARAMETER value.

		\param[in] msg The ID of the EMV message.

		\return The size in bytes required to store the current value of the tag parameter, or one of the error codes defined in the \ref RBA_SDK_Errors.h file.

		<b>C Example:</b>
		\code
int len = RBA_SDK_GetTagParamLen(M33_05_EMV_AUTHORIZATION_CONFIRMATION);
if( len <= 0 )
{
	return RESULT_ERROR_PARAMETER;
}
		\endcode

		<b>Objective-C Example:</b>
		\code
if( [RBA_SDK GetTagParamLen:M33_05_EMV_AUTHORIZATION_CONFIRMATION] <= 0 )
{
	return RESULT_ERROR_PARAMETER;
}
		\endcode

		\sa     RBA_SDK_GetTagParam
	 */
    DLLEXPORT int   RBA_SDK_GetTagParamLen(int msg);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int   RBA_SDK_GetTagParamLenFor(unsigned int instanceId, int msg);
    //! \endcond

    /**
		Clears memory for an EMV tag parameter stored by the \libraryName for an EMV message.

		This function notifies the library that it should clear and free the memory for its copy of the tag parameter data. This function can free memory for parameters that were set either by the application or by the library when it received a message from the device.
		
		\aboutMessaging

		\param[in] msg The ID of the message that contains the tag parameters, or -1 to clear all tag data for all messages.
		\param[in] tagId The ID of the tag parameter to clear, or -1 to clear all tag parameter data for the message.

		\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

		Here are some code examples of how to use this function:

		<b>C Example:</b>
		\code {.cpp}
RBA_SDK_ResetTagParam(M33_05_EMV_AUTHORIZATION_CONFIRMATION, -1);
		\endcode

		<b>Objective-C Example:</b>
		\code {.m}
[RBA_SDK ResetTagParam:M33_05_EMV_AUTHORIZATION_CONFIRMATION tagid:-1];
		\endcode

		<b>C# Example:</b>
		\code {.cs}
RBA_SDK_API.ResetTagParam(RBA_SDK_MSG_ID.M33_03_EMV_AUTHORIZATION_REQUEST);
RBA_SDK_API.ResetTagParam();
		\endcode
		
		\sa	RBA_SDK_AddTagParam
		\sa RBA_SDK_GetTagParam
	 */
    DLLEXPORT int  RBA_SDK_ResetTagParam(int msg, unsigned int tagId);
    //! \cond INSTANCE_FUNCS
    DLLEXPORT int  RBA_SDK_ResetTagParamFor(unsigned int instanceId, int msg, unsigned int tagId);
    //! \endcond

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/**
		Sets the function that the \libraryName calls to 
        provide logging information to your application.
		
		\cppThreadWarning
		
		\aboutLogging

		\param[in] cbFunction A pointer to the function.
		
		\sa LOUT
		\sa RBA_SDK_SetDefaultLogLevel
		\sa RBA_SDK_SetModuleLogLevel
		\sa RBA_SDK_SetTraceOutputFormatOption
	 */
    DLLEXPORT void   RBA_SDK_SetLogCallBack(LOUT cbFunction);
    
    /**
     Sets the default function that the \libraryName calls to
     provide logging information to your application.
     Default function uses standard output for printing a messages
     
     
     \cppThreadWarning
     
     \aboutLogging
     
     \sa LOUT
     \sa RBA_SDK_SetDefaultLogLevel
     \sa RBA_SDK_SetModuleLogLevel
     \sa RBA_SDK_SetTraceOutputFormatOption
     */

    DLLEXPORT void   RBA_SDK_SetDefaultLogCallback();

	/**
		Sets the default level of detail of information to be logged.
		
		\aboutLogging
		
		\param[in] level The level of logging detail.
		
		\sa LOG_LEVEL
		\sa RBA_SDK_SetLogCallBack
		\sa RBA_SDK_SetModuleLogLevel
		\sa RBA_SDK_SetTraceOutputFormatOption
	 */
	DLLEXPORT void   RBA_SDK_SetDefaultLogLevel(LOG_LEVEL level);
	
	/**
		Sets the level of detail of information to be logged for the specified module.
		
		\aboutLogging
		
		\param[in] moduleName The name of the module.
		\param[in] level The level of logging detail.
		
		\sa LOG_LEVEL
		\sa RBA_SDK_SetDefaultLogLevel
		\sa RBA_SDK_SetLogCallBack
		\sa RBA_SDK_SetTraceOutputFormatOption
	 */
    DLLEXPORT void   RBA_SDK_SetModuleLogLevel(const char* moduleName, LOG_LEVEL level);
	
	/**
		Sets what information is included in the logging output.
		
		\aboutLogging
	 
		\param[in] option What information appears in the logging output.
		
		\sa RBA_SDK_SetDefaultLogLevel
		\sa RBA_SDK_SetLogCallBack
		\sa RBA_SDK_SetModuleLogLevel
	 */
    DLLEXPORT void   RBA_SDK_SetTraceOutputFormatOption(LOG_OUTPUT_FORMAT_OPTIONS option);

    /**
		Triggers the \libraryName to output log and trace data.
		
		Use this function to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
		
		Use the \ref RBA_SDK_SetLogCallBack function to set the function that the \libraryName calls to 
        provide logging information to your application.
		
		\aboutLogging
		
		\param[in] module The name of the module to which to attribute the logging event.
		\param[in] severity The level of the logging detail.
		\param[in] format The format string for the logging message.
		
		\sa RBA_SDK_SetDefaultLogLevel
		\sa RBA_SDK_SetLogCallBack
		\sa RBA_SDK_SetModuleLogLevel
		\sa RBA_SDK_SetTraceOutputFormatOption
	 */
    DLLEXPORT void   RBA_SDK_LogOut(const char* module, LOG_LEVEL severity , const char* format, ...);
	
    //! \cond INSTANCE_FUNCS
    DLLEXPORT void   RBA_SDK_LogOutFor(unsigned int instance, const char* module, LOG_LEVEL severity , const char* format, ...);
    //! \endcond
    
#ifdef __cplusplus
}
#endif

/** @} */
