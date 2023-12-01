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
/*  --------------------------LBW_200_1.0(A)-------------------------//
*  @file main.c
*  @brief this file contains the state machine fuctions and the console 
*  functions, It also contains the appliaction functions and interrupt
*  service routines.
*
*
*  @author S.tei  MIGHT INDUSTRY Co.，Ltd
*  @date May 2017
*  @version 1.0  version
*  @note Built with CCS for MSP430 Version: 4.2.1
*/ 

#include <intrinsics.h>
#include <cstring>
#include <cstdio>

#include "MSP430.h"
#include "main.h"
#include "spi_if.h"
#include "data_flash.h"
#include "bq_pack.h"
#include "USBCDC_constructs.h"

#include "Common\types.h"
#include "Common\hal_macros.h"
#include "Common\hal_UCS.h"
#include "Common\hal_pmm.h"



/**
* @brief  Global Variables .                             
*/


#ifdef USB_COMM  
char OutputString[MAX_STR_LENGTH] = "";   // Holds the outgoing string  
#endif
  
#ifdef UART_COMM  
char OutputString[MAX_STR_LENGTH] = "";   // Holds the outgoing string  
#endif
 


/**
* @brief  Local Variables     .                         
*/

//State Machine Tasks Pointer
void (*StateMachineTaskPointer)(void);    // Base States pointer

#ifdef UART_COMM
//UART
char UARTRxBuffer[MAX_STR_LENGTH]= "";
char * UARTRxBufferIndex = UARTRxBuffer;
volatile BYTE bUARTDataReceived = FALSE; // Indicates data has been received
#endif

//USB
// Indicates data has been received without an open rcv operation
volatile BYTE bDataReceived_event = FALSE;
// data receive completed event 
volatile BYTE bDataReceiveCompleted_event = FALSE;  
volatile BYTE bDataSendCompleted_event = FALSE;   // data send completed event
#ifdef USB_COMM
// The entire input string from the last 'return'
  char wholeString[MAX_STR_LENGTH] = "";
#endif

unsigned char TEST=0x0;
unsigned short CPU_active_F = 0;                   // add 2023.02.20

unsigned short lpm_timer = 0;                      // add 2023.04.27
unsigned short LPM_F = 0;                          // add 2023.05.18
unsigned short Check_F = 0;                          // add 2023.05.18
unsigned short LV_F = 0;                          // add 2023.05.18
unsigned short NO_F = 0;                          // add 2023.05.18


/**
* @brief Function Name: main.                                                 
* @brief  Description: this function is the main routine
* It controls the SW flow and the state machine
* It also initializes the system.
* @param none                                                   
* @return none                                                    
*/     
void main(void)
{

InitMCU();
  
  //Enable in3errupts
  __bis_SR_register(GIE);
  
  while(bq_pack_address_discovery() != NUMBER_OF_BQ_DEVICES){
  

    //BQ devices not discovered -> broken communication
    //Disable 1sec Timer
    Disable1SecTimer();
    				
    //Turn On LED to indicate failure
    BQ76PL536_LED_PxOUT |= OUT_BQ_LED;
    //P1OUT |= BIT7;

    //Retry to SPI comm with the BQ76PL536 devices after 1000 MCLCK cycles
    __delay_cycles(1000);
  
  }
    
  //Initialize detected BQ76PL536 devices  
  bq_pack_init();
  
  //Initial State Machine status
  StateMachineTaskPointer = &GoToLowPowerMode;

  //Main system loop



  for(;;)
  {




	  if (bq_pack.lowest_cell_volts<=get_u32_value(LOW_POWER_THERESHOLD)&&(CPU_active_F == 1)&&(LPM_F == 1)&&(Check_F == 1)) {
		  __delay_cycles(75000000);  //3秒遅延
		  update_bq_pack_data();
	  }
	  
	  if (bq_pack.lowest_cell_volts<=get_u32_value(LOW_POWER_THERESHOLD)&&(CPU_active_F == 1)&&(LPM_F == 1)&&(Check_F == 1)) {
		  BQ76PL536_FAULT_PxSEL = 0;
    	  BQ76PL536_ALERT_PxSEL = 0;
    	  BQ76PL536_DRDY_PxSEL  = 0;
          BQ76PL536_FAULT_PxIFG = 0;
          BQ76PL536_ALERT_PxIFG = 0;
          BQ76PL536_DRDY_PxIFG  = 0;
          BQ76PL536_TEMP_PxOUT = 0;

       // battery manager initial mode /////////////////////////////////
          //bq_pack.op_mode = FAULT_MODE;  //必ずこの設定にする
          bq_pack.op_mode = SOV_MODE;  //必ずこの設定にする
          //bq_pack.op_mode = INITIAL_MODE;
          bq_pack.error_status = 0;
          bq_pack.voltage = 0;
          bq_pack.timer_status = 0;
          bq_pack.eoc_eod_timer = 0;
          bq_pack.charge_taper_timer = 0;
          bq_pack.chg_dschg_op_timer = 0;
          bq_pack.balancing_timer = 0;
          bq_pack.max_balance_timer = 0;
          bq_pack.last_imbalanced_cell_idx = 0;
          bq_pack.cell_imbalance_fail_timer = 0;
       //////////////////////////////////////////////////////////////////
 
           
       // set the battery manager to initial mode ///////////////////////
          update_op_mode(INITIAL_MODE);
       //////////////////////////////////////////////////////////////////

          PCOUT   =   0x0000;
	      PCSEL   =   0x0000;
	      PCDIR   =   0xFFFF;

       // LPM4.5/////////////////////////////////////////////////////////
	      PMMCTL0_H = PMMPW_H; // PMM を開く
          PMMCTL0_L |= PMMREGOFF; // LPM4 リクエストで LPM4.5 に入るフラグを設定します
          PMMCTL0_H = 0; // ロック
       //////////////////////////////////////////////////////////////////
	      __disable_interrupt();
	      for(;;)  __bis_SR_register(LPM4_bits); // goes into LPM4

      } else {

	    // State machine entry & exit point
	    (*StateMachineTaskPointer)();	// jump to a task state
	    NO_F=0;
	  }

      if (bq_pack.lowest_cell_volts>get_u32_value(LOW_POWER_THERESHOLD)+10) {
         CPU_active_F = 1;
      }


  }  //end of for(;;) 
} //end of main()

