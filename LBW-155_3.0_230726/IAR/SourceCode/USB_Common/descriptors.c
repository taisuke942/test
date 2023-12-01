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
*  \file descriptors.c
*  \brief For more information on this file please refer to 
*   Programmer’s Guide: MSP430 USB API Stack for CDC/HID
*  http://focus.ti.com/docs/prod/folders/print/msp430f5529.html#toolssoftware.
*  \author Texas Instruments, Inc
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
|  Source: Descriptors.c, v1.18 2009/06/11                                    |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2008/12/23   enhancements of CDC API                          |
|  RSTO         2009/01/12   enhancements for USB serial number               |
|  RSTO         2009/03/01   added HID descriptors                            |
|  RSTO         2009/05/25   put all config constants into this file          |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Include files                                                               |
+----------------------------------------------------------------------------*/

#include "MSP430.h"
#include "..\Common\types.h"              // Basic Type declarations
#include "..\USB_Common\defMSP430USB.h"
#include "..\USB_Common\usb.h"            // USB-specific Data Structures
#include "..\USB_Common\descriptors.h"
#include "..\USB_CDC_API\UsbCdc.h"

/*----------------------------------------------------------------------------+
| Internal Type Definition & Macro                                            |
+----------------------------------------------------------------------------*/


BYTE const abromDeviceDescriptor[SIZEOF_DEVICE_DESCRIPTOR] = {
    SIZEOF_DEVICE_DESCRIPTOR,       // Length of this descriptor (12h bytes)
    DESC_TYPE_DEVICE,               // Type code of this descriptor (01h)
    0x00,0x02,                      // Release of USB spec (Rev 2.0)
    0x00,                           // Device's base class code
    0,                              // Device's sub class code
    0,                              // Device's protocol type code
    EP0_PACKET_SIZE,                // End point 0's packet size = 8
    USB_VID&0xFF, USB_VID>>8,       // Vendor ID for device, TI=0x0451
                                    //      this is Texas Instruments VID
                                    //      you can use is only in this example.
                                    //      You can order your own VID at www.usb.org
    USB_PID&0xFF, USB_PID>>8,       // Product ID for device,
                                    //      this ID is to only with this example
    VER_FW_L, VER_FW_H,             // Revision level of device, Rev=1.00
    1,                              // Index of manufacturer name string desc
    2,                              // Index of product name string desc
    USB_STR_INDEX_SERNUM,           // Index of serial number string desc
    1                               // Number of configurations supported
};



BYTE const abromConfigurationDescriptorGroup[] =
{
    // CONFIGURATION DESCRIPTOR (9 bytes)
    SIZEOF_CONFIG_DESCRIPTOR,       // bLength
    DESC_TYPE_CONFIG,               // bDescriptorType: 2
    SIZEOF_CONFIGURATION_DESCRIPTOR,0x00,  // wTotalLength
    USB_NUM_CONFIGURATIONS,         // bNumInterfaces
    0x01,                           // bConfigurationValue
    CONFIG_STRING_INDEX,            // iConfiguration Description offset
//    CFG_DESC_ATTR_BUS_POWERED | USB_SUPPORT_REM_WAKE,  // bmAttributes, bus power, remote wakeup
    CFG_DESC_ATTR_BUS_POWERED,      // Bus powered, does not support remote wake-up
    USB_MAX_POWER,                  // Max. Power Consumption at 2mA unit


  #ifdef _CDC_

    //-------- Descriptor for CDC class device -------------------------------------
    // INTERFACE DESCRIPTOR (9 bytes)
    0x09,	                    // bLength: Interface Descriptor size
    DESC_TYPE_INTERFACE,	    // bDescriptorType: Interface
    INTERFACE_NUMBER_CDC,       // bInterfaceNumber
    0x00,                       // bAlternateSetting: Alternate setting
    0x03,                       // bNumEndpoints: Three endpoints used
    0x02,                       // bInterfaceClass: Communication Interface Class
    0x02,                       // bInterfaceSubClass: Abstract Control Model
    0x01,                       // bInterfaceProtocol: Common AT commands
    INTF_STRING_INDEX,	        // iInterface:

    //Header Functional Descriptor
    0x05,	                    // bLength: Endpoint Descriptor size
    0x24,	                    // bDescriptorType: CS_INTERFACE
    0x00,	                    // bDescriptorSubtype: Header Func Desc
    0x10,	                    // bcdCDC: spec release number
    0x01,

    //Call Managment Functional Descriptor
    0x05,	                    // bFunctionLength
    0x24,	                    // bDescriptorType: CS_INTERFACE
    0x01,	                    // bDescriptorSubtype: Call Management Func Desc
    0x00,	                    // bmCapabilities: D0+D1
    INTERFACE_NUMBER_CDC,       // bDataInterface: 0

    //ACM Functional Descriptor
    0x04,	                    // bFunctionLength
    0x24,	                    // bDescriptorType: CS_INTERFACE
    0x02,	                    // bDescriptorSubtype: Abstract Control Management desc
    0x02,	                    // bmCapabilities


    // ENDPOINT #2 INPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength: Endpoint Descriptor size
    DESC_TYPE_ENDPOINT,	            // bDescriptorType: Endpoint
    CDC_INTEP_ADDR,	                // bEndpointAddress: (IN2)
    EP_DESC_ATTR_TYPE_INT,	        // bmAttributes: Interrupt
    0x40, 0x00,                     // wMaxPacketSize, 64 bytes
    0xFF,	                        // bInterval

    // ENDPOINT #3 OUTPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength: Endpoint Descriptor size
    DESC_TYPE_ENDPOINT,	            // bDescriptorType: Endpoint
    CDC_OUTEP_ADDR,	                // bEndpointAddress: (OUT3)
    EP_DESC_ATTR_TYPE_BULK,	        // bmAttributes: Bulk
    0x40, 0x00,                     // wMaxPacketSize, 64 bytes
    0xFF, 	                        // bInterval: ignored for Bulk transfer

    // ENDPOINT #3 INPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength: Endpoint Descriptor size
    DESC_TYPE_ENDPOINT,	            // bDescriptorType: Endpoint
    CDC_INEP_ADDR,	                // bEndpointAddress: (IN3)
    EP_DESC_ATTR_TYPE_BULK,	        // bmAttributes: Bulk
    0x40, 0x00,                     // wMaxPacketSize, 64 bytes
    0xFF, 	                        // bInterval: ignored for bulk transfer

  #endif // _CDC_


  #ifdef _HID_
    //-------- Descriptor for HID class device -------------------------------------
    // INTERFACE DESCRIPTOR (9 bytes)
    SIZEOF_INTERFACE_DESCRIPTOR,    // bLength
    DESC_TYPE_INTERFACE,            // bDescriptorType: 4
    INTERFACE_NUMBER_HID,           // bInterfaceNumber
    0x00,                           // bAlternateSetting
    2,                              // bNumEndpoints
    0x03,                           // bInterfaceClass: 3 = HID Device
    0,                              // bInterfaceSubClass:
    0,                              // bInterfaceProtocol:
    INTF_STRING_INDEX,              // iInterface:1

    // HID DESCRIPTOR (9 bytes)
    0x09,     			    // bLength of HID descriptor
    0x21,             		    // HID Descriptor Type: 0x21
    0x01,0x01,			    // HID Revision number 1.01
    0x00,			    // Target country, nothing specified (00h)
    0x01,			    // Number of HID classes to follow
    0x22,			    // Report descriptor type
    (SIZEOF_REPORT_DESCRIPTOR& 0x0ff),  // Total length of report descriptor
    (SIZEOF_REPORT_DESCRIPTOR >>8),

    // ENDPOINT #1 INPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength
    DESC_TYPE_ENDPOINT,             // bDescriptorType
    HID_INEP_ADDR,                 // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
    EP_DESC_ATTR_TYPE_INT,          // bmAttributes, interrupt transfers
    0x40, 0x00,                     // wMaxPacketSize, 64 bytes
    0x01,                           // bInterval, ms

    // ENDPOINT #1 OUTPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength
    DESC_TYPE_ENDPOINT,             // bDescriptorType
    HID_OUTEP_ADDR,                 // bEndpointAddress; bit7=1 for IN, bits 3-0=1 for ep1
    EP_DESC_ATTR_TYPE_INT,          // bmAttributes, interrupt transfers
    0x40, 0x00,                     // wMaxPacketSize, 64 bytes
    0x01,                           // bInterval, ms
  #endif // _HID_


};


