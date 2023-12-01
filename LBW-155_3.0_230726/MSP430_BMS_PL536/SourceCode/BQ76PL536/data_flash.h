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
//This software has been submitted to export control regulations
//The ECCN is EAR99 
//*****************************************************************************
/**
*  @file data_flash.h
*
*  @brief this file contains all the definitions of the battery pack
*
*  @author S.tei  MIGHT INDUSTRY Co.�CLtd
*  @date May 2017
*  @version 1.0  version
*  @note Built with IAR for MSP430 Version: 5.10
*/
#ifndef DATA_FLASH_H
#define DATA_FLASH_H


//Battery pack definition
#define NUMBER_OF_BQ_DEVICES      3  //3 BQ76PL536 devices are connected               mod // 2017.04.03
#define NUMBER_OF_CELLS           16 //MAX number of cells in the system               mod // 2017.04.03
#define MAX_CELLS_NUMBER_IN_BQ    6  //MAX number of cells per BQ76PL536 device        mod //2017.04.03
#define CELL_BALANCING_EN         1  //set to 1 to enable cell balancing


#define ONE_MINUTE                     60

//Battery pack information and threshold values
#define dCOV_THRESHOLD                 3600  //COV_THRESHOLD           [mV]            mod // 2017.04.03
#define dCOV_RECOVERY_THRESHOLD        3450  //COV_RECOVERY_THRESHOLD  [mV]            mod // 2017.04.03
#define dCOV_TIME                      1 //20 //COV_TIME (max value 32) [100ms]        mod // 2017.04.03
#define dCUV_THRESHOLD                 2300  //CUV_THRESHOLD (2.5x0.893)  2100 [mV]    mod // 2017.04.03��20230525
#define dCUV_RECOVERY_THRESHOLD        2700  //CUV_RECOVERY_THRESHOLD  [mV]
#define dLOW_POWER_THERESHOLD          2100  //LOW_POWER_THERESHOLD  [mV]  LPM4 //2023.04.26 LPM4�ɓ���d��

#define dCUV_TIME                      1 //20 //CUV_TIME (max value 32) [100ms]

#define dPACK_OVER_TEMP1               65    //3 PACK_OVER_TEMP1   [st C]
#define dPACK_OT_TIME1                 0  //PACK_OT_TIME1       [ms]
#define dPACK_OVER_TEMP2               65    //3 PACK_OVER_TEMP2   [st C]
#define dPACK_OT_TIME2                 0  //PACK_OT_TIME2       [ms]

//PACK_END_OF_CHARGE_VOLTAGE   [mV]
#define dPACK_END_OF_CHARGE_VOLTAGE    (DWORD)3550*NUMBER_OF_CELLS                   // mod  2017.04.03
#define dCC_CV_QUAL_TIME               10    //CC_CV_QUAL_TIME              [s]        mod // 2017.04.03
//PACK_END_OF_DISCHARGE_VOLTAGE[mV]
#define dPACK_END_OF_DISCHARGE_VOLTAGE (DWORD)dCUV_THRESHOLD*NUMBER_OF_CELLS 
#define dEND_OF_DISCHARGE_QUAL_TIME    10    //END_OF_DISCHARGE_QUAL_TIME   [s]        mod // 2017.04.03

#define dCHARGE_CURRENT                1100  //CHARGE_CURRENT               [mA]
#define dCHARGE_TAPER_CURRENT          300   //CHARGE_TAPER_CURRENT         [mA]
#define dCHARGE_TAPER_TIME             (DWORD)1*ONE_MINUTE//CHARGE_TAPER_TIME[s]      mod // 2017.04.03
#define dMAX_CHARGE_TIME               (DWORD)5*ONE_MINUTE//MAX_CHARGE_TIME  [s]      mod // 2017.04.03 ???

