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
*  \file defMSP430USB.h
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
|  Source: defMSP430USB.h, v1.18 2009/06/11                                   |
|  Author: RSTO                                                               |
|                                                                             |
|  Description:                                                               |
|  Contains USB Constants, Type Definitions & Macros                          |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
+----------------------------------------------------------------------------*/

#ifndef _defMSP430USB_H
#define _defMSP430USB_H

/*----------------------------------------------------------------------------+
| Constant Definitions                                                        |
+----------------------------------------------------------------------------*/
#define YES         1
#define NO          0

#define TRUE        1
#define FALSE       0

#define NOERR       0
#define ERR         1

#define NO_ERROR    0
#define ERROR       1

#define DISABLE     0
#define ENABLE      1


/*----------------------------------------------------------------------------+
| USB Constants, Type Definition & Macro                                      |
+----------------------------------------------------------------------------*/

// USB related Constant
#define MAX_ENDPOINT_NUMBER     0x07    // A maximum of 7 endpoints is available
#define EP0_MAX_PACKET_SIZE     0x08
#define EP0_PACKET_SIZE         0x08
#define EP_MAX_PACKET_SIZE      0x40

// Base addresses of transmit and receive buffers
#define OEP1_X_BUFFER_ADDRESS   0x1C00  // Input  Endpoint 1 X Buffer Base-address
#define OEP1_Y_BUFFER_ADDRESS   0x1C40  // Input  Endpoint 1 Y Buffer Base-address
#define IEP1_X_BUFFER_ADDRESS   0x1C80  // Output Endpoint 1 X Buffer Base-address
#define IEP1_Y_BUFFER_ADDRESS   0x1CC0  // Output Endpoint 1 Y Buffer Base-address

#define OEP2_X_BUFFER_ADDRESS   0x1D00  // Input  Endpoint 2 X Buffer Base-address
#define OEP2_Y_BUFFER_ADDRESS   0x1D40  // Input  Endpoint 2 Y Buffer Base-address
#define IEP2_X_BUFFER_ADDRESS   0x1D80  // Output Endpoint 2 X Buffer Base-address
#define IEP2_Y_BUFFER_ADDRESS   0x1DC0  // Output Endpoint 2 Y Buffer Base-address

#define OEP3_X_BUFFER_ADDRESS   0x1E00  // Input  Endpoint 2 X Buffer Base-address
#define OEP3_Y_BUFFER_ADDRESS   0x1E40  // Input  Endpoint 2 Y Buffer Base-address
#define IEP3_X_BUFFER_ADDRESS   0x1E80  // Output Endpoint 2 X Buffer Base-address
#define IEP3_Y_BUFFER_ADDRESS   0x1EC0  // Output Endpoint 2 Y Buffer Base-address

#define OEP4_X_BUFFER_ADDRESS   0x1F00  // Input  Endpoint 2 X Buffer Base-address
#define OEP4_Y_BUFFER_ADDRESS   0x1F40  // Input  Endpoint 2 Y Buffer Base-address
#define IEP4_X_BUFFER_ADDRESS   0x1F80  // Output Endpoint 2 X Buffer Base-address
#define IEP4_Y_BUFFER_ADDRESS   0x1FC0  // Output Endpoint 2 Y Buffer Base-address

#define OEP5_X_BUFFER_ADDRESS   0x2000  // Input  Endpoint 2 X Buffer Base-address
#define OEP5_Y_BUFFER_ADDRESS   0x2040  // Input  Endpoint 2 Y Buffer Base-address
#define IEP5_X_BUFFER_ADDRESS   0x2080  // Output Endpoint 2 X Buffer Base-address
#define IEP5_Y_BUFFER_ADDRESS   0x20C0  // Output Endpoint 2 Y Buffer Base-address

#define OEP6_X_BUFFER_ADDRESS   0x2100  // Input  Endpoint 2 X Buffer Base-address
#define OEP6_Y_BUFFER_ADDRESS   0x2140  // Input  Endpoint 2 Y Buffer Base-address
#define IEP6_X_BUFFER_ADDRESS   0x2180  // Output Endpoint 2 X Buffer Base-address
#define IEP6_Y_BUFFER_ADDRESS   0x21C0  // Output Endpoint 2 Y Buffer Base-address

#define OEP7_X_BUFFER_ADDRESS   0x2200  // Input  Endpoint 2 X Buffer Base-address
#define OEP7_Y_BUFFER_ADDRESS   0x2240  // Input  Endpoint 2 Y Buffer Base-address
#define IEP7_X_BUFFER_ADDRESS   0x2280  // Output Endpoint 2 X Buffer Base-address
#define IEP7_Y_BUFFER_ADDRESS   0x22C0  // Output Endpoint 2 Y Buffer Base-address

#define X_BUFFER 0
#define Y_BUFFER 1

// addresses of pipes for endpoints
#define EP1_ADDR          0x01    //address for endpoint 1
#define EP2_ADDR          0x02    //address for endpoint 2
#define EP3_ADDR          0x03    //address for endpoint 3
#define EP4_ADDR          0x04    //address for endpoint 4
#define EP5_ADDR          0x05    //address for endpoint 5
#define EP6_ADDR          0x06    //address for endpoint 6
#define EP7_ADDR          0x07    //address for endpoint 7

// EDB Data Structure
typedef struct _tEDB
{
    BYTE    bEPCNF;             // Endpoint Configuration
    BYTE    bEPBBAX;            // Endpoint X Buffer Base Address
    BYTE    bEPBCTX;            // Endpoint X Buffer byte Count
    BYTE    bSPARE0;            // no used
    BYTE    bSPARE1;            // no used
    BYTE    bEPBBAY;            // Endpoint Y Buffer Base Address
    BYTE    bEPBCTY;            // Endpoint Y Buffer byte Count
    BYTE    bEPSIZXY;           // Endpoint XY Buffer Size
} tEDB, *tpEDB;

typedef struct _tEDB0
{
    BYTE    bIEPCNFG;           // Input Endpoint 0 Configuration Register
    BYTE    bIEPBCNT;           // Input Endpoint 0 Buffer Byte Count
    BYTE    bOEPCNFG;           // Output Endpoint 0 Configuration Register
    BYTE    bOEPBCNT;           // Output Endpoint 0 Buffer Byte Count
} tEDB0, *tpEDB0;

// EndPoint Desciptor Block Bits
#define EPCNF_USBIE     0x04    // USB Interrupt on Transaction Completion. Set By MCU
                                // 0:No Interrupt, 1:Interrupt on completion
#define EPCNF_STALL     0x08    // USB Stall Condition Indication. Set by UBM
                                // 0: No Stall, 1:USB Install Condition
#define EPCNF_DBUF      0x10    // Double Buffer Enable. Set by MCU
                                // 0: Primary Buffer Only(x-buffer only), 1:Toggle Bit Selects Buffer

#define EPCNF_TOGGLE     0x20   // USB Toggle bit. This bit reflects the toggle sequence bit of DATA0 and DATA1.

#define EPCNF_UBME      0x80    // UBM Enable or Disable bit. Set or Clear by MCU.
                                // 0:UBM can't use this endpoint
                                // 1:UBM can use this endpoint
#define EPBCNT_BYTECNT_MASK 0x7F // MASK for Buffer Byte Count
#define EPBCNT_NAK       0x80    // NAK, 0:No Valid in buffer, 1:Valid packet in buffer

//definitions for MSP430 USB-module
#define START_OF_USB_BUFFER   0x1C00

// input and output buffers for EP0
#define USBIEP0BUF 0x2378
#define USBOEP0BUF 0x2370


#endif    /*_defMSP430USB_H    */
