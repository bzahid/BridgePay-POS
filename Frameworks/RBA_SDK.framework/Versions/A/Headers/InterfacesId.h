#pragma once

/*!
	\addtogroup sdk_c_api
	@{
*/

//! Device communication through the TCP/IP interface
#define TCPIP_INTERFACE                     0

//! Device communication through the RS-232 interface
#define SERIAL_INTERFACE                    1

/** Device communication through the USB HID (Human Interface Device) interface
  *
  * \warning USB HID is designed to quickly transfer small amounts of data and is not well suited
  *			for large data transfers.  During normal operation you should not see a significant 
  *		 	difference in performance; however, when performing large data transfers over 
  *		 	USB HID the transfer will be several times slower than with other interfaces.
  */
#define USB_HID_INTERFACE                   2

//!   Device communication through the Bluetooth interface
#define BLUETOOTH_INTERFACE                 3

/**  Device communication through the iOS accessory interface
  *
  * \note For iOS devices, use this instead of BLUETOOTH_INTERFACE.
  */
#define ACCESSORY_INTERFACE                 4

//!   Device communication through TCP/IP interface with SSL encryption 
#define SSL_TCPIP_INTERFACE                 5

/** Device communication through the USB
  *
  */
//#define USB_CDC_INTERFACE                   6

//!   MOC interface 
#define MOC_INTERFACE		               7


//!@}
