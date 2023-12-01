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
*  \file usb_eventHandling.c
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
|  Source: usb_eventHandling.c, v1.18 2009/06/11                              |
|  Author: RSTO                                                               |
|                                                                             |
|  Description:                                                               |
|  Event-handling placeholder functions.                                      |
|  All functios are called in interrupt context.                              |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2008/12/23   enhancements of CDC API                          |
|  RSTO         2009/11/06   added USB_handleEnumCompleteEvent()              |
+----------------------------------------------------------------------------*/

#include "MSP430.h"
#include "..\Common\types.h"            // Basic Type declarations
#include "..\USB_Common\defMSP430USB.h"
#include "descriptors.h"
#include "usb.h"                        // USB-specific Data Structures

// These variables are only example, they are not needed for stack
extern volatile BYTE bDataReceived_event;          // data received event
extern volatile BYTE bDataReceiveCompleted_event;  // data receive completed event
extern volatile BYTE bDataSendCompleted_event;     // data send completed event

/*
If this function gets executed, it's a sign that the output of the USB PLL has failed.
returns TRUE to keep CPU awake
*/
BYTE USB_handleClockEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
If this function gets executed, it indicates that a valid voltage has just been applied to the VBUS pin.
returns TRUE to keep CPU awake
*/
BYTE USB_handleVbusOnEvent()
{
    //TO DO: You can place your code here

    //We switch on USB and connect to the BUS
    if (USB_enable() == kUSB_succeed)
    {
        USB_reset();
        USB_connect();  // generate rising edge on DP -> the host enumerates our device as full speed device
    }
    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
If this function gets executed, it indicates that a valid voltage has just been removed from the VBUS pin.
returns TRUE to keep CPU awake
*/
BYTE USB_handleVbusOffEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
If this function gets executed, it indicates that the USB host has issued a USB reset event to the device.
returns TRUE to keep CPU awake
*/
BYTE USB_handleResetEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
If this function gets executed, it indicates that the USB host has chosen to suspend this device after a period of active operation.
returns TRUE to keep CPU awake
*/
BYTE USB_handleSuspendEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
If this function gets executed, it indicates that the USB host has chosen to resume this device after a period of suspended operation.
returns TRUE to keep CPU awake
*/
BYTE USB_handleResumeEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return TRUE to wake up after interrupt
}

/*
If this function gets executed, it indicates that the USB host has enumerated this device :
after host assigned the address to the device. 
returns TRUE to keep CPU awake
*/
BYTE USB_handleEnumCompleteEvent()
{
    //TO DO: You can place your code here

    return TRUE;   //return TRUE to wake up after interrupt
}


#ifdef _CDC_

/*
This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleDataReceived(BYTE intfNum)
{
    //TO DO: You can place your code here

    bDataReceived_event = TRUE;     // data received event

    return TRUE;   //return TURE to wake up after data was received
}

/*
This event indicates that a send operation on interface intfNum has just been completed.
returns TRUE to keep CPU awake
*/
BYTE USBCDC_handleSendCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    bDataSendCompleted_event = TRUE;

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

/*
This event indicates that a receive operation on interface intfNum has just been completed.
*/
BYTE USBCDC_handleReceiveCompleted(BYTE intfNum)
{
    //TO DO: You can place your code here

    bDataReceiveCompleted_event = TRUE; // data received event

    return TRUE;   //return FALSE to go asleep after interrupt (in the case the CPU slept before interrupt)
}

#endif // _CDC_



/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
