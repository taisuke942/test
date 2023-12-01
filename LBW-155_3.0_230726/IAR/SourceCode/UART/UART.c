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
//This software has been submitted to export control regulations
//The ECCN is EAR99 
//*****************************************************************************
/**
*  @file UART.c
*
*  @brief this file contains all the required functions to send and receive
*  data using the UART module.
*
*
*  @author Daniel Torres - Texas Instruments, Inc
*  @date November 2010
*  @version 1.0 Initial version
*  @note Built with IAR for MSP430 Version: 5.10
*/


#include "msp430.h"
#include "main.h"
#include "UART.h"


  
/**
* @brief Function Name:     InitUART.                                                 
* @brief  Description: This function initialized the USCI-UART.
* @param none                                                   
* @return none                                                    
*/     
void InitUART(void){ 

  UCAxCTL1 |= UCSWRST;            // **Stops USCI state machine** 
  
  UART_PxREN &= ~(UART_TX_PAD|UART_RX_PAD); //Disable port pull resistors
  UART_PxDIR &= ~UART_RX_PAD;               // Configure Px.X as input
  UART_PxDIR |= UART_TX_PAD;                // Configure Px.X as output
  UART_PxSEL |= (UART_TX_PAD|UART_RX_PAD); // Px.x & Px.X = USCI_Ax TXD & RXD
  
  UCAxCTL0 = 0x00;                // No parity, 8-N-1 mode
  UCAxCTL1 |= UCSSEL_2;           // Select SMCLK as clock source for the UART
  UCAxBR = UART_BAUDRATE_REG;     // defines baudrate
  UCAxMCTL =  (UCBRF_0|UCBRS_6);  // Modulation UCBRSx = 6
  
  UCAxIFG &= ~UCAxRXIFG;          //Clear RX IFG
  
  UCAxCTL1 &= ~UCSWRST;           // **Initialize USCI state machine**
  UCAxIE |= UCAxRXIE;             // Enable USCI_A1 RX interrupt
  
}  

/**
* @brief Function Name: StopUARTRx.                                                 
* @brief  Description: This function disables the USCI-UART interrupts in order
*                     to not acknowledge byte sent by the TX.
* @param none                                                   
* @return none                                                    
*/
void StopUARTRx(void){

  UCAxIE &= ~UCAxRXIE;             // Disable USCI RX interrupt 
  
}


/**
* @brief Function Name: StartUARTRx.                                                 
* @brief  Description: This function enables the USCI-UART interrupts in order
*                     to be ready to receive USBID messages.
* @param none                                                   
* @return none                                                    
*/
void StartUARTRx(void){
  
  UCAxIFG &= ~UCAxRXIFG;           // Clear RX IFG
  UCAxIE |= UCAxRXIE;              // Enable USCI RX interrupt
}


/**
* @brief Function Name: WriteUART.                                      
* @brief  Description: This function writes data into the UART TX REG.
* @param unsigned char data the data to be written      
* @return None                                          
*/
void WriteUART(unsigned char data)
{  
  unsigned char TimeOutCounter = 0;
  // USCI_A0 TX buffer ready?
  while (!(UCAxIFG & UCAxTXIFG)){ 
  	    __delay_cycles(1000);
        TimeOutCounter++;
        if(TimeOutCounter >= 200)
          return ;    
                     
  }
  //if so...then send byte
  UCAxTXBUF = data;

}

/**
* @brief Function Name: putsUART .                                           
* @brief  Description: This function puts the data string to be transmitted 
*                     into the transmit buffer (till NULL character)  .     
* @param unsigned char * address of the string buffer to be   
*                     transmitted                                          
* @return None                                                
*/
void putsUART(unsigned char *buffer, unsigned short StringSize)
{
  unsigned short i;
  unsigned char TimeOutCounter = 0;
  
  // transmit till NULL character is encountered 
  for(i=0;i<StringSize;i++)
  {
  // USCI_A0 TX buffer ready?
  while (!(UCAxIFG & UCAxTXIFG)){ 
  	    __delay_cycles(1000);
        TimeOutCounter++;
        if(TimeOutCounter >= 200)
          return ;    
                      
  }                    //wait until Tx buffer is empty      
  UCAxTXBUF = *buffer++;    // transfer data word to TX reg
            
  }

}






