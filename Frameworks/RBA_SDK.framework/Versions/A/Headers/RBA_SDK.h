//
//  RBA_Driver.h
//  RBA_Driver
//
//  Created by Serge Pjatkin on 10/30/12.
//  Copyright (c) 2012 Serge Pjatkin. All rights reserved.
//

#pragma once

#import <Foundation/Foundation.h>
#define IOS_PLATFORM 1

#include "CommSettings.h"
#include "InterfacesId.h"
#include "LogTraceTypes.h"
#include "msgId.h"
#include "RBA_SDK_Errors.h"
#include "RBA_SDK_Interface.h"
#include "RBA_SDK_AttributeId.h"
#include "iSMPBarCodeReaderManager.h"

/** @addtogroup sdk_objective-c_api
    @{ */
	
/** 
	Protocol for callback delegates that handle PIN pad messages, connection events, and battery level events.
	
	Implement the methods to handle the events.

	\cppThreadWarning
		
	\sa RBA_SDK#SetDelegate:
*/
@protocol RBA_SDK_Event_support <NSObject>  

@required
/** 
	Method that is called when the library receives an asynchronous response or non-blocking message from a device.
	
	\cppThreadWarning
	
	\aboutMessaging
		
	\param[in] messageId The ID of the message that has been received.

	\sa RBA_SDK#ProcessMessage:
	\sa RBA_SDK#SetProcessMessageSyncMode:
	\sa RBA_SDK#SetProcessMessageAsyncMode:
	\sa RBA_SDK#SetDelegate
 */
-(void) ProcessPinPadParameters:(NSInteger) messageId;

@optional
/** 
	Method that is called when the library establishes a connection that allows end-to-end communication with a PIN pad device.
	
	To enable the library to call this method, use the \ref RBA_SDK#EnableNotifyRbaConnect: method.
	
	\cppThreadWarning
	
	\aboutConnecting
		
	\sa RBA_SDK#EnableNotifyRbaConnect:
 */
-(void) RBA_Connected;

/** 
	Method that is called when the library terminates a connection with a PIN pad device.
	
	To enable the library to call this method, use the \ref RBA_SDK#EnableNotifyRbaDisconnect: method.
	
	\cppThreadWarning
	
	\aboutConnecting
		
	\sa RBA_SDK#EnableNotifyRbaDisconnect:
 */
-(void) RBA_Disconnected;

/** 
	Method that is called when the battery level crosses the threshold.
	
	The method is called when the threshold is crossed, either from above or below.

	Set the threshold by using the \ref RBA_SDK#SetBatteryNotifyThreshold: method.
	
	\cppThreadWarning
	
	\param[in] level The battery charge level as a percentage of the full battery charge.
	\param[in] btState Whether the battery is charging or discharging
	\param[in] theBatteryLevelState Whether the battery is above or below the threshold.
		
	\sa RBA_SDK#SetBatteryNotifyThreshold:
 */
-(void) RBA_BatteryLevel:(int)level state:(BATTERY_STATE)btState levelState:(BATTERY_LEVEL_STATE)theBatteryLevelState;

@end

//extern NSString* const kRBA_SDK_BatteryLevel;

/**	
	Provides an Objective-C wrapper for the \libraryName functionality.
*/
@interface RBA_SDK : NSObject

/** 
	Gets the SDK version number of the \libraryName.
	
	\return A string that represents the library version number. 
*/
+ (NSString*) GetVersion;

/**
	Initializes the \libraryName.

	With the exception of the \ref LogTrace#SetDefaultLogLevel: and \ref GetVersion methods, an application must call this method before it can call other methods in the library.

	\aboutInitializing

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa Connect:
	\sa RBA_SDK_Shutdown
 */
+ (NSInteger) Initialize;
- (id) initWithName:(NSString*)name;
- (id) initWithName:(NSString*)name encoding:(NSStringEncoding)encoding;

- (unsigned int) GetInstanceId;
- (NSString*) GetName;

/**
	Prepares the \libraryName to be unloaded by freeing all internal resources.

	This method frees all internal resources managed by the library, including message parameters, so that the application can unload the library from memory.

	\aboutInitializing

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa Disconnect
	\sa RBA_SDK_Initialize
 */