/**
* @brief  State Machine tasks                              
*/
/**
* @brief Function Name:  GoToLowPowerMode.                                                
* @brief Description  :  This function sets the MSP430 in low power mode.
* @param parameters   :  none                                                   
* @return Value       :  none                                                   
*/
void GoToLowPowerMode(void){

  //* Enter LPM awaiting for an alarm/fault event or timer*/
  __bis_SR_register(LOW_POWER_MODE);  
/*
  unsigned short i;
  for (i=0; i<NUMBER_OF_BQ_DEVICES; i++){
	  if (bq_pack.bq_devs[i].fault_status == (0<<1)){
	  	  BQ76PL536_TEMP_PxOUT &= ~OUT_BQ_TEMP;
	  }
  }*/

}


/**
* @brief Function Name: BQFaultSignalTask.                                                  
* @brief Description  : This function executes the corrective actions to be 
* taken when a fault condition is detected by asserting the FAULT line on any 
* of the 'PL536 devices.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
void BQFaultSignalTask(void){

	BYTE i;
  
  //*Read BQ device for detailed status*/
  //*Read each device errors*/
  for(i=0;i<NUMBER_OF_BQ_DEVICES;i++){    
  //read device errors
  bq_dev_read_errors(&bq_pack.bq_devs[i]);
    
  /*Clear faults */
  bq_dev_clear_faults(&bq_pack.bq_devs[i]);
    
  /*Read each device temperature*/
  bq_dev_read_temps(&bq_pack.bq_devs[i]);
  }  
  
  //check the POT, CUV and COV conditions
  CheckFaultConditions();
  
  //Send Fault message to the HOST
  SendFaultMessageToHost();
     
  //go to Low Power Mode
  StateMachineTaskPointer = &GoToLowPowerMode;
  
}

/**
* @brief Function Name: BQAlertSignalTask.                                                  
* @brief Description  : This function executes the corrective actions to be 
* taken when an alert condition is detected by asserting the FAULT line on any 
* of the 'PL536 devices.
* @param parameters   :                                                     
* @return Value       :                                                     
*/     
void BQAlertSignalTask(void){
   BYTE i;  
   
   //*Read BQ device for detailed status*/
   //*Read each device errors*/
   for(i=0;i<NUMBER_OF_BQ_DEVICES;i++){
     
    bq_dev_read_errors(&bq_pack.bq_devs[i]);
    
    //*Clear alerts */
    bq_dev_clear_alerts(&bq_pack.bq_devs[i]);
    
    //*Read each device temperature*/
    bq_dev_read_temps(&bq_pack.bq_devs[i]);
    
   }
   
  //*Signal error to the HOST*/
  //check the POT, CUV and COV conditions
  CheckFaultConditions();
   
  //Send Fault message to the HOST
  SendAlertMessageToHost();
      
  //go to Low Power Mode
  StateMachineTaskPointer = &GoToLowPowerMode;
}

/**
* @brief Function Name: Timer1SecExpiredTask.                                                 
* @brief Description  : Service routine for the 1sec timer
* it triggers the ADC conversion on the 'PL536 devices.
* @param parameters   :  none                                                   
* @return Value       :  none                                                   
*/     
void Timer1SecExpiredTask(void){

  //Increment BQ Pack timer
  update_bq_pack_timer();         
  
  //Start Data processing
  bq_pack_start_conv();

}


/**
* @brief Function Name: DRDYSignalTask .                                                 
* @brief Description  : This is the service routine for the DRDY line .
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
void DRDYSignalTask(void){

  ///*BQ76PL536-ADC conversion ready*/    
  //Read data from BQ pack for overall system verification
  update_bq_pack_data();            

  //Analyze bq_pack data and perform required action (if necessary)
  BatteryPackManager();
  //Send data to HOST
  HostCommunicationTask();  
  

  //go to Low Power Mode
  StateMachineTaskPointer = &GoToLowPowerMode;
}

