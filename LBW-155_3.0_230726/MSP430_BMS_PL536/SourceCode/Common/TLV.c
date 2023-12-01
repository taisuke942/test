/* ***********************************************************
* THIS PROGRAM IS PROVIDED "AS IS". TI MAKES NO WARRANTIES OR
* REPRESENTATIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
* COMPLETENESS OF RESPONSES, RESULTS AND LACK OF NEGLIGENCE.
* TI DISCLAIMS ANY WARRANTY OF TITLE, QUIET ENJOYMENT, QUIET
* POSSESSION, AND NON-INFRINGEMENT OF ANY THIRD PARTY
* INTELLECTUAL PROPERTY RIGHTS WITH REGARD TO THE PROGRAM OR
* YOUR USE OF THE PROGRAM.
*
* IN NO EVENT SHALL TI BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
* CONSEQUENTIAL OR INDIRECT DAMAGES, HOWEVER CAUSED, ON ANY
* THEORY OF LIABILITY AND WHETHER OR NOT TI HAS BEEN ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGES, ARISING IN ANY WAY OUT
* OF THIS AGREEMENT, THE PROGRAM, OR YOUR USE OF THE PROGRAM.
* EXCLUDED DAMAGES INCLUDE, BUT ARE NOT LIMITED TO, COST OF
* REMOVAL OR REINSTALLATION, COMPUTER TIME, LABOR COSTS, LOSS
* OF GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF
* USE OR INTERRUPTION OF BUSINESS. IN NO EVENT WILL TI'S
* AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF
* YOUR USE OF THE PROGRAM EXCEED FIVE HUNDRED DOLLARS
* (U.S.$500).
*
* Unless otherwise stated, the Program written and copyrighted
* by Texas Instruments is distributed as "freeware".  You may,
* only under TI's copyright in the Program, use and modify the
* Program without any charge or restriction.  You may
* distribute to third parties, provided that you transfer a
* copy of this license to the third party and the third party
* agrees to these terms by its first use of the Program. You
* must reproduce the copyright notice and any other legend of
* ownership on each copy or partial copy, of the Program.
*
* You acknowledge and agree that the Program contains
* copyrighted material, trade secrets and other TI proprietary
* information and is protected by copyright laws,
* international copyright treaties, and trade secret laws, as
* well as other intellectual property laws.  To protect TI's
* rights in the Program, you agree not to decompile, reverse
* engineer, disassemble or otherwise translate any object code
* versions of the Program to a human-readable form.  You agree
* that in no event will you alter, remove or destroy any
* copyright notice included in the Program.  TI reserves all
* rights not specifically granted under this license. Except
* as specifically provided herein, nothing in this agreement
* shall be construed as conferring by implication, estoppel,
* or otherwise, upon you, any license or other right under any
* TI patents, copyrights or trade secrets.
*
* You may not use the Program in non-TI devices.
//
//This software has been submitted to export control regulations
//The ECCN is EAR99 
* ********************************************************* */
//*****************************************************************************
/**
*  @file TLV.c
*
*  @brief This file contains definitions for the Hardware Abstraction Layer 
*  (HAL) specifically created for the MSP430.
*
*  @author Texas Instruments, Inc
*  @date November 2010
*  @version 1.0 Initial version
*  @note Built with IAR for MSP430 Version: 5.10
*/

// TLV Access Function Definition file

#include "TLV_descriptors.h"

/* Function Defintion
   Passing parameters:
      tag - The specific/particular tag information (length and data address location) required by the user
      *length - Address of the variable (byte long) where the number of bytes allocated for the particular 'tag' is to be stored
      *data_address - Address of the variable (word long) which is used to access the value info of the the particular 'tag' (in the TLV structure)

  NOTE: If 'length' and 'data_address' returned = 0, it implies that there was no tag match. This condition can be checked for in the 
        main function that calls this Get_TLV_info(..) function and appropriate actions can be taken
*/

void Get_TLV_info(unsigned char tag, unsigned char *length, unsigned int *data_address)
{
//  char *TLV_address = (char *)TLV_START;               // TLV Structure Start Address
    unsigned char *TLV_address = (unsigned char *)TLV_START;  // TLV Structure Start Address

//  while((*TLV_address != tag) && (*TLV_address != TLV_TAGEND) && ((unsigned int)TLV_address < TLV_END))
        while ((*TLV_address != tag) && (*TLV_address != TLV_TAGEND) && ((unsigned int)(unsigned long)TLV_address < (unsigned int)(unsigned long)TLV_END))
      //  while ((*TLV_address != tag) && (*TLV_address != TLV_TAGEND) && (TLV_address < (char *)TLV_END))

  {
    TLV_address += *(TLV_address+1) + 2;               // add (Current TAG address + LENGTH) + 2
  }
  if (*TLV_address == tag)                             // Check if Tag match happened..
  {
    *length = *(TLV_address+1);                        // Return length = Address + 1
//    *data_address = (unsigned char)(TLV_address+2);     // Return address of first data/value info = Address + 2
    *data_address = *((unsigned int*)(TLV_address + 2));    // Return address of first data/value info = Address + 2
   //unsigned char *data_address = (unsigned char *)(TLV_address + 2);
  }
  else                                                 // If there was no tag match and the end of TLV structure was reached..
  {
    *length = 0;                                       // Return 0 for TAG not found
    data_address = 0;                                  // Return 0 for TAG not found
  }
}
