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
*  \file dma.c
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
|                          MSP430 USB-Example (HID/CDC Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: dma.c, v1.18 2009/06/11                                           |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2009/03/03   born                                             |
|  RSTO         2009/04/08   Redefine memcpy()                                |
|  RSTO         2009/04/16   use 16 bit access to DMA regs                    |
|  RSTO         2009/09/18   fixed trigger selection for DMA with bit set     |
|  RSTO         2009/11/03   do not transfer via DMA if length is zero        |
+----------------------------------------------------------------------------*/

#include "MSP430.h"
#include "..\Common\types.h"              // Basic Type declarations
#include "..\USB_Common\defMSP430USB.h"
#include "..\USB_Common\descriptors.h"
#include <string.h>


//function pointers
VOID *(*USB_TX_memcpy)(VOID * dest, const VOID * source, size_t count);
VOID *(*USB_RX_memcpy)(VOID * dest, const VOID * source, size_t count);

VOID * memcpyDMA0(VOID * dest, const VOID * source, size_t count);
VOID * memcpyDMA1(VOID * dest, const VOID * source, size_t count);
VOID * memcpyDMA2(VOID * dest, const VOID * source, size_t count);

// NOTE: this functin works only with data in the area <64k (small memory model)
VOID * memcpyV(VOID * dest, const VOID * source, size_t count)
{
    WORD i;
    volatile BYTE bTmp;
    for (i=0; i<count; i++)
    {
        bTmp = *((BYTE*)source +i);
        *((BYTE*)dest  +i) = bTmp;
    }
    return dest;
}


//this function inits the
VOID USB_initMemcpy(VOID)
{
    USB_TX_memcpy = memcpyV;
    USB_RX_memcpy = memcpyV;

    switch (USB_DMA_TX)
    {
    case 0:
        DMACTL0 &= ~DMA0TSEL_31;         // DMA0 is triggered by DMAREQ
        DMACTL0 |= DMA0TSEL_0;           // DMA0 is triggered by DMAREQ
        DMA0CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                  // and destination address
        DMACTL4 |= ENNMI;               // enable NMI interrupt
        USB_TX_memcpy = memcpyDMA0;
        break;
    case 1:
        DMACTL0 &= ~DMA1TSEL_31;         // DMA1 is triggered by DMAREQ
        DMACTL0 |= DMA1TSEL_0;           // DMA1 is triggered by DMAREQ
        DMA1CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                  // and destination address
        DMACTL4 |= ENNMI;               // enable NMI interrupt
        USB_TX_memcpy = memcpyDMA1;
        break;
    case 2:
       DMACTL0 &= ~DMA2TSEL_31;         // DMA2 is triggered by DMAREQ
       DMACTL0 |= DMA2TSEL_0;           // DMA2 is triggered by DMAREQ
       DMA2CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                 // and destination address
       DMACTL4 |= ENNMI;               // enable NMI interrupt
       USB_TX_memcpy = memcpyDMA2;
       break;
    }

   switch (USB_DMA_RX)
    {
    case 0:
        DMACTL0 &= ~DMA0TSEL_31;         // DMA0 is triggered by DMAREQ
        DMACTL0 |= DMA0TSEL_0;           // DMA0 is triggered by DMAREQ
        DMA0CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                  // and destination address
        DMACTL4 |= ENNMI;               // enable NMI interrupt
        USB_RX_memcpy = memcpyDMA0;
        break;
    case 1:
        DMACTL0 &= ~DMA1TSEL_31;         // DMA1 is triggered by DMAREQ
        DMACTL0 |= DMA1TSEL_0;           // DMA1 is triggered by DMAREQ
        DMA1CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                  // and destination address
        DMACTL4 |= ENNMI;               // enable NMI interrupt
        USB_RX_memcpy = memcpyDMA1;
        break;
    case 2:
       DMACTL0 &= ~DMA2TSEL_31;         // DMA2 is triggered by DMAREQ
       DMACTL0 |= DMA2TSEL_0;           // DMA2 is triggered by DMAREQ
       DMA2CTL = (DMADT_1 + DMASBDB + DMASRCINCR_3 +   // configure block transfer (byte-wise) with increasing source
                       DMADSTINCR_3 );                 // and destination address
       DMACTL4 |= ENNMI;               // enable NMI interrupt
       USB_RX_memcpy = memcpyDMA2;
       break;
    }
}

// this functions starts DMA transfer to/from USB memory into/from RAM
// Using DMA0
// Support only for data in <64k memory area.
VOID * memcpyDMA0(VOID * dest, const VOID *  source, size_t count)
{
    if (count == 0)         // do nothing if zero bytes to transfer
    {
        return dest;
    }
    
    DMA0DAL = (WORD)dest;   // set destination for DMAx
    DMA0SAL = (WORD)source; // set source for DMAx
    DMA0SZ = count;         // how many bytes to transfer

    DMA0CTL |= DMAEN;       // enable DMAx
    DMA0CTL |= DMAREQ;      // trigger DMAx

    //wait for DMA transfer finished
    while (!(DMA0CTL & DMAIFG));

    DMA0CTL &= ~DMAEN;      // disable DMAx
    return dest;
}

// this functions starts DMA transfer to/from USB memory into/from RAM
// Using DMA1
// Support only for data in <64k memory area.
VOID * memcpyDMA1(VOID * dest, const VOID * source, size_t count)
{
    if (count == 0)         // do nothing if zero bytes to transfer
    {
        return dest;
    }
  
    DMA1DAL = (WORD)dest;   // set destination for DMAx
    DMA1SAL = (WORD)source; // set source for DMAx
    DMA1SZ = count;         // how many bytes to transfer

    DMA1CTL |= DMAEN;       // enable DMAx
    DMA1CTL |= DMAREQ;      // trigger DMAx

    //wait for DMA transfer finished
    while (!(DMA1CTL & DMAIFG));

    DMA1CTL &= ~DMAEN;      // disable DMAx
    return dest;
}

// this functions starts DMA transfer to/from USB memory into/from RAM
// Using DMA2
// Support only for data in <64k memory area.
VOID * memcpyDMA2(VOID * dest, const VOID * source, size_t count)
{
    if (count == 0)         // do nothing if zero bytes to transfer
    {
        return dest;
    }

    DMA2DAL = (WORD)dest;   // set destination for DMAx
    DMA2SAL = (WORD)source; // set source for DMAx
    DMA2SZ = count;         // how many bytes to transfer

    DMA2CTL |= DMAEN;       // enable DMAx
    DMA2CTL |= DMAREQ;      // trigger DMAx

    //wait for DMA transfer finished
    while (!(DMA2CTL & DMAIFG));

    DMA2CTL &= ~DMAEN;      // disable DMAx
    return dest;
}

/*----------------------------------------------------------------------------+
| End of source file                                                          |
+----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/
