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
*  \file UsbIsr.c
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
|  Source: UsbIsr.c, v1.18 2009/06/11                                         |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2008/12/23   enhancements of CDC API                          |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Include files                                                               |
+----------------------------------------------------------------------------*/

#include "MSP430.h"
#include "..\Common\types.h"              // Basic Type declarations
#include "..\USB_Common\defMSP430USB.h"
#include "..\USB_Common\descriptors.h"
#include "..\USB_Common\usb.h"            // USB-specific Data Structures
# ifdef _CDC_
    #include "..\USB_CDC_API\UsbCdc.h"
#endif

#include "UsbIsr.h"
#include <string.h>

/*----------------------------------------------------------------------------+
| External Variables                                                          |
+----------------------------------------------------------------------------*/
extern BYTE  bFunctionSuspended;

extern __no_init tEDB0 __data16 tEndPoint0DescriptorBlock;
extern __no_init tEDB __data16 tInputEndPointDescriptorBlock[];
extern __no_init tEDB __data16 tOutputEndPointDescriptorBlock[];

extern volatile BYTE bHostAsksUSBData;
extern volatile BYTE bTransferInProgress;
extern volatile BYTE bSecondUartTxDataCounter[];
extern volatile PBYTE pbSecondUartTxData;

extern BYTE bStatusAction;
extern WORD wUsbEventMask;

BOOL CdcToHostFromBuffer();
BOOL CdcToBufferFromHost();
BOOL CdcIsReceiveInProgress();

BOOL HidToHostFromBuffer();
BOOL HidToBufferFromHost();
BOOL HidIsReceiveInProgress();

extern unsigned char TEST;
/*----------------------------------------------------------------------------+
| General Subroutines                                                         |
+----------------------------------------------------------------------------*/

#pragma vector=USB_UBM_VECTOR
__interrupt VOID iUsbInterruptHandler(VOID)
{
    BYTE bWakeUp = FALSE;
  
    //Check if the setup interrupt is pending. 
    //We need to check it before other interrupts, 
    //to work around that the Setup Int has lower priority then Input Endpoint 0
    if (USBIFG & SETUPIFG)
    {
        bWakeUp = SetupPacketInterruptHandler();  
        USBIFG &= ~SETUPIFG;    // clear the interrupt bit
    }   
    
    switch (__even_in_range(USBVECINT & 0x3f, USBVECINT_OUTPUT_ENDPOINT7))
    {
      case USBVECINT_NONE:
        break;
      case USBVECINT_PWR_DROP:
        __no_operation();
        break;
      case USBVECINT_PLL_LOCK:
        break;
      case USBVECINT_PLL_SIGNAL:
        break;
      case USBVECINT_PLL_RANGE:
        if (wUsbEventMask & kUSB_clockFaultEvent)
        {
            bWakeUp = USB_handleClockEvent();
        }
        break;
      case USBVECINT_PWR_VBUSOn:
        PWRVBUSonHandler();
        if (wUsbEventMask & kUSB_VbusOnEvent)
        {
            bWakeUp = USB_handleVbusOnEvent();
        }
        break;
      case USBVECINT_PWR_VBUSOff:
        PWRVBUSoffHandler();
        if (wUsbEventMask & kUSB_VbusOffEvent)
        {
            bWakeUp = USB_handleVbusOffEvent();
        }
        break;
      case USBVECINT_USB_TIMESTAMP:
        break;
      case USBVECINT_INPUT_ENDPOINT0:
        IEP0InterruptHandler();
        break;
      case USBVECINT_OUTPUT_ENDPOINT0:
        OEP0InterruptHandler();
        break;
      case USBVECINT_RSTR:
        USB_reset();
        if (wUsbEventMask & kUSB_UsbResetEvent)
        {
            bWakeUp = USB_handleResetEvent();
        }
        break;
      case USBVECINT_SUSR:
        USB_suspend();
        if (wUsbEventMask & kUSB_UsbSuspendEvent)
        {
            bWakeUp = USB_handleSuspendEvent();
        }
        break;
      case USBVECINT_RESR:
        USB_resume();
        if (wUsbEventMask & kUSB_UsbResumeEvent)
        {
            bWakeUp = USB_handleResumeEvent();
        }
        //-- after resume we will wake up! Independ what event handler says.
        bWakeUp = TRUE;
  
        break;
      case USBVECINT_SETUP_PACKET_RECEIVED: 
        bWakeUp = SetupPacketInterruptHandler();
        break;
  
      case USBVECINT_STPOW_PACKET_RECEIVED:
        break;
  
      case USBVECINT_INPUT_ENDPOINT1:

          break;
  
      case USBVECINT_INPUT_ENDPOINT2:
        break;
  
      case USBVECINT_INPUT_ENDPOINT3:
        #ifdef _CDC_
            //send saved bytes from buffer...
            bWakeUp = CdcToHostFromBuffer();
        #endif
        break;
  
      case USBVECINT_INPUT_ENDPOINT4:
        break;
      case USBVECINT_INPUT_ENDPOINT5:
        break;
      case USBVECINT_INPUT_ENDPOINT6:
        break;
      case USBVECINT_INPUT_ENDPOINT7:
        break;
  
      case USBVECINT_OUTPUT_ENDPOINT1:
        
        break;
  
      case USBVECINT_OUTPUT_ENDPOINT2:
        break;
  
      case USBVECINT_OUTPUT_ENDPOINT3:
        #ifdef _CDC_
            //call callback function if no receive operation is underway
            if (!CdcIsReceiveInProgress())
            {
                if (wUsbEventMask & kUSB_dataReceivedEvent)
                {
                    bWakeUp = USBCDC_handleDataReceived(1);
                }
            }
            else
            {
                //complete receive opereation - copy data to user buffer
                bWakeUp = CdcToBufferFromHost();
            }
            TEST++;
        #endif
            break;
  
      case USBVECINT_OUTPUT_ENDPOINT4:
            break;
      case USBVECINT_OUTPUT_ENDPOINT5:
        break;
      case USBVECINT_OUTPUT_ENDPOINT6:
        break;
      case USBVECINT_OUTPUT_ENDPOINT7:
        break;
      default:
        break;
    }
   
    if (bWakeUp)
    {
        __bic_SR_register_on_exit(LPM3_bits); // Exit LPM0-3
    }
}