/**
* @brief Function Name: HostCommunicationTask.                                                  
* @brief Description  : It takes care of the communication interface 
* (UART or USB) with the host, it could be a PC or other MCU.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
void HostCommunicationTask(void){

#ifdef UART_COMM  
  if(bUARTDataReceived)// Some data is in the buffer; begin receiving a command              
  {  
    //Go to the UART comm routine
    UARTCommunicationTask();
  }
#endif  

#ifdef USB_COMM  
  if(USB_connectionState() == ST_ENUM_ACTIVE){
    //Go to the USB comm routine
    USBCommunicationTask();
  }
#endif  
  


}

/**
* @brief Function Name:  SendFaultMessageToHost                                                  
* @brief Description  :  Sends a fault message to the host when a fault
* condition occurs.
* @param parameters   :  none                                                   
* @return Value       :  none                                                   
*/     
void SendFaultMessageToHost(void){
  
  BYTE i;    
  BYTE DeviceID = 0;
  
  //identify the device & cell with the fault condition
  for(i=0;i<NUMBER_OF_BQ_DEVICES;i++){      
    if(bq_pack.bq_devs[i].device_status & BIT6){//check if fault bit is set
      DeviceID = i;
    }
  }  
  
#ifdef USB_COMM
  // Prepare the outgoing string
  strcpy(OutputString,"\r\nThe battery pack is in FAULT MODE\r\n");     
  // Send the response over USB                                
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);                 
  //print the variable
  sprintf(OutputString,"Fault detected on device %u\r\n",DeviceID);           
  // Send the response over USB 
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);  
  //print the variable       
  sprintf(OutputString,"Device address %u\r\n",
  bq_pack.bq_devs[DeviceID].device_address);           
  // Send the response over USB  
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10); 
  //print the variable        
  sprintf(OutputString,"Device %u status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].device_status);           
  // Send the response over USB
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
  
  for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
    //print the variable
    sprintf(OutputString,"Cell %u voltage %u\r\n",i,
    bq_pack.bq_devs[DeviceID].cell_voltage[i]);           
    // Send the response over USB
    sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
  }
  //print the variable
  sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].alert_status);           
  // Send the response over USB
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);
  //print the variable         
  sprintf(OutputString,"Device %u fault status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].fault_status);           
  // Send the response over USB
  if(sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,1)){return;}
  //print the variable         
  sprintf(OutputString,"Device %u cov fault on cells 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].cov_fault);       
  // Send the response over USB    
  if(sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,1)){return;}
  //print the variable          
  sprintf(OutputString,"Device %u cuv fault on cells 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].cuv_fault);           
  // Send the response over USB
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
#endif

#ifdef UART_COMM
  // Prepare the outgoing string
  strcpy(OutputString,"\r\nThe battery pack is in FAULT MODE\r\n");     
  // Send the response over UART                              
  putsUART((BYTE*)OutputString,strlen(OutputString));                  
  //print the variable        
  sprintf(OutputString,"Fault detected on device %u\r\n",DeviceID);
  // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));
  //print the variable          
  sprintf(OutputString,"Device address %u\r\n",
  bq_pack.bq_devs[DeviceID].device_address);      
  // Send the response over UART    
  putsUART((BYTE*)OutputString,strlen(OutputString));     
  //print the variable    
  sprintf(OutputString,"Device %u status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].device_status);       
  // Send the response over UART    
  putsUART((BYTE*)OutputString,strlen(OutputString));          
        
  for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
    //print the variable
    sprintf(OutputString,"Cell %u voltage %u\r\n",i,
    bq_pack.bq_devs[DeviceID].cell_voltage[i]);      
    // Send the response over UART     
    putsUART((BYTE*)OutputString,strlen(OutputString));          
  }
        
  sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].alert_status);           //print the variable
  // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));
  sprintf(OutputString,"Device %u fault status 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].fault_status);           //print the variable
  // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));          
  sprintf(OutputString,"Device %u cov fault on cell 0x%X\r\n",
  DeviceID,bq_pack.bq_devs[DeviceID].cov_fault);     //print the variable
  // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));          
  sprintf(OutputString,"Device %u cuv fault on cell 0x%X\r\n",DeviceID,
  bq_pack.bq_devs[DeviceID].cuv_fault);           //print the variable
  // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));          
   
#endif  
}


/**
* @brief Function Name: SendAlertMessageToHost  .                                                
* @brief Description  : Send message to host when alert condition occurs.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
void SendAlertMessageToHost(void){
  
  BYTE i;    
  unsigned char DeviceID = 0;
  
  //identify the device with the alert condition
  for(i=0;i<NUMBER_OF_BQ_DEVICES;i++){
    if(bq_pack.bq_devs[i].device_status & BIT5){//check if alert bit is set
      DeviceID = i;
    }
  }
      
#ifdef USB_COMM // Prepare the outgoing string & Send data
  strcpy(OutputString,"\r\nThe battery pack is in ALERT Mode\r\n");          
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);     
  sprintf(OutputString,"alert detected on device %u\r\n",DeviceID);          
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);      
  sprintf(OutputString,"Device address %u\r\n",
          bq_pack.bq_devs[DeviceID].device_address);           
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);       
  sprintf(OutputString,"Device %u status 0x%X\r\n",
          DeviceID,bq_pack.bq_devs[DeviceID].device_status);           
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);     
  
        for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
          sprintf(OutputString,"Cell %u voltage %u\r\n",i,
                 bq_pack.bq_devs[DeviceID].cell_voltage[i]);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
        }
        sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].alert_status);           
        sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);        
        sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].fault_status);          
        sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
        sprintf(OutputString,"Device %u cov alert on cells 0x%X\r\n",
                DeviceID,bq_pack.bq_devs[DeviceID].cov_fault);           
        sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
        sprintf(OutputString,"Device %u cuv alert on cells 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].cuv_fault);          
        sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
#endif

#ifdef UART_COMM  // Prepare the outgoing string & Send data
  strcpy(OutputString,"\r\nThe battery pack is in alert MODE\r\n");                
  putsUART((BYTE*)OutputString,strlen(OutputString));                  
        
  sprintf(OutputString,"alert detected on device %u\r\n",DeviceID);     
  putsUART((BYTE*)OutputString,strlen(OutputString));         
  sprintf(OutputString,"Device address %u\r\n",
          bq_pack.bq_devs[DeviceID].device_address);          
  putsUART((BYTE*)OutputString,strlen(OutputString));         

  sprintf(OutputString,"Device %u status 0x%X\r\n",DeviceID,
          bq_pack.bq_devs[DeviceID].device_status);            
  putsUART((BYTE*)OutputString,strlen(OutputString));          
        
  for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
          sprintf(OutputString,"Cell %u voltage %u\r\n",i,
                  bq_pack.bq_devs[DeviceID].cell_voltage[i]);           
          putsUART((BYTE*)OutputString,strlen(OutputString));          
  }
        
  sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
          bq_pack.bq_devs[DeviceID].alert_status);           
  putsUART((BYTE*)OutputString,strlen(OutputString));          
  sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
          bq_pack.bq_devs[DeviceID].fault_status);           
  putsUART((BYTE*)OutputString,strlen(OutputString));          
  sprintf(OutputString,"Device %u cov alert on cells 0x%X\r\n",
          DeviceID,bq_pack.bq_devs[DeviceID].cov_fault);           
  putsUART((BYTE*)OutputString,strlen(OutputString));          
  sprintf(OutputString,"Device %u cuv alert on cells 0x%X\r\n",
          DeviceID,bq_pack.bq_devs[DeviceID].cuv_fault);           
  putsUART((BYTE*)OutputString,strlen(OutputString));          
    
#endif  
}

//**
//* @brief Function Name: BQCommunicationProblemTask                                                 
//* @brief Description  : Identify if there is a communication wit
//* @param parameters   :                                                     
//* @return Value       :                                                     
//*/     
void BQCommunicationProblemTask(void){
// Prepare the outgoing string & Send data  

strcpy(OutputString,"\r\nThere is a communication problem with the BQ devices");                  
  
#ifdef USB_COMM  
  sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);                   
