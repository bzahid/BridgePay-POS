/**************************************************************************
 *  THIS IS AUTO-GENERATED FILE. DO NOT EDIT
 *  INSTEAD OF THIS EDIT rba_sdk.xml and run XML2RBA_SDK.pl
 **************************************************************************/
//! \addtogroup	sdk_c_api
//!@{
//! \enum RBA_SDK_ATTRIBUTE_ID
//!
//! Interval for battery timer
//!\var	BATTERY_TIMER_INTERVAL_MINUTES
//!\brief		Interval for checking battery level, in minutes
//!
//! Process message timeout
//!\var	PROCESS_MESSAGE_TIMEOUT_SEC
//!\brief		Maximum timeout for the processing one message, in seconds
//!
//! Discover Service
//!\var	DISCOVER_SERVICE_UDP_PORT
//!\brief		UDP port to send broadcast messages. The same port uses for listening response
//!
//! Max number of sending internal message to detect the device is responding
//!\var	MAX_NUMBER_OF_PINGING_DURING_CONNECT
//!\brief		Max number of cycle to to send internal the M11_STATUS during the Connect procedure to detect the Telium device is responding. If device responded, library sends RBA_Connected notification, otherwise sends RBA_Disconnected notification.

enum RBA_SDK_ATTRIBUTE_ID {

//! \cond PRIVATE
//SSL Attribute for TCP/IP session
	SSL_ROOT_CERTIFICATE_FILE = 0,
//! \endcond
	SSL_CERTIFICATE_FILE_1 = 1,
	SSL_CERTIFICATE_FILE_2 = 2,
	SSL_CERTIFICATE_FILE_3 = 3,
	SSL_CERTIFICATE_FILE_4 = 4,
	SSL_LOCAL_CERTIFICATE_FILE = 5,
	SSL_LOCAL_CERTIFICATE_PASSPHRASE = 6,
	SSL_PRIVATE_KEY_FILE = 7,
	SSL_SECURE_PROTOCOL = 8,
	SSL_SERVER_HANDSHAKE = 9,

//Interval for battery timer
	BATTERY_TIMER_INTERVAL_MINUTES = 10,

//Process message timeout
	PROCESS_MESSAGE_TIMEOUT_SEC = 11,

//Discover Service
	DISCOVER_SERVICE_UDP_PORT = 12,

//Max number of sending internal message to detect the device is responding
	MAX_NUMBER_OF_PINGING_DURING_CONNECT = 13,

//! \cond PRIVATE
//Last Attribute for internal use
	ATTRIBUTE_LAST = 14,
//! \endcond

};
//!@}