+ (NSInteger) Shutdown;
- (void) dealloc;

/**
	Initiates a connection to a device.

	\note The library must be properly initialized using the \ref RBA_SDK_Initialize method before calling this method.
		
	\note The communication settings used by your application must match the configuration of the device being used. In other words, you cannot configure the RBA SDK to communicate via Ethernet if the device is configured to use a serial connection.
		
	After the library establishes a connection and end to end and communication is possible, the library calls the application's connected callback method. For more information, see the \ref EnableNotifyRbaConnect:) method and the \ref RBA_SDK_Event_support#RBA_Connected and \ref RBA_SDK_Event_support#RBA_Disconnected methods.

	\aboutConnecting

	\param[in] settings The communication settings for the connection.
		
	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa Disconnect
	\sa GetConnectionStatus
	\sa RBA_SDK_Initialize
	\sa SetCommTimeouts:
	\sa EnableNotifyRbaConnect:
 */
+ (NSInteger) Connect:(SETTINGS_COMMUNICATION) settings;
- (NSInteger) Connect:(SETTINGS_COMMUNICATION) settings;

/**
	Reconnects to a device, using the previous communication settings.

	You can call this method to re-establish a connection with a device after the \ref Connect:(SETTINGS_COMMUNICATION) and \ref Disconnect methods were called.
	- If the application calls this method without previously calling the \ref Connect:(SETTINGS_COMMUNICATION)  method, then this method tries to connect using the default settings, which are defined by the \ref SETTINGS_COMMUNICATION structure with all values set to binary zero.
	- If the device is already connected, then this method returns an \ref RESULT_ERROR_ALREADY_CONNECTED error.

	To conserve power if your application is running on a mobile or battery powered device, you can call the \ref Disconnect method between transactions or after a period of inactivity, and then call the Reconnect method before sending the next request.
	
	\aboutConnecting
		
	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the \ref ERROR_ID enumeration.

	\sa Connect: 
	\sa Disconnect
	\sa Initialize
	\sa SetCommTimeouts:
 */
+ (NSInteger) Reconnect;
- (NSInteger) Reconnect;

/**
	Closes the connection to the device.
	
	\aboutConnecting

	\return     \ref RESULT_SUCCESS if successful, otherwise, an error code defined in RBA_SDK_Errors.h

	\sa         Connect:(SETTINGS_COMMUNICATION)
	\sa 		GetConnectionStatus
 */
+ (NSInteger) Disconnect;
- (NSInteger) Disconnect;

/** 
 *  Returns the connection status.
 *
 *	\aboutConnecting
 *  
 *  \return     The current state of the device connection (see \ref CONNECTION_STATUS).
 *  
 *  \sa         Connect:
 *	\sa			Disconnect
 */
+ (NSInteger) GetConnectionStatus;
- (NSInteger) GetConnectionStatus;

/**
	Sets a parameter for a PIN pad request message.

	Use this method to provide the \libraryName with a value for each of the required parameters for a PIN pad message that is to be processed on the device. The library constructs a request messages for the device from the message ID and the associated parameter values.

	This method overwrites any previous value for the parameter. However, some parameters allow multiple values. To set multiple values on a parameter, use the \ref AddParam:data: method.
	
	\aboutMessaging
	For information about specific messages and parameters, see the \baseGuide and the 
	\ref MESSAGE_ID and \ref PARAMETER_ID enumerations.

	\param[in]  id   The ID of parameter to set.
	\param[in]  data The value to which to set the parameter.

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	<b>Objective-C Example:</b>
	\code {.m}
[RBA_SDK SetParam:P01_REQ_APPID data:@"0000"];
	\endcode

	\sa AddParam:data:
	\sa GetParam:
	\sa ProcessMessage:
	\sa ResetParam:
 */
+ (NSInteger) SetParam:(NSInteger) id data:(NSString*) data;
- (NSInteger) SetParam:(NSInteger) id data:(NSString*) data;