//FULL_DISCHARGE_CLEAR_VOLTS   [mV]
#define dFULL_DISCHARGE_CLEAR_VOLTS    dPACK_END_OF_DISCHARGE_VOLTAGE
//FULL_CHARGE_CLEAR_VOLTS      [mV] 
#define dFULL_CHARGE_CLEAR_VOLTS       dPACK_END_OF_CHARGE_VOLTAGE    
#define dDELTA_CHARGE_V                10   //DELTA_CHARGE_V               [mv]
#define dCHARGE_DISCHARGE_TIME         (DWORD)1*ONE_MINUTE  //CHARGE_DISCHARGE_TIME [s]
#define dDELTA_DISCHARGE_V             10   //DELTA_DISCHARGE_V            [mV]

#define dSOV_THRESHOLD                 3800  //SOV_THRESHOLD                [mV]
#define dSOV_RECOVERY_THRESHOLD        3750  //SOV_RECOVERY_THRESHOLD       [mV]
#define dSOV_TIME                      3000  //SOV_TIME                     [ms]

#define dCELL_IMBALANCE_FAIL_THRESHOLD 50000   //CELL_IMBALANCE_FAIL_THRESHOLD[mV] //20230426 Fauit���������ׂ�5000�ɂ���
#define dCELL_IMBALANCE_FAULT_V        300     //CELL_IMBALANCE_FAULT_V[mV] //20230608 Fauit�M�����K�v�Ȃ̂Œǉ� 0.5V��0.3V�ɕύX 20230613
#define dCELL_IMBALANCE_FAIL_TIME      (DWORD)2*ONE_MINUTE//CELL_IMBALANCE_FAIL_TIME[s]
#define dBALANCE_TIME                  (DWORD)1*ONE_MINUTE//BALANCE_TIME A.K.A CB_TIME[s]
#define dBALANCE_VOLTS_THRESHOLD       50    //BALANCE_VOLTS_THRESHOLD      [mV]
#define dMIN_BALANCE_VOLTS             dCUV_RECOVERY_THRESHOLD //MIN_BALANCE_VOLTS[mV]
#define dMAX_BALANCE_TIME              (DWORD)7200*ONE_MINUTE//MAX_BALANCE_TIME[s]



/**
* @brief  Global defines         .                     
*/

//definition of the Parameters structure
typedef enum PARAM_ID
{
  /*Voltage*/
  COV_THRESHOLD, //COV_THRESHOLD = 0,
  COV_RECOVERY_THRESHOLD,
  COV_TIME,
  CUV_THRESHOLD,  
  CUV_RECOVERY_THRESHOLD,
  CUV_TIME,
  LOW_POWER_THERESHOLD,         //20230525�ǉ��@
  
  /*Temperature*/
  PACK_OVER_TEMP1,
  PACK_OT_TIME1,
  PACK_OVER_TEMP2,
  PACK_OT_TIME2,
  
  /*Charge and Discharge*/
  PACK_END_OF_CHARGE_VOLTAGE,
  CC_CV_QUAL_TIME,
  PACK_END_OF_DISCHARGE_VOLTAGE,
  END_OF_DISCHARGE_QUAL_TIME,
  CHARGE_CURRENT,
  CHARGE_TAPER_CURRENT,
  CHARGE_TAPER_TIME,
  MAX_CHARGE_TIME,
  FULL_DISCHARGE_CLEAR_VOLTS,
  FULL_CHARGE_CLEAR_VOLTS,
  DELTA_CHARGE_V,
  CHARGE_DISCHARGE_TIME,
  DELTA_DISCHARGE_V,
  
  /*Safety*/
  SOV_THRESHOLD,
  SOV_RECOVERY_THRESHOLD,
  SOV_TIME,

  /*Balancing*/
  CELL_IMBALANCE_FAIL_THRESHOLD,
  CELL_IMBALANCE_FAIL_TIME,
  BALANCE_TIME,
  BALANCE_VOLTS_THRESHOLD,
  MIN_BALANCE_VOLTS,
  MAX_BALANCE_TIME,
  CELL_IMBALANCE_FAULT_V
  
} param_id_t;


/**
* @brief  Global functions declaration         .                     
*/

extern unsigned short get_u16_value(param_id_t param_id);
extern unsigned long get_u32_value(param_id_t param_id);

#endif

/*EOF*/