BYTE const abromStringDescriptor[] = {
    // string index 0, language support
    4,                              // Length of language descriptor ID
    3,                              // LANGID tag
    0x09,0x04,                      // 0x0409 for English

    // string index 1, manufacture
    36,                             // Length of this string descriptor
    DESC_TYPE_STRING,
    'T',0x00,'e',0x00,'x',0x00,'a',0x00,'s',0x00,' ',0x00,
    'I',0x00,'n',0x00,'s',0x00,'t',0x00,'r',0x00,'u',0x00,
    'm',0x00,'e',0x00,'n',0x00,'t',0x00,'s',0x00,

    // string index 2, product
    38,                            // Length of this string descriptor
    DESC_TYPE_STRING,
    'M',0x00,'S',0x00,'P',0x00,'4',0x00,'3',0x00,'0',0x00,
    '-',0x00,'U',0x00,'S',0x00,'B',0x00,
    ' ',0x00,'E',0x00,'x',0x00,'a',0x00,'m',0x00,'p',0x00,
	'l',0x00,'e',0x00,

    // string index 3, serial (dummy index. real serial number will be stored in RAM)
    4,
    DESC_TYPE_STRING,
    '0',0x00,

    // string index 4, interface 0

    50-22,                        // Length of this string descriptor
    DESC_TYPE_STRING,
    'H',0x00,'I',0x00,'D',0x00,' ',0x00,'I',0x00,'n',0x00,
    't',0x00,'e',0x00,'r',0x00,'f',0x00,'a',0x00,'c',0x00,
    'e',0x00,
    /*'S',0x00,'e',0x00,'r',0x00,'i',0x00,'a',0x00,
	'l',0x00,' ',0x00,'p',0x00,'o',0x00,'r',0x00,'t',0x00, */

    // string index 5, interface 0

    46,                           // Length of this string descriptor
    DESC_TYPE_STRING,
    'V',0x00,'i',0x00,'r',0x00,'t',0x00,'u',0x00,'a',0x00,
    'l',0x00,' ',0x00,'C',0x00,'O',0x00,'M',0x00,' ',0x00,
    'p',0x00,'o',0x00,'r',0x00,'t',0x00,' ',0x00,'(',0x00,
	'C',0x00,'D',0x00,'C',0x00,')',0x00,
};


BYTE const abromReportDescriptor[SIZEOF_REPORT_DESCRIPTOR]=
{
    0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)

    0x85, 0x3F,                    //   Report ID
    0x95, 0x3F,                    //   REPORT_COUNT ()
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x25, 0x01,
    0x15, 0x01,
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)

    0x85, 0x3F,                    //   Report ID
    0x95, 0x3F,                    //   REPORT_COUNT ()
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x25, 0x01,
    0x15, 0x01,
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

    0xC0                           //   end Application Collection
};


/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