/**
	Adds to or constructs an array of values for a parameter for a PIN pad request message.

	Call this method to build an array of values for a parameter to send to the connected device when your application calls the \ref ProcessMessage: method.
	-# To set the first value, call the \ref SetParam:data: method.
	-# Then call the \b AddParam method to add subsequent values to the array.
		
	\note Any call to the \ref SetParam:data: method overwrites any previous values that may have been set on the associated parameter.

	\warning When building an array of values for a specific \ref PARAMETER_ID, the order in which the application adds these values is significant.

	Only a few messages support a variable number of parameters.
	\aboutMessaging
	For more information about specific messages and parameters, see the \baseGuide.

	\param[in]  id   The ID of the value to add to the parameter value array.
	\param[in]  data A pointer to a buffer that contains the value to add to the parameter value array.
    
	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	<b>Objective-C Example:</b>
	\code {.m}
[RBA_SDK RBA_SDK_SetParam:P13_REQ_AMOUNT data:@"100"];
[RBA_SDK RBA_SDK_AddParam:P13_REQ_AMOUNT data:@"200"];
[RBA_SDK RBA_SDK_AddParam:P13_REQ_AMOUNT data:@"3000"];
	\endcode

	\sa GetParam:
	\sa ProcessMessage:
	\sa SetParam:data:
 */
+ (NSInteger) AddParam:(NSInteger) id data:(NSString*) data;
- (NSInteger) AddParam:(NSInteger) id data:(NSString*) data;

/** 
	Places the \libraryName in the asynchronous message processing mode.
	
	\note In asynchronous mode, all messages as asynchronous. When the 
		message finishes processing, the library calls the application's 
		\ref RBA_SDK_Event_support#ProcessPinPadParameters: method, which 
		the application can set using the \ref SetDelegate: method.
	
	\warning Using synchronous mode (see \ref SetProcessMessageSyncMode) 
		is recommended over asynchronous mode. However, depending on the 
		message ID, synchronous mode may result in blocking (synchronous) 
		messages or non-blocking (asynchronous) messages.
	
	\aboutMessaging

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa         ProcessMessage:
	\sa         SetProcessMessageSyncMode
	\sa			RBA_SDK_Event_support#ProcessPinPadParameters:
 */
+ (NSInteger) SetProcessMessageAsyncMode;
- (NSInteger) SetProcessMessageAsyncMode;

/** 
	Places the \libraryName in the synchronous message processing mode.
		
	\note Depending on the message ID, synchronous mode may result in blocking (synchronous) messages or non-blocking (asynchronous) messages.
		
	\note For non-blocking messages, when the message finishes processing, the library calls the \ref RBA_SDK_Event_support#ProcessPinPadParameters: method. Use the \ref SetDelegate: method to set the callback delegate.
	
	\aboutMessaging
	
	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa RBA_SDK_Event_support#ProcessPinPadParameters:
	\sa ProcessMessage:
	\sa SetProcessMessageAsyncMode
 */
+ (NSInteger) SetProcessMessageSyncMode;
- (NSInteger) SetProcessMessageSyncMode;

/** 
	Sends an RBA message to the device.

	An application calls this method to send an RBA message to the device.  All
	the low-level details related to the connection, protocol, and message 
	acknowledgements are handled by the \libraryName.
	
	\aboutMessaging

	\note If the device responds immediately (synchronous mode has been set and the
		message is blocking), then this method handles the response message from the device.
 		If the device does not respond immediately (asynchronous mode has been set or the
		message is non-blocking or callback only), then the message callback is called when the response is
		ready. Implement the \ref RBA_SDK_Event_support#ProcessPinPadParameters: to handle the message callback. 
		Use the \ref SetDelegate: method to set the callback delegate.

	\param[in]  CommandID Unique Message ID defined in msgID.h to be processed

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa SetParam:data:
	\sa GetParam:
	\sa SetProcessMessageSyncMode
	\sa SetProcessMessageAsyncMode
	\sa RBA_SDK_Event_support#ProcessPinPadParameters:      
 */
+ (NSInteger) ProcessMessage:(NSInteger) CommandID;
- (NSInteger) ProcessMessage:(NSInteger) CommandID;

