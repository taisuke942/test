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
*  @file hal_UCS.h
*
*  @brief This file contains definitions for the Hardware Abstraction Layer 
*  (HAL) specifically created for the MSP430.
*
*  @author Texas Instruments, Inc
*  @date November 2010
*  @version 1.0 Initial version
*  @note Built with IAR for MSP430 Version: 5.10
*/
//*******************************************************************************
//  Provides Functions to Initialize the UCS/FLL and clock sources
//    File: hal_ucs.c
//
//    Texas Instruments
//
//    Version 1.2
//    11/24/09
//
//    V1.0  Initial Version
//    V1.1  Added timeout function
//    V1.1  Added parameter for XTDrive
//*******************************************************************************


#ifndef __hal_UCS
#define __hal_UCS

#include <stdint.h>
#include "hal_macros.h"

//************************************************************************
// Check and define required Defines
//************************************************************************

#ifndef XT1LFOFFG               // Defines if not available in header file
#define XT1LFOFFG 0
#endif
#ifndef XT1HFOFFG               // Defines if not available in header file
#define XT1HFOFFG 0
#endif
#ifndef XT2OFFG                 // Defines if not available in header file
#define XT2OFFG 0
#endif
#ifndef XTS                    // Defines if not available in header file
#define XTS 0
#endif
#ifndef XT2DRIVE_3             // Defines if not available in header file
#define XT2DRIVE_3  0
#endif
/*************************************************************************
* MACROS
**************************************************************************/

/* Select source for FLLREF  e.g. SELECT_FLLREF(SELREF__XT1CLK) */
#define SELECT_FLLREF(source) st(UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (source);) 
/* Select source for ACLK    e.g. SELECT_ACLK(SELA__XT1CLK) */
#define SELECT_ACLK(source)   st(UCSCTL4 = (UCSCTL4 & ~(SELA_7))   | (source);) 
/* Select source for MCLK    e.g. SELECT_MCLK(SELM__XT2CLK) */
#define SELECT_MCLK(source)   st(UCSCTL4 = (UCSCTL4 & ~(SELM_7))   | (source);) 
/* Select source for SMCLK   e.g. SELECT_SMCLK(SELS__XT2CLK) */
#define SELECT_SMCLK(source)  st(UCSCTL4 = (UCSCTL4 & ~(SELS_7))   | (source);) 
/* Select source for MCLK and SMCLK e.g. SELECT_MCLK_SMCLK(SELM__DCOCLK + SELS__DCOCLK) */
#define SELECT_MCLK_SMCLK(sources) st(UCSCTL4 = (UCSCTL4 & ~(SELM_7 + SELS_7)) | (sources);)

/* set ACLK/x */
#define ACLK_DIV(x)         st(UCSCTL5 = (UCSCTL5 & ~(DIVA_7)) | (DIVA__##x);)     
/* set MCLK/x */
#define MCLK_DIV(x)         st(UCSCTL5 = (UCSCTL5 & ~(DIVM_7)) | (DIVM__##x);)     
/* set SMCLK/x */
#define SMCLK_DIV(x)        st(UCSCTL5 = (UCSCTL5 & ~(DIVS_7)) | (DIVS__##x);)     
/* Select divider for FLLREF  e.g. SELECT_FLLREFDIV(2) */
#define SELECT_FLLREFDIV(x) st(UCSCTL3 = (UCSCTL3 & ~(FLLREFDIV_7))|(FLLREFDIV__##x);) 

//************************************************************************
// Defines
//************************************************************************

#define UCS_STATUS_OK     0
#define UCS_STATUS_ERROR  1

//====================================================================
/**
 * Startup routine for 32kHz Cristal on LFXT1
 *
 * \param xtdrive: Bits defining the LFXT drive mode after startup
 *
*/
extern void LFXT_Start(uint16_t xtdrive);

//====================================================================
/**
 * Startup routine for 32kHz Cristal on LFXT1 with timeout counter
 *
 * \param xtdrive: Bits defining the LFXT drive mode after startup
 * \param timeout: value for the timeout counter
 *
*/
extern uint16_t LFXT_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

//====================================================================
/**
 * Startup routine for XT1
 *
 * \param xtdrive: Bits defining the XT drive mode
 *
*/
extern void XT1_Start(uint16_t xtdrive);

//====================================================================
/**
 * Startup routine for XT1 with timeout counter
 *
 * \param xtdrive: Bits defining the XT drive mode
 * \param timeout: value for the timeout counter
 *
*/
extern uint16_t XT1_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

//====================================================================
/**
 * Use XT1 in Bypasss mode
 *
*/
extern void XT1_Bypass(void);

//====================================================================
/**
 * Startup routine for XT2
 *
 * \param xtdrive: Bits defining the XT drive mode
 *
*/
extern void XT2_Start(uint16_t xtdrive);

//====================================================================
/**
 * Startup routine for XT2 with timeout counter
 *
 * \param xtdrive: Bits defining the XT drive mode
 * \param timeout: value for the timeout counter
 *
*/
extern uint16_t XT2_Start_Timeout(uint16_t xtdrive, uint16_t timeout);

//====================================================================
/**
 * Use XT2 in Bypasss mode for MCLK
 *
*/
extern void XT2_Bypass(void);

//====================================================================
/**
  * Initializes FLL of the UCS and wait till settled
  *
  * \param fsystem  required system frequency (MCLK) in kHz
  * \param ratio    ratio between fsystem and FLLREFCLK
  */
extern void Init_FLL_Settle(uint16_t fsystem, uint16_t ratio);


//====================================================================
/**
  * Initializes FLL of the UCS
  *
  * \param fsystem  required system frequency (MCLK) in kHz
  * \param ratio    ratio between fsystem and FLLREFCLK
  */
static void Init_FLL(uint16_t fsystem, uint16_t ratio);

#endif /* __hal_UCS */