#endif

#ifdef UART_COMM // Send the response over UART
  putsUART((BYTE*)OutputString,strlen(OutputString));
#endif  
  
    //Go To Low Power Mode
  StateMachineTaskPointer = &GoToLowPowerMode; 
}

/**
* @brief Function Name: UARTCommunicationTask     .                                             
* @brief Description  : Sends Batery Pack information to the hosrt over uart.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
#ifdef UART_COMM
void UARTCommunicationTask(void){

    BYTE i;    
    bUARTDataReceived = FALSE;

    if(strchr(UARTRxBuffer,0x0D) != NULL)
    {    

      if(!(strcmp(UARTRxBuffer,"ch\r"))) // Compare to string #1, and respond
      {
        HOST_CONTROL_IN |= BIT0; //Set Charge mode active  
        strcpy(OutputString,"\r\nThe battery pack is charging\r\n");                                      
        putsUART((BYTE*)OutputString,strlen(OutputString));                  
      }// Compare to string #2, and respond 
      else if(!(strcmp(UARTRxBuffer, "di\r")))                                       
      {
        HOST_CONTROL_IN &= ~BIT0; //Set discharge mode active  
        strcpy(OutputString,"\r\nThe battery pack is discharging\r\n");                                     
        putsUART((BYTE*)OutputString,strlen(OutputString));                  
      }
      // Compare to string #3, and respond
      else if(!(strcmp(UARTRxBuffer, "p\r")))                              
      {                      
        strcpy(OutputString,"\r\nBattery Pack Data\r\n");                         
        putsUART((BYTE*)OutputString,strlen(OutputString));                  
     
        sprintf(OutputString,"Battery Pack Mode:%u\r\n",bq_pack.op_mode);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Battery Pack Voltage:%u\r\n",bq_pack.voltage);           
        putsUART((BYTE*)OutputString,strlen(OutputString));                
        sprintf(OutputString,"Battery Pack Lowest Cell Voltage:%u\r\n",
                bq_pack.lowest_cell_volts);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Battery Pack Highest Voltage:%u\r\n",
                bq_pack.highest_cell_volts);           
        putsUART((BYTE*)OutputString,strlen(OutputString));
        sprintf(OutputString,"Battery Pack Balancing Timer:%u\r\n",
                bq_pack.balancing_timer);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Battery Pack Charge/Discharge Timer:%u\r\n",
                bq_pack.chg_dschg_op_timer);           
        putsUART((BYTE*)OutputString,strlen(OutputString));     
        sprintf(OutputString,"Battery Pack Max Balancing Timer:%u\r\n",
                bq_pack.max_balance_timer);           
        putsUART((BYTE*)OutputString,strlen(OutputString));     
        sprintf(OutputString,"Battery Pack Max Imbalancing Fail Timer:%u\r\n",
                bq_pack.cell_imbalance_fail_timer);           
        putsUART((BYTE*)OutputString,strlen(OutputString));     
        sprintf(OutputString,"Battery Pack Temperature 1:%u\r\n",
                bq_pack.bq_devs[0].temperature1);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Battery Pack Temperature 2:%u\r\n",
                bq_pack.bq_devs[0].temperature2);           
        putsUART((BYTE*)OutputString,strlen(OutputString));   
        sprintf(OutputString,"OV delay Timer:%u\r\n",       //add 2017.06.22
                bq_pack.ov_output_delay_timer);
        putsUART((BYTE*)OutputString,strlen(OutputString));
      // Compare to string #3, and respond  
      }else if(!(strcmp(UARTRxBuffer, "c\r")))                              
      {                      
        static unsigned short DeviceID;
        
        strcpy(OutputString,"\r\nBQ76PL536 Data\r\n");             
        putsUART((BYTE*)OutputString,strlen(OutputString));                  
        sprintf(OutputString,"Device %u cell count %u\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].cell_count);           
        putsUART((BYTE*)OutputString,strlen(OutputString));           
        sprintf(OutputString,"Device %u address %u\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].device_address);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Device %u status 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].device_status);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        
        for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
          sprintf(OutputString,"Cell %u voltage %u\r\n",i,
                  bq_pack.bq_devs[DeviceID].cell_voltage[i]);           
          putsUART((BYTE*)OutputString,strlen(OutputString));          
        }
        
        sprintf(OutputString,"Device %u alert status 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].alert_status);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Device %u fault status 0x%X\r\n",DeviceID,
                bq_pack.bq_devs[DeviceID].fault_status);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Device %u cov fault on cells 0x%X\r\n",
                DeviceID,bq_pack.bq_devs[DeviceID].cov_fault);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Device %u cuv fault on cells 0x%X\r\n",
                DeviceID,bq_pack.bq_devs[DeviceID].cuv_fault);           
        putsUART((BYTE*)OutputString,strlen(OutputString));          
        sprintf(OutputString,"Device %u Imbalanced Cells 0x%X\r\n",
                DeviceID,(0x003F & find_imbalanced_cell(DeviceID)));           
        putsUART((BYTE*)OutputString,strlen(OutputString));          

        
        
        DeviceID++;
        if(DeviceID > (NUMBER_OF_BQ_DEVICES-1)){
           DeviceID = 0;
        }       
      }
      else// Handle other
      {
        strcpy(OutputString,"Invalid Command!\r\n");                                
        putsUART((BYTE*)OutputString,strlen(OutputString));               
        strcpy(OutputString,
      "\r\nMenu:\r\nCharge:ch\r\nDischarge:di\r\nPackInfo:p\r\nCellInfo:c\r\n");                                
        putsUART((BYTE*)OutputString,strlen(OutputString));               
  
      }   
       // Clear the string in preparation for the next one  
      for(i=0;i<MAX_STR_LENGTH;i++){                                                      
        UARTRxBuffer[i] = NULL;
        OutputString[i] = NULL;
      }
      
      UARTRxBufferIndex = &UARTRxBuffer[0]; //reset index       
    }
  
  //go to Low Power Mode
//  StateMachineTaskPointer = &GoToLowPowerMode;
}
#endif


/**
* @brief Function Name: USBCommunicationTask     .                                             
* @brief Description  : Sends Batery Pack information to the hosrt over USB.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
#ifdef USB_COMM
// Holds the new addition to the string
static char pieceOfString[MAX_STR_LENGTH] = ""; 
static unsigned short DeviceID;
void USBCommunicationTask(void)
{

  BYTE i;
  // Check the USB state and directly main loop accordingly
  switch(USB_connectionState())
  {
  case ST_USB_DISCONNECTED:
       break;
        
  case ST_USB_CONNECTED_NO_ENUM:
       break;
        
  case ST_ENUM_ACTIVE:
    // Some data is in the buffer; begin receiving a command              
    if(bDataReceived_event)
    {    
      bDataReceived_event = FALSE;
      // Add bytes in USB buffer to theCommand
      receiveDataInBuffer((BYTE*)pieceOfString,MAX_STR_LENGTH,1);                 
      strcat(wholeString,pieceOfString);     
      // Has the user pressed return yet?
      if(strchr(wholeString,0x0D) != NULL)                                                       
      {    
        // Compare to string #1, and respond
        if(!(strcmp(wholeString, "ch\r")))                                             
        {
          HOST_CONTROL_IN |= BIT0; //Set Charge mode active  
          strcpy(OutputString,"\r\nThe battery pack is charging\r\n");                                      
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);                 
        } // Compare to string #2, and respond
        else if(!(strcmp(wholeString, "di\r")))                                       
        {
          HOST_CONTROL_IN &= ~BIT0; //Set discharge mode active  
          strcpy(OutputString,"\r\nThe battery pack is discharging\r\n");                                     
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);                 
        }
        // Compare to string #3, and respond
        else if(!(strcmp(wholeString, "p\r")))                              
        {
          strcpy(OutputString,"\r\nBattery Pack Data\r\n");                         
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);             
          sprintf(OutputString,"Battery Pack Mode:%u\r\n",bq_pack.op_mode);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Battery Pack Voltage:%u\r\n",bq_pack.voltage);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);               
          sprintf(OutputString,"Battery Pack Lowest Cell Voltage:%u\r\n",
                  bq_pack.lowest_cell_volts);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Battery Pack Highest Voltage:%u\r\n",
                  bq_pack.highest_cell_volts);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);
          sprintf(OutputString,"Battery Pack Balancing Timer:%u\r\n",
                  bq_pack.balancing_timer);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Battery Pack Charge/Discharge Timer:%u\r\n",
                  bq_pack.chg_dschg_op_timer);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);    
          sprintf(OutputString,"Battery Pack Max Balancing Timer:%u\r\n",
                  bq_pack.max_balance_timer);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);    
          sprintf(OutputString,"Battery Pack Max Imbalancing Fail Timer:%u\r\n",
                  bq_pack.cell_imbalance_fail_timer);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);    
          sprintf(OutputString,"Battery Pack Temperature 1:%u\r\n",
                  bq_pack.bq_devs[0].temperature1);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Battery Pack Temperature 2:%u\r\n",
                  bq_pack.bq_devs[0].temperature2);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);  
          sprintf(OutputString,"OV delay Timer:%u\r\n",
                  bq_pack.ov_output_delay_timer);
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);
          
        }// Compare to string #3, and respond
        else if(!(strcmp(wholeString, "c\r")))                              
        {
          
          strcpy(OutputString,"\r\nBQ76PL536 Data\r\n");                         
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);                        
          sprintf(OutputString,"Device %u cell count %u\r\n",DeviceID,
                  bq_pack.bq_devs[DeviceID].cell_count);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);          
          sprintf(OutputString,"Device %u address %u\r\n",DeviceID,
                  bq_pack.bq_devs[DeviceID].device_address);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Device %u status 0x%X\r\n",DeviceID,
                  bq_pack.bq_devs[DeviceID].device_status);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);    
          for(i=0;i<MAX_CELLS_NUMBER_IN_BQ;i++){
            sprintf(OutputString,"Cell %u voltage %u\r\n",i,
                    bq_pack.bq_devs[DeviceID].cell_voltage[i]);           
            sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          }
          sprintf(OutputString,"Device %u alert status 0x%X\r\n",
                  DeviceID,bq_pack.bq_devs[DeviceID].alert_status);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Device %u fault status 0x%X\r\n",DeviceID,
                  bq_pack.bq_devs[DeviceID].fault_status);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Device %u cov fault on cells 0x%X\r\n",
                  DeviceID,bq_pack.bq_devs[DeviceID].cov_fault);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
          sprintf(OutputString,"Device %u cuv fault on cells 0x%X\r\n",
                  DeviceID,bq_pack.bq_devs[DeviceID].cuv_fault);           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);      			
          sprintf(OutputString,"Device %u Imbalanced Cells 0x%X\r\n",
                  DeviceID,(0x003F & find_imbalanced_cell(DeviceID)));           
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10); 
          DeviceID++;
          if(DeviceID > (NUMBER_OF_BQ_DEVICES-1)){
             DeviceID = 0;
          }       
        }
        else// Handle other
        {
          strcpy(OutputString,"\r\nInvalid Command!\r\n");                                
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);              
          strcpy(OutputString,
          "Menu:\r\nCharge:ch\r\nDischarge:di\r\nPack Info:p\r\nCellInfo:c\r\n");                                
          sendData_waitTilDone((BYTE*)OutputString,strlen(OutputString),1,10);         
        }// Clear the string in preparation for the next one                     
        for(i=0;i<MAX_STR_LENGTH;i++){                                                        
          wholeString[i] = NULL;
          pieceOfString[i] = NULL; 
          }//end of for
        }//end of if car return received conditional    
      }//end of data received conditional
          break;
          
   case ST_ENUM_SUSPENDED:
        break;
        
   case ST_ENUM_IN_PROGRESS:
        break;
   
   case ST_NOENUM_SUSPENDED:
        break;
        
   case ST_ERROR:
        break;
        
   default:
     break;
  }//end of switch-case sentence
    
  //go to Low Power Mode
  StateMachineTaskPointer = &GoToLowPowerMode;
}

#endif


/**
* @brief  Interrupts                             
*/
//ISR for the DRDY,ALERT,FAULT signals
static void NotUsedPortISR(void);
static void BQ76PL536_FAULT_ISR(void);
static void BQ76PL536_DRDY_ISR(void);
static void BQ76PL536_ALERT_ISR(void);