/**
	Gets a parameter from a message that the \libraryName received from a PIN pad device.
		
	Use this method to retrieve the values for parameters for a PIN pad message that was sent from the device to the library. The library parses each message it receives from the device to extract the parameter values. To notify the library that it can free the memory for its copy of the parameter data, use the \ref ResetParam: method.
		
	To send a message to the device, see the \ref ProcessMessage: method. To receive messages from the device, implement the \ref RBA_SDK_Event_support#ProcessPinPadParameters: method and use the \ref SetDelegate: method to set the callback method.
	
	\aboutMessaging

	\param[in]     id   The ID of the parameter value to get.

	\return The parameter value.

	<b>Objective-C Example:</b>
	\code {.m}
NSString* data = [RBA_SDK GetParam:P00_RES_REASON_CODE];
	\endcode

	\sa GetParamLen:
	\sa ProcessMessage:
	\sa ResetParam:
	\sa SetParam:data:
	\sa RBA_SDK_Event_support#ProcessPinPadParameters:  

	\todo We should consider having GetParam() return the value and automatically overwrite the value so it cannot be retrieved again by the application. This approach significantly reduces the possibility of an application leaving card holder data in memory for a longer period than necessary.
*/
+ (NSString*) GetParam:(NSInteger) id;
- (NSString*) GetParam:(NSInteger) id;

/**
	The same as \ref GetParam:, but returns an \b NSMutableString instead of an \b NSString.

	\param[in]     id   The ID of the parameter value to get.

	\return The parameter value.

	\sa GetParam:
	\sa GetParamLen:
	\sa ProcessMessage:
	\sa ResetParam:
	\sa SetParam:data:
	\sa RBA_SDK_Event_support#ProcessPinPadParameters:  

	\todo We should consider having GetParam() return the value and automatically overwrite the value so it cannot be retrieved again by the application. This approach significantly reduces the possibility of an application leaving card holder data in memory for a longer period than necessary.
*/
+ (NSMutableString*) GetMutableParam:(NSInteger) id;
- (NSMutableString*) GetMutableParam:(NSInteger) id;

/**
	Returns the size in bytes required to store the current value of a specific parameter.
	
	\aboutMessaging

	\param[in] id	The ID of the parameter.
	\return			The size in bytes required to store the current value of the parameter, or one of the error codes defined in the \ref ERROR_ID enumeration.
		
	\sa GetParam:
*/
+ (NSInteger) GetParamLen:(NSInteger) id;
- (NSInteger) GetParamLen:(NSInteger) id;

/**
	Clears a parameter value stored by the \libraryName.

	This method notifies the library that it should clear and free the memory for its copy of the parameter data. This method can free memory for parameters that were set either by the application or by the library when it received a message from the device.
		
	\note Some parameters hold sensitive card holder information. An application should call this method as soon as the data is no longer needed.
		
	\aboutMessaging

	\param[in] id	The ID of the parameter, or -1, to clear library memory for all parameters.

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa SetParam:data:
	\sa GetParam:
*/
+ (NSInteger) ResetParam:(NSInteger) id;
- (NSInteger) ResetParam:(NSInteger) id;

/** 
	Sets the communication timeout values used during communication with a device.
  
	Applications are expected to set proper values for the communication interface 
	(see \ref InterfacesId.h) they are using.
	If the value for a timeout interval is 0, then then the \libraryName will set the default  
	value for this interval. If value is invalid, then the \libraryName
	will set the minimum interval for the interface. 
	
	\note For all interfaces, the 
		ReceiveTimeout (see \ref SETTINGS_COMM_TIMEOUTS) value refers to the time it takes to receive each character, 
		not the time it takes to receive a full packet.
	
	\aboutConnecting
	
	\param[in]	Timeouts The timeout values to be used during device communication.
	
	\returns	\ref RESULT_SUCCESS if successful, otherwise, an error code defined in RBA_SDK_Errors.h
 */ 
+ (NSInteger) SetCommTimeouts:(SETTINGS_COMM_TIMEOUTS) Timeouts;
- (NSInteger) SetCommTimeouts:(SETTINGS_COMM_TIMEOUTS) Timeouts;

