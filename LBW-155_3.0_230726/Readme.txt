Multi-Cell Li-Ion Battery Management System with MSP430 and BQ76PL536
Texas Instruments, Inc.

********************************************************************************
Revision History
********************************************************************************
Ver 1.0 - December 2010 (Daniel Torres)
-first release

NOTES:
-This folder contains the source code and projects for the SLAA478 application 
report "Multi-Cell Lio-Ion Battery Management System with the MSP430 and 
the BQ76PL536"
-The IAR folder contains the project files compatible with IAR Embedded Work 
Bench 5.1 or higher.
The CCS folder contains the project files compatible with Code Composer 
Studio 4.2.1 or higher
-The docs folde contained inside the project folder contain the detail software 
documentation. Refer to the "INDEX_OPEN_THIS_FILE.html" to navigate through the 
software documents.


********************************************************************************
Project File Listing
********************************************************************************
|--MSP430_CDC.inf           :USB dirver for the MSP430 USB CDC device
|--readme.txt               :this file
|--IAR                      :contains the IAR workbench(5.1) version of the SLAA478 application software
  |--Docs                   :contains a detail description of the software
  |--settings              :contains the IAR project settings
  |--MSP430_BMS_PL536.eww   :IAR workbench IDE workspace file
  |--MSP430_BMS_PL536.ewd   :IAR workbench file
  |--MSP430_BMS_PL536.ewp   :IAR workbench project file  
  |--MSP430_BMS_PL536.eww   :IAR workbench dep file  
  |--SourceCode             :contains the project source code files
    |--main.c               :contains the main entry point 
    |--main.h               :contains the system definitions 
    |--USBCDC_constructs.c  :contains the USB CDC definitions 
    |--USBCDC_constructs.h  :contains the USB CDC definitions 
    |--BQ76PL536            :contains the Battery Pack and BQ devices definitions
    |--Common               :containing MSP430 low-level HAL (SLAA448)
    |--SPI                  :contains the SPI bus definitions      
    |--UART                 :contains the UART definitions      
    |--USB_CDC_API          :contains the USB CDC API functions  
    |--USB_Common           :contains the USB common files 
|--CCS                      :contains the CCS (V4.2.1) version of the SLAA478 application software
  |--Docs                   :contains a detail description of the software
  |--.settings              :contains the project settings
  |--.launches              :contains the specific files for CCS  
  |--.ccsprojec             :CCS project file
  |--.cdtbuild              :CCS file
  |--.cdtproject            :CCS file  
  |--MSP430F5529.ccxml      :MSP430F5529 XML file  
  |--MSP430f5529.cmd        :Hardcoded memory locations for USB functions
  |--lnk_msp430f5529.cmd    :project linker command file
  |--SourceCode             :contains the project source code files
    |--main.c               :contains the main entry point 
    |--main.h               :contains the system definitions 
    |--USBCDC_constructs.c  :contains the USB CDC definitions 
    |--USBCDC_constructs.h  :contains the USB CDC definitions 
    |--BQ76PL536            :contains the Battery Pack and BQ devices definitions
    |--Common               :containing MSP430 low-level HAL (SLAA448)
    |--SPI                  :contains the SPI bus definitions      
    |--UART                 :contains the UART definitions      
    |--USB_CDC_API          :contains the USB CDC API functions  
    |--USB_Common           :contains the USB common files 