//ISR definition for each port, hast to be updated if the ports are reassigned
//to other pins
typedef void(*pt2Func)(void);

pt2Func pBQ76PL536PortsISR[]={//the order is defined by the port number

  NotUsedPortISR,         // Handler for PORT Px.x Interrupt
  NotUsedPortISR,         // Handler for PORT Px.0 Interrupt
  BQ76PL536_FAULT_ISR,    // Handler for PORT Px.1 Interrupt
  BQ76PL536_ALERT_ISR,    // Handler for PORT Px.2 Interrupt
  BQ76PL536_DRDY_ISR,     // Handler for PORT Px.3 Interrupt
  NotUsedPortISR,         // Handler for PORT Px.4 Interrupt   
  NotUsedPortISR,         // Handler for PORT Px.5 Interrupt   
  NotUsedPortISR,         // Handler for PORT Px.6 Interrupt   
  NotUsedPortISR,         // Handler for PORT Px.7 Interrupt   

};     


/**
* @brief Function Name: NotUsedPortISR.                                                 
* @brief Description  : Service Routine for the undefined port interrupts.
* @param parameters   : none                                                     
* @return Value       : none                                                     
*/     
static void NotUsedPortISR(void){
  
  BQ76PL536_FAULT_PxIFG = 0x00;         //clear the port interrupt flags
  BQ76PL536_DRDY_PxIFG = 0x00;          //clear the port interrupt flags
  BQ76PL536_ALERT_PxIFG = 0x00;         //clear the port interrupt flags
  
}