/** 
	Sends a custom message of a type which is supported on the RBA (terminal), but not
	yet supported by the \libraryName.
	
	If \a bReceive is true, the message response will be handled as blocking (synchronous),
	and the method will wait for the device to respond before returning. If \a bReceive is false, the message 
	response will be handled as non-blocking (asynchronous), and the message response will be
	returned in the message callback with a message ID of RAW_PINPAD_RESPONSE. The custom message
	that is received can be read by using \ref GetParam: with parameter ID of 
	RAW_PINPAD_RESPONSE_DATA. 
	
	It is also possible to use \b SendCustomMessage to send a request for a supported message
	ID to be received asynchronously (bReceive=false). In this case, the \libraryName will recognize the
	response as a supported message and issue a callback with the standard supported message ID. 
	You can then use \ref GetParam: to retrieve the parameters using the supported parameter IDs.
	
	\aboutMessaging
	
	\param[in]  RawData    The data to be sent to the terminal.
	\param[in]  bReceive   \b true if the message response is handled as blocking;
			\b false if the message response is handled as non-blocking.
	
	\return     \ref RESULT_SUCCESS if successful; otherwise, an error code defined in RBA_SDK_Errors.h
	
	\sa SetProcessMessageSyncMode
	\sa GetParam:
 */
+ (NSInteger) SendCustomMessage:(NSString *)RawData receive:(BOOL) bReceive;
- (NSInteger) SendCustomMessage:(NSString *)RawData receive:(BOOL) bReceive;

// 	TODO: Fix the RBA_SDK_ATTRIBUTE_ID reference so that it goes to C/C++ instead of C#.
/**
	Sets an attribute of the \libraryName.
	
	Use this method to configure an attribute of the library. The attribute IDs are defined in the \ref RBA_SDK_ATTRIBUTE_ID enumeration.
		
	\note For numeric values, the value must be a positive integer, represented as a decimal string.

	\param[in] id The ID of the attribute to set.
	\param[in] data The value to which to set the attribute. 

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	<b>Objective-C Example:</b>
	\code {.m}
[RBA_SDK SetAttribute:BATTERY_TIMER_INTERVAL_MINUTES data:@"5"];
	\endcode

	\sa         GetAttribute:
  */
+ (NSInteger) SetAttribute:(NSInteger) id data:(NSString*) data;
- (NSInteger) SetAttribute:(NSInteger) id data:(NSString*) data;

// 	TODO: Fix the RBA_SDK_ATTRIBUTE_ID reference so that it goes to C/C++ instead of C#.
/**
	Gets an attribute of the \libraryName.
		
	Use this function to retrieve the current value of an attribute of the library. The attribute IDs are defined in the \ref RBA_SDK_ATTRIBUTE_ID enumeration.
		
	\note For numeric values, the value is a positive integer, represented as a decimal string.

	\param[in] id The ID of the attribute to get.

	\return The attribute value.

	<b>Objective-C Example:</b>
	\code {.m}
NSString* interval = [RBA_SDK GetAttribute:BATTERY_TIMER_INTERVAL_MINUTES];
	\endcode
	
	\sa SetAttribute:data:
 */
+ (NSString*) GetAttribute:(NSInteger) id;
- (NSString*) GetAttribute:(NSInteger) id;

/**
	Adds to or constructs data values for the EMV tag data for an applicable PIN pad request message.
		
	Use this method to provide the \libraryName with the EMV parameter data for an EMV message that is to be processed on the device. The library constructs an EMV request message for the device from the message ID, the associated parameter values, and the collection of EMV tag parameters.
		
	Use the \ref ResetTagParam:tagid: method to clear previous EMV tag data. Use this method to set the first and each additional tag parameter for an EMV message.
	
	Each message has a unique set of tag parameters that must be set in order for the message to be processed. These parameters are defined in the \emvGuide.

	\param[in]  msg     The ID of the message for which to include the tag parameter.
	\param[in]  tagId   The ID of the EMV tag parameter.
	\param[in]  data    The value for the EMV tag parameter.

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	\sa AddTagParam:tagid:string:
	\sa GetTagParam:tagData:
	\sa ResetTagParam:tagid:
 */
