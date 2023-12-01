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
*  @file TLV_descriptors.h
*
*  @brief This file contains definitions for the Hardware Abstraction Layer 
*  (HAL) specifically created for the MSP430.
*
*  @author Texas Instruments, Inc
*  @date November 2010
*  @version 1.0 Initial version
*  @note Built with IAR for MSP430 Version: 5.10
*/
/************************************************************
* TLV Descriptors for F5438
************************************************************/


// function declaration
extern void Get_TLV_info(unsigned char tag, unsigned char *length, unsigned int *data_address);


#ifndef __MSP430_HAS_TLV__              /* Definition to show that Module is available */
#define __MSP430_HAS_TLV__              /* Definition to show that Module is available */
#define TLV_START             (0x1A08)    /* Start Address of the TLV structure */
#define TLV_END               (0x1AFF)    /* End Address of the TLV structure */

#define TLV_LDTAG             (0x01)      //  Legacy descriptor (1xx, 2xx, 4xx families)
#define TLV_PDTAG             (0x02)      //  Peripheral discovery descriptor
#define TLV_Reserved1         (0x03)      //  Future usage
#define TLV_Reserved2         (0x04)      //  Future usage
#define TLV_BLANK             (0x05)      //  Blank descriptor
#define TLV_Reserved3         (0x06)      //  Future usage
#define TLV_SERNUM            (0x07)      //  Serial Number
#define TLV_DIERECORD         (0x08)      /*  Die Record  */
#define TLV_ADCCAL            (0x10)      //  ADC calibration
#define TLV_TAGEXT            (0xFE)      //  Tag extender
#define TLV_TAGEND            (0xFF)      //  Tag End of Table


#endif