/**
* @brief Function Name: BQ76PL536_FAULT_ISR  .                                               
* @brief Description  : Service routine for the Fault port.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
static void BQ76PL536_FAULT_ISR(void){
	//go to the Fault task
  StateMachineTaskPointer = &BQFaultSignalTask;
  //Clear interrupt flags  
  BQ76PL536_FAULT_PxIFG &= ~IN_BQ_FAULT; 
}

/**
* @brief Function Name: BQ76PL536_ALERT_ISR  .                                               
* @brief Description  : Service routine for the ALERT port.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/      
static void BQ76PL536_ALERT_ISR(void){
	//go to the Alert Task
  StateMachineTaskPointer = &BQAlertSignalTask;
  //Clear interrupt flags
  BQ76PL536_ALERT_PxIFG &= ~IN_BQ_ALERT;
}


/**
* @brief Function Name: BQ76PL536_DRDY_ISR  .                                               
* @brief Description  : Service routine for the DRDY port.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/      
static void BQ76PL536_DRDY_ISR(void){
  //BQ76PL536 ADC conversion ready
  StateMachineTaskPointer = &DRDYSignalTask;  
  //Clear interrupt flags  
  BQ76PL536_DRDY_PxIFG  &= ~IN_BQ_DRDY; 

}

/**
* @brief Function Name : USCI1RX_ISR     .                                            
* @brief description: USCI1RX_ISR interrupt service routine, this ISR is 
*                     called when a byte is receveid in the USCI-UART, It
*                     detects the SLIP packets and identify the start/end
*                     of a message.
* @param Parameters  : None                                                    
* @return Value      : none                                                    
*/
#ifdef UART_COMM
#pragma vector=UCAxRX_VECTOR
__interrupt void USCIxRX_ISR(void){

  switch(UCAxIV)
  {
    
  case 0x02:  
    //fill the RX buffer
    *UARTRxBufferIndex++ = UCAxRXBUF;  
    //round buffer
    if(UARTRxBufferIndex >= &UARTRxBuffer[MAX_STR_LENGTH])
      UARTRxBufferIndex = &UARTRxBuffer[0]; //reset index       
    bUARTDataReceived = TRUE;  
    UCAxIFG &= ~UCAxRXIFG;           // Clear RX IFG    
    break;
  
  case 0x04://TX interrupt - disabled
    break;
  default:
    break;
        
  }
    // Clear LPM bits from 0(SR)      
  __bic_SR_register_on_exit(LOW_POWER_MODE); 
}  
#endif

