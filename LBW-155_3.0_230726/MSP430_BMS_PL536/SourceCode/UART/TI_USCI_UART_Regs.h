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
//
//This software has been submitted to export control regulations
//The ECCN is EAR99 
/**
* @file TI_USCI_UART_Regs.h
* @brief Generic UART register definition
*
* @author Daniel Torres - Texas Instruments
*
* @date 09/2010
*
* @version 1.0  Initial Version
*/

#ifndef USCI_UART_REGS
#define USCI_UART_REGS



#if (USCI_A_MODULE == 0)
  #ifdef   __MSP430_HAS_USCI_A0__
    #define UCAxCTL0		   UCA0CTL0		/* USCI Control Register 0 */	
    #define UCAxCTL1    	 UCA0CTL1		/* USCI Control Register 1 */
    #define UCAxBR         UCA0BRW
    #define UCAxBR0     	 UCA0BR0			/* USCI Baud Rate 0 */
    #define UCAxBR1     	 UCA0BR1			/* USCI Baud Rate 1 */
    #define UCAxMCTL   	   UCA0MCTL		/* USCI modulation control register*/
    #define UCAxSTAT    	 UCA0STAT		/* USCI Status Register */
    #define UCAxRXBUF   	 UCA0RXBUF		/* USCI Receive Buffer */
    #define UCAxTXBUF   	 UCA0TXBUF		/* USCI Transmit Buffer */
    #define UCAxABCTL   	 UCA0ABCTL		/* USCI auto baud control register*/
    #define UCAxIE 		     UCA0IE       		/* USCI Interrupt Enable Register */
    #define UCAxIFG		     UCA0IFG      		/* USCI Interrupt Flags Register */                        
    #define UCAxIV         UCA0IV  /* USCI Interrupt Vector Register */

    #define UCAxRX_VECTOR  USCI_A0_VECTOR

    #define UCAxRXIE       BIT0
    #define UCAxTXIE       BIT1
    #define UCAxRXIFG      BIT0
    #define UCAxTXIFG      BIT1
  #endif
#elif (USCI_A_MODULE == 1)
  #ifdef   __MSP430_HAS_USCI_A1__
    #define UCAxCTL0		   UCA1CTL0			/* USCI Control Register 0 */	
    #define UCAxCTL1    	 UCA1CTL1			/* USCI Control Register 1 */
    #define UCAxBR         UCA1BRW
    #define UCAxBR0     	 UCA1BR0			/* USCI Baud Rate 0 */
    #define UCAxBR1     	 UCA1BR1			/* USCI Baud Rate 1 */
    #define UCAxMCTL   	   UCA1MCTL			/* USCI modulation control register*/
    #define UCAxSTAT    	 UCA1STAT			/* USCI Status Register */
    #define UCAxRXBUF   	 UCA1RXBUF			/* USCI Receive Buffer  */
    #define UCAxTXBUF   	 UCA1TXBUF			/* USCI Transmit Buffer */
    #define UCAxABCTL   	 UCA1ABCTL			/* USCI auto baud control register*/
    #define UCAxIE 		     UCA1IE       		/* USCI Interrupt Enable Register */
    #define UCAxIFG		     UCA1IFG      		/* USCI Interrupt Flags Register  */                        
    #define UCAxIV         UCA1IV   /* USCI Interrupt Vector Register */
    
    #define UCAxRX_VECTOR  USCI_A1_VECTOR

    #define UCAxRXIE       BIT0
    #define UCAxTXIE       BIT1
    #define UCAxRXIFG      BIT0
    #define UCAxTXIFG      BIT1
  #endif
#else 
  #error "USCI Module not supported"
#endif  

#endif // USCI_UART_REGS


