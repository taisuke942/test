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
// 
//You may not use the Program in non-TI devices.
//
//
//This software has been submitted to export control regulations
//The ECCN is EAR99 
//****************************************************************************//
/**
*  @file   TI_USCI_SPI_Regs.h
*
*  @brief Provides definitons for the SPI Hardware abastraction layer (HAL)
*  
*  @author Daniel Torres - Texas Instruments, Inc
*  @date November 2010
*  @version 1.0 Initial version
*  @note Built with IAR for MSP430 Version: 5.10
*/


#ifndef TI_USCI_SPI_Regs
#define TI_USCI_SPI_Regs

//SPI module definitions
#define USCI_AB_MODULE   0     //USCI Module 0 will be used

#define IO_SPI_CS   BIT7  //P2.7
#define IO_SPI_SDI  BIT0  //P3.0
#define IO_SPI_SDO  BIT1  //P3.1
#define IO_SPI_SCLK BIT2  //P3.2

//SPI port definitions
#define STE_PxIN    P2IN
#define STE_PxOUT   P2OUT
#define STE_PxDIR   P2DIR
#define STE_PxSEL   P2SEL
#define STE_PxREN   P2REN

#define SIMO_PxIN   P3IN
#define SIMO_PxOUT  P3OUT
#define SIMO_PxDIR  P3DIR
#define SIMO_PxSEL  P3SEL
#define SIMO_PxREN  P3REN

#define SOMI_PxIN   P3IN
#define SOMI_PxOUT  P3OUT
#define SOMI_PxDIR  P3DIR
#define SOMI_PxSEL  P3SEL
#define SOMI_PxREN  P3REN

#define CLK_PxIN    P3IN
#define CLK_PxOUT   P3OUT
#define CLK_PxDIR   P3DIR
#define CLK_PxSEL   P3SEL
#define CLK_PxREN   P3REN

#if (USCI_AB_MODULE == 0)
     #ifdef   __MSP430_HAS_USCI_A0__ 
      #define UCAxCTL0		   UCA0CTL0		//* USCI Control Register 0 */	
      #define UCAxCTL1    	 UCA0CTL1		//* USCI Control Register 1 */
		  #define UCAxBR0     	 UCA0BR0    //* USCI Baud Rate 0 */
		  #define UCAxBR1     	 UCA0BR1	  //* USCI Baud Rate 1 */
		  #define UCAxMCTL   	   UCA0MCTL	  //* USCI modulation control register*/
		  #define UCAxSTAT    	 UCA0STAT		//* USCI Status Register */
		  #define UCAxRXBUF   	 UCA0RXBUF	//* USCI Receive Buffer */
		  #define UCAxTXBUF   	 UCA0TXBUF	//* USCI Transmit Buffer */
		  #define UCAxICTL			 UCA0ICTL		//Interrupt control register	
		  #define UCAxIE				 UCA0IE			//Interrupt Enable Register
		  #define UCAxIFG				 UCA0IFG		//Interrupt Flag register
		  #define UCAxIV				 UCA0IV			//interrupt Vector register	
		  #define UCAxRXIE       BIT0
		  #define UCAxTXIE       BIT1
		  #define UCAxRXIFG      BIT0
		  #define UCAxTXIFG      BIT1
     #endif  
     #ifdef   __MSP430_HAS_USCI_B0__ 
			#define UCBxCTL0		   UCB0CTL0		//* USCI Control Register 0 */	
			#define UCBxCTL1    	 UCB0CTL1		//* USCI Control Register 1 */
			#define UCBxBR0     	 UCB0BR0		//* USCI Baud Rate 0 */
			#define UCBxBR1     	 UCB0BR1		//* USCI Baud Rate 1 */
			#define UCBxMCTL   	   UCB0MCTL		//* USCI modulation control register*/
			#define UCBxSTAT    	 UCB0STAT		//* USCI Status Register */
			#define UCBxRXBUF   	 UCB0RXBUF  //* USCI Receive Buffer */
			#define UCBxTXBUF   	 UCB0TXBUF  //* USCI Transmit Buffer */
			#define UCBxICTL			 UCB0ICTL		//Interrupt control register	
			#define UCBxIE				 UCB0IE			//Interrupt Enable Register
			#define UCBxIFG				 UCB0IFG		//Interrupt Flag register
			#define UCBxIV				 UCB0IV			//interrupt Vector register	
			#define UCBxRXIE       BIT0
			#define UCBxTXIE       BIT1
			#define UCBxRXIFG      BIT0
			#define UCBxTXIFG      BIT1
	   #endif
#endif

#if (USCI_AB_MODULE == 1)
    #ifdef   __MSP430_HAS_USCI_A1__
			#define UCAxCTL0		   UCA1CTL0		//* USCI Control Register 0 */	
			#define UCAxCTL1    	 UCA1CTL1		//* USCI Control Register 1 */
			#define UCAxBR0     	 UCA1BR0		//* USCI Baud Rate 0 */
			#define UCAxBR1     	 UCA1BR1		//* USCI Baud Rate 1 */
			#define UCAxMCTL   	   UCA1MCTL		//* USCI modulation control register*/
			#define UCAxSTAT    	 UCA1STAT		//* USCI Status Register */
			#define UCAxRXBUF   	 UCA1RXBUF	//* USCI Receive Buffer */
			#define UCAxTXBUF   	 UCA1TXBUF	//* USCI Transmit Buffer */
			#define UCAxICTL			 UCA1ICTL		//Interrupt control register	
			#define UCAxIE				 UCA1IE			//Interrupt Enable Register
			#define UCAxIFG				 UCA1IFG		//Interrupt Flag register
			#define UCAxIV				 UCA1IV			//interrupt Vector register	
			#define UCAxRXIE       BIT0
			#define UCAxTXIE       BIT1
			#define UCAxRXIFG      BIT0
			#define UCAxTXIFG      BIT1
		#endif
	  #ifdef   __MSP430_HAS_USCI_B1__
			#define UCBxCTL0		   UCB1CTL0		//* USCI Control Register 0 */	
			#define UCBxCTL1    	 UCB1CTL1		//* USCI Control Register 1 */
			#define UCBxBR0     	 UCB1BR0		//* USCI Baud Rate 0 */
			#define UCBxBR1     	 UCB1BR1		//* USCI Baud Rate 1 */
			#define UCBxMCTL   	   UCB1MCTL		//* USCI modulation control register*/
			#define UCBxSTAT    	 UCB1STAT		//* USCI Status Register */
			#define UCBxRXBUF   	 UCB1RXBUF	//* USCI Receive Buffer */
			#define UCBxTXBUF   	 UCB1TXBUF	//* USCI Transmit Buffer */
			#define UCBxICTL			 UCB1ICTL		//Interrupt control register	
			#define UCBxIE				 UCB1IE			//Interrupt Enable Register
			#define UCBxIFG				 UCB1IFG		//Interrupt Flag register
			#define UCBxIV				 UCB1IV			//interrupt Vector register	
			#define UCBxRXIE       BIT0
			#define UCBxTXIE       BIT1
			#define UCBxRXIFG      BIT0
			#define UCBxTXIFG      BIT1
		#endif
#endif

#endif 