/*----------------------------------------------------------------------------+
| Interrupt Sub-routines                                                      |
+----------------------------------------------------------------------------*/

BYTE SetupPacketInterruptHandler(VOID)
{
    BYTE bTemp;
    BYTE bWakeUp = FALSE;

    USBCTL |= FRSTE;      // Function Reset Connection Enable - set enable after first setup packet was received

    usbProcessNewSetupPacket:

    // copy the MSB of bmRequestType to DIR bit of USBCTL
    if((tSetupPacket.bmRequestType & USB_REQ_TYPE_INPUT) == USB_REQ_TYPE_INPUT)
    {
        USBCTL |= DIR;
    }
    else
    {
        USBCTL &= ~DIR;
    }

    bStatusAction = STATUS_ACTION_NOTHING;

    // clear out return data buffer
    for(bTemp=0; bTemp<USB_RETURN_DATA_LENGTH; bTemp++)
    {
        abUsbRequestReturnData[bTemp] = 0x00;
    }

    // decode and process the request
    bWakeUp = usbDecodeAndProcessUsbRequest();

    // check if there is another setup packet pending
    // if it is, abandon current one by NAKing both data endpoint 0
    if((USBIFG & STPOWIFG) != 0x00)
    {
        USBIFG &= ~(STPOWIFG | SETUPIFG);
        goto usbProcessNewSetupPacket;
    }
    return bWakeUp;
}

//----------------------------------------------------------------------------
VOID PWRVBUSoffHandler(VOID)
{
    volatile unsigned int i;
    for (i =0; i < 1000; i++);
    if (!(USBPWRCTL & USBBGVBV))
    {
        USBKEYPID   =    0x9628;        // set KEY and PID to 0x9628 -> access to configuration registers enabled
        bEnumerationStatus = 0x00;      // device is not enumerated
        bFunctionSuspended = FALSE;     // device is not suspended
        USBCNF     =    0;              // disable USB module
        USBPLLCTL  &=  ~UPLLEN;         // disable PLL
        USBPWRCTL &= ~(VBOFFIE + VBOFFIFG);          // disable interrupt VBUSoff
        USBKEYPID   =    0x9600;        // access to configuration registers disabled
    }
}

//----------------------------------------------------------------------------

VOID PWRVBUSonHandler(VOID)
{
    volatile unsigned int i;
    for (i =0; i < 1000; i++);          // waiting till voltage will be stable

    USBKEYPID =  0x9628;                // set KEY and PID to 0x9628 -> access to configuration registers enabled
    USBPWRCTL |= VBOFFIE;               // enable interrupt VBUSoff
    USBPWRCTL &= ~ (VBONIFG + VBOFFIFG);             // clean int flag (bouncing)
    USBKEYPID =  0x9600;                // access to configuration registers disabled
}

//----------------------------------------------------------------------------
VOID IEP0InterruptHandler(VOID)
{
    USBCTL |= FRSTE;                              // Function Reset Connection Enable
    tEndPoint0DescriptorBlock.bOEPBCNT = 0x00;     

    if(bStatusAction == STATUS_ACTION_DATA_IN)
    {
        usbSendNextPacketOnIEP0();
    }
    else
    {
        tEndPoint0DescriptorBlock.bIEPCNFG |= EPCNF_STALL; // no more data
    }
}

//----------------------------------------------------------------------------
VOID OEP0InterruptHandler(VOID)
{
    USBCTL |= FRSTE;                              // Function Reset Connection Enable
    tEndPoint0DescriptorBlock.bIEPBCNT = 0x00;    

    if(bStatusAction == STATUS_ACTION_DATA_OUT)
    {
        usbReceiveNextPacketOnOEP0();
        if(bStatusAction == STATUS_ACTION_NOTHING)
        {
            switch(tSetupPacket.bRequest)
            {
            #ifdef _CDC_
                case USB_CDC_SET_LINE_CODING:
                    Handler_SetLineCoding();
                    break;
            #endif // _CDC_
            default:;
            }
        }
    }
    else
    {
        tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_STALL; // no more data
    }
}

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
