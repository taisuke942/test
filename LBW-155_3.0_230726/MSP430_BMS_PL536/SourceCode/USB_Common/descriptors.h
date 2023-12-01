//******************************************************************************
//THIS PROGRAM IS PROVIDED "AS IS". TI MAKES NO WARRANTIES OR
//REPRESENTATIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
//INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
//COMPLETENESS OF RESPONSES, RESULTS AND LACK OF NEGLIGENCE.
//TI DISCLAIMS ANY WARRANTY OF TITLE, QUIET ENJOYMENT, QUIET
//POSSESSION, AND NON-INFRINGEMENT OF ANY THIRD PARTY
//INTELLECTUAL PROPERTY RIGHTS WITH REGARD TO THE PROGRAM OR
//YOUR USE OF THE PROGRAM.
//
//IN NO EVENT SHALL TI BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
//CONSEQUENTIAL OR INDIRECT DAMAGES, HOWEVER CAUSED, ON ANY
//THEORY OF LIABILITY AND WHETHER OR NOT TI HAS BEEN ADVISED
//OF THE POSSIBILITY OF SUCH DAMAGES, ARISING IN ANY WAY OUT
//OF THIS AGREEMENT, THE PROGRAM, OR YOUR USE OF THE PROGRAM.
//EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF
//REMOVAL OR REINSTALLATION, COMPUTER TIME, LABOR COSTS, LOSS
//OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF
//USE OR INTERRUPTION OF BUSINESS. IN NO EVENT WILL TI'S
//AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF
//YOUR USE OF THE PROGRAM EXCEED FIVE HUNDRED DOLLARS
//(U.S.$500).
//
//Unless otherwise stated, the Program written and copyrighted
//by Texas Instruments is distributed as "freeware".  You may,
//only under TI's copyright in the Program, use and modify the
//Program without any charge or restriction.  You may
//distribute to third parties, provided that you transfer a
//copy of this license to the third party and the third party
//agrees to these terms by its first use of the Program. You
//must reproduce the copyright notice and any other legend of
//ownership on each copy or partial copy, of the Program.
//
//You acknowledge and agree that the Program contains
//copyrighted material, trade secrets and other TI proprietary
//information and is protected by copyright laws,
//international copyright treaties, and trade secret laws, as
//well as other intellectual property laws.  To protect TI's
//rights in the Program, you agree not to decompile, reverse
//engineer, disassemble or otherwise translate any object code
//versions of the Program to a human-readable form.  You agree
//that in no event will you alter, remove or destroy any
//copyright notice included in the Program.  TI reserves all
//rights not specifically granted under this license. Except
//as specifically provided herein, nothing in this agreement
//shall be construed as conferring by implication, estoppel,
//or otherwise, upon you, any license or other right under any
//TI patents, copyrights or trade secrets.
// 
//You may not use the Program in non-TI devices.
/**
*  \file descriptors.h
*  \author Texas Instruments, Inc
*  \brief For more information on this file please refer to 
*   Programmer�s Guide: MSP430 USB API Stack for CDC/HID
*  http://focus.ti.com/docs/prod/folders/print/msp430f5529.html#toolssoftware.
*  \date 2009/06/11 
*  \version 1.18 Initial Release
*  \note Built with IAR Embedded Workbench for MSP430 Version: 5.10.1
*/

// (c)2009 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: descriptors.h, v1.19 2009/11/18                                    |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2008/11/29   Added global USB constants                       |
|  RSTO         2008/12/23   enhancements of CDC API                          |
|  RSTO         2009/05/25   put all config constants into this file          |
|  RSTO         2009/07/17   Added comment for MCLK                           |
|  RSTO         2009/11/18   Changed FW version to 1.19					      |
+----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------+
| Include files                                                               |
+----------------------------------------------------------------------------*/
#include "..\Common\types.h"

//***********************************************************************************************
// CDC or HID
//***********************************************************************************************
#define _CDC_          // Needed for CDC inteface


//***********************************************************************************************
// CONFIGURATION CONSTANTS
//***********************************************************************************************

// These constants configure the API stack and help define the USB descriptors.
// Refer to Sec. 6 of the MSP430 USB CDC API Programmer's Guide for descriptions of these constants.

#define USB_VID 0x2047         // Vendor ID, 0x2047 for Texas Instruments Incorporated (MSP430 Group)