+ (NSInteger) AddTagParam:(NSInteger)msg tagid:(NSInteger)tagId data:(NSData*) data;
- (NSInteger) AddTagParam:(NSInteger)msg tagid:(NSInteger)tagId data:(NSData*) data;

/**
	Adds to or constructs string values for the EMV tag data for an applicable PIN pad request message.
		
	Use the \ref ResetTagParam:tagid: method to clear previous EMV tag data. Use this method to set the first and each additional tag parameter for an EMV message.
	
	\aboutMessaging

	\param[in]  msg     The ID of the message for which to include the tag parameter.
	\param[in]  tagId   The ID of the EMV tag parameter.
	\param[in]  str    The value for the EMV tag parameter.

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	<b>Objective-C Example:</b>
	\code {.m}
[RBA_SDK AddTagParam:M33_04_EMV_AUTHORIZATION_RESPONSE tagid:0x1000 string:@"0x1000"];
	\endcode

	\sa AddTagParam:tagid:data:
	\sa GetTagParam:tagData:
	\sa ResetTagParam:tagid:
 */
+ (NSInteger) AddTagParam:(NSInteger)msg tagid:(NSInteger)tagId string:(NSString*) str;
- (NSInteger) AddTagParam:(NSInteger)msg tagid:(NSInteger)tagId string:(NSString*) str;

/**
	Gets the next tag parameter associated with an EMV message that the \libraryName received from a PIN pad device.

	Use this method to retrieve values for tag parameters that were provided by the device in an EMV response message. Messages can contain multiple tag parameters. Call this method multiple times to retrieve all of the tag parameters for the message.
		
	To get the length of the data contained in a tag parameter, use the \ref GetTagParamLen: method. To notify the library that it can free the memory for its copy of the tag parameter data, use the \ref ResetTagParam:tagid: method.
		
	Data for an individual tag can only be retrieved once, as  after providing the tag parameter value to the calling application, the library clears and frees the associated memory.
		
	\aboutMessaging

	\param[in] msg The ID of the EMV message.
	\param[out] data A pointer the buffer to which the library can copy the tag parameter value.

	\return If successful, the ID of the EMV tag parameter; otherwise, one of the error codes defined in the \ref ERROR_ID enumeration.

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

	\sa ResetTagParam:tagid:
	\sa GetTagParamLen:
	\sa AddTagParam:tagid:data:
	\sa AddTagParam:tagid:string:
 */
+ (NSInteger) GetTagParam:(NSInteger)msg tagData:(NSData**)data;
- (NSInteger) GetTagParam:(NSInteger)msg tagData:(NSData**)data;

/**
	Returns the size in bytes required to store the next available value of an EMV tag parameter from the \libraryName.

	EMV messages can contain multiple tag parameters. To get the size of each EMV tag parameter, call this method each time before you call the \ref GetTagParam:tagData: method.
		
	\note If the application has retrieved all of the available EMV tag parameters for the message, then a call to this method returns the \ref RESULT_ERROR_PARAMETER value.

	\param[in] msg The ID of the EMV message.

	\return The size in bytes required to store the current value of the tag parameter, or one of the error codes defined in the \ref ERROR_ID enumeration.

	<b>Objective-C Example:</b>
	\code
if( [RBA_SDK GetTagParamLen:M33_05_EMV_AUTHORIZATION_CONFIRMATION] <= 0 )
{
	return RESULT_ERROR_PARAMETER;
}
	\endcode

	\sa     GetTagParam:tagData:
 */
+ (NSInteger) GetTagParamLen:(NSInteger)msg;
- (NSInteger) GetTagParamLen:(NSInteger)msg;

