//! \file
//! Contains settings and data structures related to communication.

#pragma once

//! @addtogroup sdk_c_api
//!@{

//!  	Baud rate of 19200 bits/second.
#define BaudRate_19200					19200
//! 	Baud rate of 38400 bits/second.
#define BaudRate_38400					38400
//! 	Baud rate of 57600 bits/second.
#define BaudRate_57600					57600
//! 	Baud rate of 115200 bits/second.
#define BaudRate_115200					115200

//! 	Size of 7 bits as the data byte for the RS-232 logic of the target device.
#define DataBits7   					7
//! 	Size of 8 bits as the data byte for the RS-232 logic of the target device.
#define DataBits8                       8

//! 	Used when no parity bit.
#define ParityNone						0
//! 	Used when parity bit is odd.
#define ParityOdd						1
//! 	Used when parity bit is even.
#define ParityEven						2

//! 	Indicates that one stop bit is used in the RS-232 protocol for the target device .
#define StopBits1						1
//! 	Indicates that two stop bits are used in the RS-232 protocol for the target device.
#define StopBits2						2

//! 	Indicates that there is no Flow Control option for the RS232 logic .
#define FlowCtrl_None					0
//! 	Indicates that the Flow Control option for the RS232 logic is Xon/Xoff.
#define FlowCtrl_Xon_Xoff				1
//! 	Indicates that the Flow Control option for the RS232 logic is hardware.
#define FlowCtrl_HW						2

/** Used to set AutoDetect to <strong>on</strong>.
 *
 *  \details When used, the iConnectEFT library will try 
 *         automatically detect the BaudRate, DataBits, etc. for a given COM Port.
 */
#define AutoDetectON                    1
//! 	Used to set AutoDetect to <strong>on</strong>.
#define AutoDetectOFF                   0

/**
	The current state of the communication interface to the device.
	
	\aboutConnecting
 */
enum CONNECTION_STATUS
{
	//! Device is not connected to the specified communication interface.
	DISCONNECTED        = 0,
    //! Device is connected to the communication interface and is ready for requests.
	CONNECTED           = 1,
    //! Device is connected, but is not ready for requests. This is an intermittent status that occurs during the connecting process. The application should wait for a CONNECTED status before attempting to communicate.
	CONNECTED_NOT_READY = 2
};

/**
	Information about Ethernet communication, to be initialized by the 
	application.

	\aboutConnecting
 */
typedef struct TAG_SETTINGS_IP
{
	//!	The IP Address of the device.
    char IPAddress[15 + 1];
	//!	The port number of an RBA application on the device.
	//!
	//!	\details Although a number, Port is a string.
	char Port[5 + 1];
    //!	The raw socket descriptor.
    //!
    //!	\details The socket descripter must be opened tcp/ip socket descripter.
    int  SocketDescriptor;
} SETTINGS_IP;

/**
	Information about Bluetooth communication.

	The \ref DeviceName parameter is not currently required for Bluetooth 
	communication. The bluetooth terminal must be paired to the PC or ECR device 
	running iConnectEFT. iConnectEFT will then attempt to select and communicate 
	to the first bluetooth connected terminal it enumerates. For this reason and 
	in order for iConnectEFT to connect to the correct terminal, there should be 
	only one bluetooth terminal paired to the ECR at a time.

	\aboutConnecting
 */
typedef struct TAG_SETTINGS_BT
{
	//!	The name of the device.
    char DeviceName[20 + 1];

} SETTINGS_BT;

/**
	Information about RS232 serial communication.

	\aboutConnecting
 */
typedef struct TAG_SETTINGS_RS232
{
	//! The name of the COM port.
    char ComPort[40];
	
	/**	Used to set the Auto Detect Mode for USB and serial interfaces during connection operations.
	 *
	 *  \details If AutoDetect is \ref AutoDetectON, then the iConnectEFT library will 
	 *		try to automatically detect the BaudRate, DataBits, etc. for the COM Port. 
	 *      Use the values in the See Also section.
     *  \note Note: The autodetect mechanism cannot detect the COM port's name. 
	 *			You must provide the COM port's name where required in function calls. 
	 *  \sa AutoDetectON
	 *  \sa AutoDetectOFF
	 */
    int AutoDetect;
	
	/**	The baud rate for serial communication. 
	 *
	 *  \details Use the values in the See Also section.
	 *  \sa BaudRate_19200
	 *  \sa BaudRate_38400
	 *  \sa BaudRate_57600
	 *  \sa BaudRate_115200
	 */	
    int BaudRate;
	
	/**	The number of data bits in each byte of serial communication.
	 *
	 *  \details Use the values in the See Also section.
	 *  \sa DataBits7
	 *  \sa DataBits8
	 */		
    int DataBits;
	
	/**	Parity information for serial communication.
	 *
	 *  \details Use the values in the See Also section.
	 *  \sa ParityNone
	 *  \sa ParityOdd
	 *  \sa ParityEven
	 */		
    int Parity;
	
	/**	Stop bit information for serial communication.
	 *
	 *  \details Use the values in the See Also section.
	 *  \sa StopBits1
	 *  \sa StopBits2
	 */			
    int StopBits;

	
	/**	Flow Control information for serial communication.
	 *
	 *  \details Use the values in the See Also section.
	 *  \sa FlowCtrl_None
	 *  \sa FlowCtrl_Xon_Xoff
	 *  \sa FlowCtrl_HW
	 */			
    int FlowControl;
	
} SETTINGS_RS232;