#ifdef _CDC_
    #define USB_PID                         0x0300 // Product ID (PID), 0xF400 for CDC stack
    #define SIZEOF_CONFIGURATION_DESCRIPTOR     53 // wTotalLength, CDC
    #define INTERFACE_NUMBER_CDC                0
    #define CDC_INTEP_ADDR                      0x82
    #define CDC_OUTEP_ADDR                      0x03
    #define CDC_INEP_ADDR                       0x83

    #ifdef _HID_
      #error Only ONE of interfaces should be defined: _HID_ or _CDC_!
    #endif
#else
    #ifdef _HID_
        #define USB_PID                     0x0301 // Product ID (PID), 0xF401 for HID stack
        #define SIZEOF_CONFIGURATION_DESCRIPTOR 41 // wTotalLength, HID
        #define START_HID_DESCRIPTOR            18
        #define INTERFACE_NUMBER_HID            0
        #define HID_OUTEP_ADDR                0x01
        #define HID_INEP_ADDR                 0x81
    #else
        #error No interface HID or CDC defined! Define it.
    #endif
#endif

/*----------------------------------------------------------------------------+
| Firmware Version                                                            |
| How to detect version number of the FW running on MSP430?                   |
| on Windows Open ControlPanel->Systems->Hardware->DeviceManager->Ports->     |
|         Msp430->ApplicationUART->Details                                    |
+----------------------------------------------------------------------------*/
#define VER_FW_H 0x01                       // Device release number -- high and low bytes, in binary-coded decimal
#define VER_FW_L 0x19                       // This is reported in the bcdDevice field of the device descriptor

// MCLK frequency of MCU, in Hz
// For running higher frequencies the Vcore voltage adjustment may required.
// Please refer to Data Sheet of the MSP430 device you use
#define USB_MCLK_FREQ 8000000               // MCLK frequency of MCU, in Hz

#define MAX_PACKET_SIZE   0x40              // Max size of the USB packets.


// If a serial number is to be reported, set this to the index within the string descriptor
// of the dummy serial number string.  It will then be automatically handled by the API.
// If no serial number is to be reported, set this to 0.
#define USB_STR_INDEX_SERNUM 3


#define USB_PLL_XT        2                 // Defines which XT is used by the PLL (1=XT1, 2=XT2)
#define USB_XT_FREQ       USBPLL_SETCLK_4_0 // Indicates the freq of the crystal on the oscillator indicated by USB_PLL_XT
#define USB_DISABLE_XT_SUSPEND 1            // If non-zero, then USB_suspend() will disable the oscillator
                                            // that is designated by USB_PLL_XT; if zero, USB_suspend won't
                                            // affect the oscillator

#define USB_SUPPORT_REM_WAKE     0x20       // If remote wakeup is to be supported, set this to 0x20.  If not, set to 0x00.
                                            // All other values are prohibited.

// Controls whether the device reports itself to be self-powered to any degree.  If so, set to 0x40.  If the
// device is fully supplied by the bus, set to 0x00.  All other values are prohibited.
#define USB_SUPPORT_SELF_POWERED 0x40


// Controls how much power the device reports it will draw from VBUS.  Expressed in 2mA units; that is, the
// number of mA communicated is twice the value of this field.
#define USB_MAX_POWER 0x32


#define USB_DMA_TX   0x1    // Set to 0xFF if no DMA channel will be used 0..7 for selected DMA channel
#define USB_DMA_RX   0x1    // Set to 0xFF if no DMA channel will be used 0..7 for selected DMA channel

#define USB_NUM_CONFIGURATIONS          1  // Number of implemented interfaces.  This is fixed to 1.


//***********************************************************************************************
// DESCRIPTOR CONSTANTS
//***********************************************************************************************
#define SIZEOF_DEVICE_DESCRIPTOR  0x12
#define SIZEOF_REPORT_DESCRIPTOR  36
#define USBHID_REPORT_LENGTH      64  // length of whole HID report (including Report ID)
#define SIZEOF_INTERFACE_DESCRIPTOR 0x09

#define CONFIG_STRING_INDEX       4
#define INTF_STRING_INDEX         5

//***********************************************************************************************
// OUTWARD DECLARATIONS
//***********************************************************************************************

//Calculates the endpoint descriptor block number from given address
#define EDB(addr) ((addr&0x07)-1)

extern BYTE const abromDeviceDescriptor[SIZEOF_DEVICE_DESCRIPTOR];
extern BYTE const abromConfigurationDescriptorGroup[SIZEOF_CONFIGURATION_DESCRIPTOR];
extern BYTE const abromReportDescriptor[SIZEOF_REPORT_DESCRIPTOR];
extern BYTE const abromStringDescriptor[];

/*------------------------ Nothing Below This Line --------------------------*/