/**
	Clears memory for an EMV tag parameter stored by the \libraryName for an EMV message.

	This method notifies the library that it should clear and free the memory for its copy of the tag parameter data. method function can free memory for parameters that were set either by the application or by the library when it received a message from the device.
	
	\aboutMessaging

	\param[in] msg The ID of the message that contains the tag parameters, or -1 to clear all tag data for all messages.
	\param[in] tagId The ID of the tag parameter to clear, or -1 to clear all tag parameter data for the message.

	\return \ref RESULT_SUCCESS if successful; otherwise, one of the error codes defined in the RBA_SDK_Errors.h file.

	<b>Objective-C Example:</b>
	\code {.m}
[RBA_SDK ResetTagParam:M33_05_EMV_AUTHORIZATION_CONFIRMATION tagid:-1];
	\endcode

	\sa AddTagParam:tagid:data:
	\sa AddTagParam:tagid:string:
	\sa GetTagParam:tagData:
 */
+ (NSInteger) ResetTagParam:(NSInteger) msg tagid:(NSInteger)tagId;
- (NSInteger) ResetTagParam:(NSInteger) msg tagid:(NSInteger)tagId;

/** 
	Sets a callback delegate that can be called when events occur.
	
	The events that the callback can handle are:
		- When the library has either connected or ended a connection with a device.
		- When messages are ready after the \ref ProcessMessage: method has been called.
		- When the battery level has crossed the battery level threshold.
	
	\cppThreadWarning
	
	\aboutConnecting
	\aboutMessaging
		
	\param[in] delegate The function that will be called when events occur.

	\sa ProcessMessage:
	\sa Connect:
	\sa SetBatteryNotifyThreshold:
 */ 
+ (void) SetDelegate:(id <RBA_SDK_Event_support> ) delegate;

- (void) ProcessPinPadParameters:(NSInteger) messageId;

/** 
	Sets the battery level threshold for the event delegate that is called from the iConnectEFT library when the threshold is crossed.
		
	The library calls the callback delegate that was set with the \ref SetDelegate: method when the battery level crosses the threshold, either below or above.
	
	\cppThreadWarning
			
	\param[in]  threshold               Battery threshold as the percent of total battery capacity.

  \sa SetDelegate:
 */
+ (void) SetBatteryNotifyThreshold:(int) threshold;

/** 
	Sets whether a callback delegate will be called when the library establishes or terminates a connection that allows end-to-end communication with a PIN pad device.
	
	The device is not ready for communication until the library calls the callback delegate or the library returns the \ref CONNECTED value from the \ref RBA_SDK_GetConnectionStatus function.
	
	The callback delegate is set using the \ref SetDelegate: method.

	\cppThreadWarning
		
	\param[in] enable If \b true, then callback delegate is called when the library establishes or terminates a connection; if \b false, then no callback delegate is called.

	\sa SetDelegate:
	\sa Connect:
	\sa GetConnectionStatus
 */ 
+ (void) EnableNotifyRbaConnect:(bool) enable;
- (void) EnableNotifyRbaConnect:(bool) enable;
/**
	Sets whether a callback delegate will be called when the library establishes or terminates a connection that allows end-to-end communication with a PIN pad device.
	
	The device is not ready for communication until the library calls the callback delegate or the library returns the \ref CONNECTED value from the \ref RBA_SDK_GetConnectionStatus function.
	
	The callback delegate is set using the \ref SetDelegate: method.
 
	\cppThreadWarning
 
	\param[in] enable If \b true, then callback delegate is called when the library establishes or terminates a connection; if \b false, then no callback delegate is called.
 
	\sa SetDelegate:
	\sa Connect:
	\sa GetConnectionStatus
 */
+ (void) EnableNotifyRbaDisconnect:(bool) enable;
- (void) EnableNotifyRbaDisconnect:(bool) enable;

@end

/** 
	Protocol for callback delegates that handle logging events.

	\cppThreadWarning
	
	\aboutLogging
		
	\sa LogTrace#SetDelegate:
*/
@protocol LogTrace_support <NSObject>

/** 
	Method that is called when there is information to be logged.
	
	Use this method to write the \a line string into a log.
	
	\cppThreadWarning
		
	\param[in] line Logging information.

	\sa LogTrace
 */ 
-(void) LogTraceOut:(NSString*) line;

@end