/**
	Information about USB Human Interface Device (HID) communication, to be initialized by the application.

	\aboutConnecting
 */
typedef struct TAG_SETTINGS_USB_HID
{
	/**
		Whether to use autodetect.

		If this field is set to \ref AutoDetectON, then the \libraryName automatically searches for the device using the specified USB vendor and product ID.
		
		\sa AutoDetectON
		\sa AutoDetectOFF
	 */
    int autoDetect;
	
	//!	Ingenico's USB vendor ID.			
    unsigned short int vendor_id;
	
	//!	The USB product ID for the connected device.			
    unsigned short int product_id;
	
} SETTINGS_USB_HID;

/**
	Information about Accessory communication, to be initialized by the application.
 
	\aboutConnecting
 */
typedef struct TAG_SETTINGS_ACCESSORY
{
    //!	The Serial Number of the device.
    char serialNumber[20 + 1];
    //!	The Accessory name of the devie.
    char accessoryName[20 + 1];
    
} SETTINGS_ACCESSORY;

/**
	Settings for controlling communication timeouts.
	
	\note All timeout values are in milliseconds.

	\aboutConnecting
  */
typedef struct TAG_SETTINGS_COMM_TIMEOUTS
{
    /**	Connection timeout in milliseconds.
	 *
     *  \details The maximum duration in msec that the \libraryName will wait for the OS to
     *           establish a connection. If the connection is not established before
     *           this timeout expires, the \libraryName will return a timeout error to the
     *           application.
     */
    unsigned long ConnectTimeout;
	
    /**	Send timeout in milliseconds.
	 *
     *  \details The maximum duration in msec that the \libraryName will wait for the OS to
     *           send a message to the RBA terminal. If the send is not completed before
     *           this timeout expires, the \libraryName will return a timeout error to the
     *           application.
     */
    unsigned long SendTimeout;
	
    /**	Receive timeout in milliseconds.
	 *
     *  \details The maximum duration in msec that the \libraryName will wait between characters
     *           while receiving a message from the RBA terminal. If this timeout expires,
     *           the \libraryName will consider the message as complete and attempt to verify and
     *           parse it. If the message is incomplete, then the \libraryName will encounter errors
     *           during the verification and parsing process, and will return an error to the
     *           application.
     */
    unsigned long ReceiveTimeout;
	
} SETTINGS_COMM_TIMEOUTS;


/**
	Information about all modes of communication.
	\aboutConnecting
 */
typedef struct TAG_SETTINGS_COMMUNICATION
{
	/**
	 Indicates the communication interface mode that the \libraryName uses to communicate with the device.
	 
	 The supported interfaces are listed in \ref InterfacesId.h.
	 */				
    int interface_id;	

	/**	Settings for an Ethernet connection.
	 *
	 *  \details Used when the communication mode is set to \ref TCPIP_INTERFACE.
	 */		
	SETTINGS_IP         ip_config;

	/**	Settings for a serial connection.
	 *
	 *  \details Used when the communication mode is set to \ref SERIAL_INTERFACE.
	 */	
	SETTINGS_RS232		rs232_config;
	
	/**	Settings for a USB Human Interface Device (HID) connection.
	 *
	 *  \details Used when the communication mode is set to \ref USB_HID_INTERFACE.
	 */	
	SETTINGS_USB_HID	usbhid_config;		
	
	/**	Settings for a Bluetooth connection.
	 *
	 *  \details Used when the communication mode is set to \ref BLUETOOTH_INTERFACE.
	 */		
    SETTINGS_BT         bt_config;
    
    /**	Settings for a Bluetooth connection.
     *
     *  \details Used when the communication mode is set to \ref ACCESSORY_INTERFACE.
     */		
    SETTINGS_ACCESSORY  accessory_config;
    
} SETTINGS_COMMUNICATION;

/**	Whether the battery is charging or discharging.
 *  \sa BatteryLevelCallBack
 */
typedef enum {
	//! Battery state is not applicable. (That is, not relevant.)
    BS_NA, 
	//! Battery is charging.
	BS_CHARGING, 
	//! Battery is discharging.
	BS_DISCHARGING
} BATTERY_STATE;

/**	An indication of the battery's charge with regards to the threshold.
 *  \sa BatteryLevelHandler
 */
typedef enum {
    //! Battery level state is not applicable. (That is, not relevant.)
	BL_NA, 
	//! Battery level state is below a threshold
    BL_LEVEL_IS_BELOW_THRESHOLD,
	//! Battery level state is above a threshold
	BL_LEVEL_IS_ABOVE_THRESHOLD
} BATTERY_LEVEL_STATE;


//! @}