/**
* @brief Function Name: Timer1SecISR   .                                              
* @brief Description  : Timer 1Sec interrupt service routine.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     

#pragma vector=Timer1Sec_TIMER_VECTOR
__interrupt void Timer1SecISR (void)
{
  
  //Go to Timer 1Sec ExpiredT ask
  StateMachineTaskPointer = &Timer1SecExpiredTask;
  
  //Toggle LED pin
  BQ76PL536_LED_PxOUT ^= OUT_BQ_LED;


   // Clear TACCRx interrupt flag
  Timer1Sec_TAxCCTLx &= ~CCIFG;


  // ---------add S.tei 170417 ------------//
//  if (bq_pack.highest_cell_volts >= 3750 | bq_pack.lowest_cell_volts<= 3300) {
//    if (bq_pack.lowest_cell_volts<= 3300) {
  if (((bq_pack.highest_cell_volts - bq_pack.lowest_cell_volts) > get_u32_value(BALANCE_VOLTS_THRESHOLD))){
	  Timer1Sec_TAxCCRx = 4096;
  }
  else {
	  Timer1Sec_TAxCCRx = 40960;
  }

  // Clear LPM bits from 0(SR)      
  __bic_SR_register_on_exit(LOW_POWER_MODE);

}

/**
* @brief Function Name: PORT_ISR  .                                                
* @brief Description  : IO interrupt service.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
#pragma vector=BQ76PL536_OUTPUTS_VECTOR   
__interrupt void PORT_ISR(void)
{
  /*Read port inputs*/
  
  // Jump to the corresponding ISR based on the Vector register
  pBQ76PL536PortsISR[(BQ76PL536_OUTPUTS_PxIV>>1)]();  

  
  // Clear LPM bits from 0(SR)      
  __bic_SR_register_on_exit(LOW_POWER_MODE);   
  
}

/**
* @brief Function Name: UNMI_ISR  .                                               
* @brief Description  : Service Routine for the UNMI vector.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/     
#ifdef USB_COMM
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR(VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
    case SYSUNIV_NONE:
      __no_operation();
      break;
    case SYSUNIV_NMIIFG:
      __no_operation();
      break;
    case SYSUNIV_OFIFG:
    // Clear OSC flaut Flags fault flags
      UCSCTL7 &= ~(DCOFFG+XT1LFOFFG+XT1HFOFFG+XT2OFFG); 
      SFRIFG1 &= ~OFIFG;   // Clear OFIFG fault flag
      break;
    case SYSUNIV_ACCVIFG:
      __no_operation();
      break;
    case SYSUNIV_BUSIFG:

      // If bus error occured - the cleaning of flag and re-initializing of 
      // USB is required.
      SYSBERRIV = 0;            // clear bus error flag
      USB_disable();            // Disable
      break;
    }
}
#endif

/**
* @brief  Local functions.                           
*/

/**
* @brief Function Name:  InitMCU.                                                
* @brief Description  :  Initializes the MSP430 peripherals and modules.
* @param parameters   :  none                                                   
* @return Value       :  none                                                   
*/
void InitMCU(void){
  
  __disable_interrupt(); // Disable global interrupts
  //Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  Init_Ports(); // Init ports (do first ports because clocks do change ports)
  SetVCore(PMMCOREV_3); // DVCC > 2.4V
  Init_Clock();

  //Init_Clock(); //init clocl system
#ifdef UART_COMM
  InitUART();   //init UART module
#endif
  
#ifdef USB_COMM  
  USB_init();   //init USB module
#endif  
  //Init SPI module
  init_spi();  
  //*Initialize IO ports for BQ Pack input/output signals*/
  InitBQ76PL536ports();  
  //*Initilize 1s system periodic interrupt*/
  Init1SecTimer();

#ifdef USB_COMM  
  // Enable various USB event handling routines
  USB_setEnabledEvents(kUSB_VbusOnEvent
                       +kUSB_VbusOffEvent
                       +kUSB_receiveCompletedEvent
                       +kUSB_dataReceivedEvent+kUSB_UsbSuspendEvent
                       +kUSB_UsbResumeEvent+kUSB_UsbResetEvent);
    
// See if we're already attached physically to USB, and if so, connect to it
// Normally applications don't invoke the event handlers, 
// but this is an exception.  
  if (USB_connectionInfo() & kUSB_vbusPresent)
    USB_handleVbusOnEvent();    
#endif   
  __enable_interrupt(); // enable global interrupts

}



