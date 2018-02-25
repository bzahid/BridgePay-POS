/*
 
 Copyright 2013 Ingenico Inc. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, is permitted provided that adherence to the following
 conditions is maintained. If you do not agree with these terms,
 please do not use, install, modify or redistribute this software.
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY INGENICO INC. "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL IMOBILE3, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */
#pragma once

//! @addtogroup barcode_settings
//!	@{
//! @enum BarcodeSymbology
//! @brief Supported barcode symbologies.
//! @details Supported barcode symbologies.
typedef enum
{
    BarcodeSymbologyUnknown = -1,
    BarcodeSymbologyAllSymbologies    = 0,
    
    BarcodeSymbologyEAN13,
    BarcodeSymbologyEAN8,
    BarcodeSymbologyUPCA,
    BarcodeSymbologyUPCE,
    BarcodeSymbologyEAN13_2,
    BarcodeSymbologyEAN8_2,
    BarcodeSymbologyUPCA_2,
    BarcodeSymbologyUPCE_2,
    BarcodeSymbologyEAN13_5,
    BarcodeSymbologyEAN8_5,
    BarcodeSymbologyUPCA_5,
    BarcodeSymbologyUPCE_5,
    BarcodeSymbologyCode39,
    BarcodeSymbologyInterleaved2of5 = 15,
    BarcodeSymbologyStandard2of5,
    BarcodeSymbologyMatrix2of5,
    BarcodeSymbologyCodabar = 19,
    BarcodeSymbologyAmesCode,
    BarcodeSymbologyMSI,
    BarcodeSymbologyPlessey,
    BarcodeSymbologyCode128,
    BarcodeSymbologyCode16K,
    BarcodeSymbology93,
    BarcodeSymbology11,
    BarcodeSymbologyTelepen,
    BarcodeSymbologyCode49,
    BarcodeSymbologyCode39_ItalianCPI,
    BarcodeSymbologyCodablockA,
    BarcodeSymbologyCodablockF,
    BarcodeSymbologyPDF417 = 33,
    BarcodeSymbologyGS1_128,
    BarcodeSymbologyISBT128,
    BarcodeSymbologyMicroPDF,
    BarcodeSymbologyGS1_DataBarOmni,
    BarcodeSymbologyGS1_DataBarLimited,
    BarcodeSymbologyGS1_DataBarExpanded,
    BarcodeSymbologyDataMatrix,
    BarcodeSymbologyQRCode,
    BarcodeSymbologyMaxicode,
    BarcodeSymbologyAztec = 0x4A,
    
    BarcodeSymbologyMaxIndex
}
BarcodeSymbology;
//! @}

//! @addtogroup barcode_settings
//!	@{
//! @enum BarcodeScanMode
//! @brief Supported scan modes.
//! @details Enumeration of the different barcode scan modes supported by the iSMP's barcode scanner.
typedef enum
{
    BarcodeScanModeSingleScan,
    BarcodeScanModeMultiScan
}
BarcodeScanMode;
//!	@}

//! @addtogroup barcode_settings
//!	@{
//! @enum BarcodeImagerMode
//! @brief Supported imager modes.
//! @details Enumeration of the different barcode imager modes supported by the iSMP's barcode scanner.
typedef enum
{
    BarcodeImagerMode1D,
    BarcodeImagerMode1D2D,
    BarcodeImagerMode1D2DBright,
    BarcodeImagerMode1D2DReflective
}
BarcodeImagerMode;
//! @}

//! @addtogroup barcode_settings
//!	@{
//! @enum BarcodeIlluminationMode
//! @brief Supported illumination modes.
//! @details Enumeration of the different barcode illumination modes supported by the iSMP's barcode scanner.
typedef enum
{
    BarcodeIlluminationModeAimerAndIlluminationLEDs,
    BarcodeIlluminationModeAimerOnly,
    BarcodeIlluminationModeIlluminationLEDsOnly,
    BarcodeIlluminationModeNoIllumination
}
BarcodeIlluminationMode;
//! @}

//! @addtogroup barcode_settings
//!	@{
//! @enum BarcodeLightingMode
//! @brief Supported lighting modes.
//! @details Enumeration of the different barcode lighting modes supported by the iSMP's barcode scanner.
typedef enum
{
    BarcodeLightingModeIlluminationLEDPriority,
    BarcodeLightingModeAperturePriority
}
BarcodeLightingMode;

typedef enum {
    BarCodeReader_PowerOnSuccess,             /**< The powerOn command was successful */
    BarCodeReader_PowerOnFailed,              /**< The powerOn command failed due to a synchronization problem */
    BarCodeReader_PowerOnDenied               /**< The powerOn command was forbidden. This happens when the device is charging on the craddle */
}
Barcode_PowerOnStatus;
//! @}

@interface iSMPBarCodeReaderManager : NSObject

+ (iSMPBarCodeReaderManager *)sharedManager;

// Power ON/OFF the barcode scanner
- (Barcode_PowerOnStatus)powerOn;
- (void)powerOff;

// Scan data
-(void) startScan;
-(void) stopScan;


// Configuration of the barcode scanner
- (void)configureSymbologies:(NSArray *)symbologies;
- (void)configureScanMode:(BarcodeScanMode)scanMode;
- (void)configureImagerMode:(BarcodeImagerMode)imagerMode;
- (void)configureIlluminationMode:(BarcodeIlluminationMode)illuminationMode;
- (void)configureLightingMode:(BarcodeLightingMode)lightingMode;

// Enable/Disable the beep capability
- (void)enableBeep:(BOOL)enable;
- (void)beep;

@end
