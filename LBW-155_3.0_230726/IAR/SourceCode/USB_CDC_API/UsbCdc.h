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
//
//This software has been submitted to export control regulations
//The ECCN is EAR99 
/**
*  \file UsbCdc.h
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
|                          MSP430 USB-Example (CDC Driver)                    |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: UsbCdc.h, v1.18 2009/06/11                                         |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2008/12/23   enhancements of CDC API                          |
|  RSTO         2009/05/15   added param to USBCDC_rejectData()               |
|  RSTO         2009/05/26   added USBCDC_bytesInUSBBuffer()                  |
+----------------------------------------------------------------------------*/

#ifndef _UsbCdc_H_
#define _UsbCdc_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define kUSBCDC_sendStarted         0x01
#define kUSBCDC_sendComplete        0x02
#define kUSBCDC_intfBusyError       0x03
#define kUSBCDC_receiveStarted      0x04
#define kUSBCDC_receiveCompleted    0x05
#define kUSBCDC_receiveInProgress   0x06
#define kUSBCDC_generalError        0x07
#define kUSBCDC_busNotAvailable     0x08



/*----------------------------------------------------------------------------
These functions can be used in application
+----------------------------------------------------------------------------*/

/*
Sends data over interface intfNum, of size size and starting at address data.
  Returns:  kUSBCDC_sendStarted
            kUSBCDC_sendComplete
            kUSBCDC_intfBusyError
*/
BYTE USBCDC_sendData(const BYTE* data, WORD size, BYTE intfNum);

/*
Receives data over interface intfNum, of size size, into memory starting at address data.
*/
BYTE USBCDC_receiveData(BYTE* data, WORD size, BYTE intfNum);

/*
Aborts an active receive operation on interface intfNum.
  size: the number of bytes that were received and transferred
  to the data location established for this receive operation.
*/
BYTE USBCDC_abortReceive(WORD* size, BYTE intfNum);


#define kUSBCDC_noDataWaiting 1 //returned by USBCDC_rejectData() if no data pending

/*
This function rejects payload data that has been received from the host.
*/
BYTE USBCDC_rejectData(BYTE intfNum);

/*
Aborts an active send operation on interface intfNum.  Returns the number of bytes that were sent prior to the abort, in size.
*/
BYTE USBCDC_abortSend(WORD* size, BYTE intfNum);


#define kUSBCDC_waitingForSend      0x01
#define kUSBCDC_waitingForReceive   0x02
#define kUSBCDC_dataWaiting         0x04
#define kUSBCDC_busNotAvailable     0x08
/*
This function indicates the status of the interface intfNum.
  If a send operation is active for this interface,
  the function also returns the number of bytes that have been transmitted to the host.
  If a receiver operation is active for this interface, the function also returns
  the number of bytes that have been received from the host and are waiting at the assigned address.

returns kUSBCDC_waitingForSend (indicates that a call to USBCDC_SendData()
  has been made, for which data transfer has not been completed)

returns kUSBCDC_waitingForReceive (indicates that a receive operation
  has been initiated, but not all data has yet been received)

returns kUSBCDC_dataWaiting (indicates that data has been received
  from the host, waiting in the USB receive buffers)
*/
BYTE USBCDC_intfStatus(BYTE intfNum, WORD* bytesSent, WORD* bytesReceived);

/*
Returns how many bytes are in the buffer are received and ready to be read.
*/
BYTE USBCDC_bytesInUSBBuffer(BYTE intfNum);


/*----------------------------------------------------------------------------
Event-Handling routines
+----------------------------------------------------------------------------*/

/*
This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleDataReceived(BYTE intfNum);

/*
This event indicates that a send operation on interface intfNum has just been completed.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleSendCompleted(BYTE intfNum);

/*
This event indicates that a receive operation on interface intfNum has just been completed.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleReceiveCompleted(BYTE intfNum);


/*----------------------------------------------------------------------------
These functions is to be used ONLY by USB stack, and not by application
+----------------------------------------------------------------------------*/

/**
Send a packet with the settings of the second uart back to the usb host
*/
VOID usbGetLineCoding(VOID);

/**
Prepare EP0 to receive a packet with the settings for the second uart
*/
VOID usbSetLineCoding(VOID);

/**
Function set or reset RTS
*/
VOID usbSetControlLineState(VOID);

/**
Readout the settings (send from usb host) for the second uart
*/
VOID Handler_SetLineCoding(VOID);


#ifdef __cplusplus
}
#endif
#endif //_UsbCdc_H_