/** 
	Provides capabilities for logging of information from the \libraryName.
	
	\aboutLogging

	\sa LogTrace_support:
*/
@interface LogTrace : NSObject
{
    NSString* m_moduleName;
    unsigned int m_instanceId;
}

/** 
	Sets the default level of detail of information to be logged.
	
	\aboutLogging

	\param[in] level The level of logging detail.

	\sa SetModuleLogLevel:severity:
*/
+ (void) SetDefaultLogLevel:(LOG_LEVEL) level;

/** 
	Sets the level of detail of information to be logged for the specified module.
	
	\aboutLogging

	\param[in] moduleName The name of the module.
	\param[in] level The level of logging detail.

	\sa SetDefaultLogLevel:
*/
+ (void) SetModuleLogLevel:(const char*) moduleName severity:(LOG_LEVEL) level;

/** 
	Sets the callback delegate that is called when there is information to be logged.
	
	\aboutLogging

	\param[in] delegate The callback delegate.
*/
+ (void) SetDelegate:(id<LogTrace_support> ) delegate;

/** 
	Sets what information is included in the logging output.
	
	\aboutLogging

	\param[in] option What information appears in the logging output.
*/
+ (void) SetTraceOutputFormatOption:(LOG_OUTPUT_FORMAT_OPTIONS) option;

/** 
	Initializes by setting a module name to be used when logging information relevant to a specific module.
	
	\aboutLogging

	\param[in] moduleName The module name
	
	\sa SetModuleLogLevel:severity:
*/
- (id) initWithModuleName:(NSString*)moduleName;
- (id) initWithModuleName:(NSString*)moduleName instanceId:(unsigned int)instanceId;

/** 
	Triggers the \libraryName to output logging information of \ref LTL_INFO severity.
	
	Use this method to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
	
	Use the \ref SetDelegate: method to set the delegate that the \libraryName calls to provide logging information to your application.
	
	\aboutLogging

	\param[in] format The format string for the logging message.
	
	\sa LOG_LEVEL
	\sa Warning:
	\sa Error:
	\sa Debug:
	\sa Trace:
*/
- (void) Info:(NSString*)format, ...;

/** 
	Triggers the \libraryName to output logging information of \ref LTL_WARNING severity.
	
	Use this method to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
	
	Use the \ref SetDelegate: method to set the delegate that the \libraryName calls to provide logging information to your application.
	
	\aboutLogging

	\param[in] format The format string for the logging message.
	
	\sa LOG_LEVEL
	\sa Info:
	\sa Error:
	\sa Debug:
	\sa Trace:
*/
- (void) Warning:(NSString*)format, ...;

/** 
	Triggers the \libraryName to output logging information of \ref LTL_ERROR severity.
	
	Use this method to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
	
	Use the \ref SetDelegate: method to set the delegate that the \libraryName calls to provide logging information to your application.
	
	\aboutLogging

	\param[in] format The format string for the logging message.
	
	\sa LOG_LEVEL
	\sa Info:
	\sa Warning:
	\sa Debug:
	\sa Trace:
*/
- (void) Error:(NSString*)format, ...;

/** 
	Triggers the \libraryName to output logging information of \ref LTL_DEBUG severity.
	
	Use this method to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
	
	Use the \ref SetDelegate: method to set the delegate that the \libraryName calls to provide logging information to your application.
	
	\aboutLogging

	\param[in] format The format string for the logging message.
	
	\sa LOG_LEVEL
	\sa Info:
	\sa Warning:
	\sa Error:
	\sa Trace:
*/
- (void) Debug:(NSString*)format, ...;

/** 
	Triggers the \libraryName to output logging information of \ref LTL_TRACE severity.
	
	Use this method to have the library generate a log message based on the input parameters. The library uses the \a format and any additional parameters to created the message text, similar to the C printf function.
	
	Use the \ref SetDelegate: method to set the delegate that the \libraryName calls to provide logging information to your application.
	
	\aboutLogging

	\param[in] format The format string for the logging message.
	
	\sa LOG_LEVEL
	\sa Info:
	\sa Warning:
	\sa Error:
	\sa Debug:
*/
- (void) Trace:(NSString*)format, ...;

@end

/** @}  */