/**
* @brief Function Name: Init_Clock .                                                
* @brief Description  : Initializes MSP430 clock module. 
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/    
VOID Init_Clock(VOID)
{
    // Initialization of clock module
    // XT2 used as USB PLL reference => USB_PLL_XT = 2
    P5SEL |= 0x0C;                            // enable XT2 pins

    SELECT_FLLREF(SELREF__REFOCLK);           // Set DCO FLL reference = REFO
    SELECT_ACLK(SELA__REFOCLK);               // Set ACLK = REFO 
    Init_FLL_Settle(MCLK_FREQ/1000, MCLK_FREQ/32768); // set FLL (DCOCLK)
    XT2_Start(0); //Lowest Current Consumption;
    
}
/**
* @brief Function Name: InitBQ76PL536ports .                                                 
* @brief Description  : init IO ports to connect the FAULT,CONV,DRDY & ALERT
* signals comming from the 'PL536 device.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/    
void InitBQ76PL536ports(void)
{
   
  //Inputs
  // I/O port control pad
  BQ76PL536_FAULT_PxSEL &= ~IN_BQ_FAULT;
  BQ76PL536_ALERT_PxSEL &= ~IN_BQ_ALERT; 
  BQ76PL536_DRDY_PxSEL  &= ~IN_BQ_DRDY; 
  
  // Set pull up/down resistor configuration
  BQ76PL536_FAULT_PxREN &= ~IN_BQ_FAULT;
  BQ76PL536_ALERT_PxREN &= ~IN_BQ_ALERT; 
  BQ76PL536_DRDY_PxREN  &= ~IN_BQ_DRDY;   
  
  // Set port direction as input
  BQ76PL536_FAULT_PxDIR &= ~IN_BQ_FAULT;
  BQ76PL536_ALERT_PxDIR &= ~IN_BQ_ALERT; 
  BQ76PL536_DRDY_PxDIR  &= ~IN_BQ_DRDY;   
  
  // Clear interrupt flags
  BQ76PL536_FAULT_PxIFG &= ~IN_BQ_FAULT;
  BQ76PL536_ALERT_PxIFG &= ~IN_BQ_ALERT; 
  BQ76PL536_DRDY_PxIFG  &= ~IN_BQ_DRDY; 

  // interrupts enabled 
  BQ76PL536_FAULT_PxIE |= IN_BQ_FAULT;
  BQ76PL536_ALERT_PxIE |= IN_BQ_ALERT; 
  BQ76PL536_DRDY_PxIE  |= IN_BQ_DRDY;  
  
  //Output
  //I/O port control pad
  BQ76PL536_CONV_PxSEL &= ~OUT_BQ_CONV;
  
  //Set pin to Logic Level 0
  BQ76PL536_CONV_PxOUT &= ~OUT_BQ_CONV;
  
  //Set pull up/down resistor configuration
  BQ76PL536_CONV_PxREN &= ~OUT_BQ_CONV; 
  
  //Set port direction as output
  BQ76PL536_CONV_PxDIR |= OUT_BQ_CONV;  
 
  //LED  pin
  // I/O port control pad
  BQ76PL536_CONV_PxSEL &= ~OUT_BQ_LED;
  
  //Set pin to Logic Level 1
  BQ76PL536_CONV_PxOUT |= OUT_BQ_LED;
  
  // Set pull up/down resistor configuration
  BQ76PL536_CONV_PxREN &= ~OUT_BQ_LED; 
  
  // Set port direction as output
  BQ76PL536_CONV_PxDIR |= OUT_BQ_LED;
  
  BQ76PL536_CONV_PxSEL &= ~(OUT_BQ_CONV|OUT_BQ_LED);

  //Output TEMP add by S.tei 12704 33pin
  //I/O port control pad
  BQ76PL536_TEMP_PxSEL &= ~OUT_BQ_TEMP;

  //Set pin to Logic Level 0
  BQ76PL536_TEMP_PxOUT &= ~OUT_BQ_TEMP;

  //Set pull up/down resistor configuration
  BQ76PL536_TEMP_PxREN &= ~OUT_BQ_TEMP;

  //Set port direction as output
  BQ76PL536_TEMP_PxDIR |= OUT_BQ_TEMP;

  //Output FAULT_O add by S.tei 12704 32pin
  //I/O port control pad
  BQ76PL536_FAULT_O_PxSEL &= ~OUT_BQ_FAULT_O;

  //Set pin to Logic Level 0
  BQ76PL536_FAULT_O_PxOUT &= ~OUT_BQ_FAULT_O;

  //Set pull up/down resistor configuration
  BQ76PL536_FAULT_O_PxREN &= ~OUT_BQ_FAULT_O;

  //Set port direction as output
  BQ76PL536_FAULT_O_PxDIR |= OUT_BQ_FAULT_O;

  //Output OV add by S.tei 12704 34pin
  //I/O port control pad
  BQ76PL536_OV_PxSEL &= ~OUT_BQ_OV;

  //Set pin to Logic Level 0
  BQ76PL536_OV_PxOUT &= ~OUT_BQ_OV;

  //Set pull up/down resistor configuration
  BQ76PL536_OV_PxREN &= ~OUT_BQ_OV;

  //Set port direction as output
  BQ76PL536_OV_PxDIR |= OUT_BQ_OV;

}



/**
* @brief Function Name: Init1SecTimer     .                                             
* @brief Description  : initializes the 1 sec timer, 
* TimeAx used to create a 1Sec delay.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/
void Init1SecTimer(void)
{
  /*Initialize TimerAx in continuous mode with 1us tick*/
  Timer1Sec_TAxCTL = MC_0;                             //Stop TA0
  Timer1Sec_TAxCTL |= TACLR;                           //Clear Timer register  
  Timer1Sec_TAxCCTLx = 0 ;                              //Stop TAx capture

  Timer1Sec_TAxCCRx = 4096;

  Timer1Sec_TAxCTL = TASSEL_1 | MC_1 | ID_3;  //ACLK = 32.768kHz
                                              //=> TCLK = 244.14us
  Timer1Sec_TAxCCTLx &= ~CCIFG;               // Clear TACCRx interrupt flag
  Timer1Sec_TAxCCTLx |= CCIE;                 // TACCRx interrupt enabled
}

/**
* @brief Function Name: Disable1SecTimer.                                                  
* @brief Description  : Disables the 1 sec timer.
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/
void Disable1SecTimer(void)
{
  Timer1Sec_TAxCTL &= MC_0;                             // Stop TAx
  Timer1Sec_TAxCTL |= TACLR;                           // Clear TAx
}

/**
* @brief Function Name: Init_Ports.                                                  
* @brief Description  : Configures IO ports
* @param parameters   : none                                                    
* @return Value       : none                                                    
*/    
VOID Init_Ports(VOID)
{
    // Initialization of ports all unused pins as outputs with low-level

    // set all ports  to low on all pins
    PAOUT   =   0x0000;
    PASEL   =   0x0000;
    PADIR   =   0xFFFF;

    PBOUT   =   0x0000;
    PBSEL   =   0x0000;
    PBDIR   =   0xFFFF;

    PCOUT   =   0x0000;
    PCSEL   =   0x0000;
    PCDIR   =   0xFFFF;

  //  PDOUT   =   0x0000;
  //  PDSEL   =   0x0000;
  //  PDDIR   =   0xFFFF;


    PJDIR   =   0xFFFF;
    PJOUT   =   0x0000;
}

//EOF


