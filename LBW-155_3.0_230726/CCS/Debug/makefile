################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.1.0

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./SourceCode/BQ76PL536/data_flash.obj" \
"./SourceCode/BQ76PL536/bq_pack.obj" \
"./SourceCode/Common/hal_pmm.obj" \
"./SourceCode/Common/hal_UCS.obj" \
"./SourceCode/Common/TLV.obj" \
"./SourceCode/SPI/spi_if.obj" \
"./SourceCode/UART/UART.obj" \
"./SourceCode/USB_CDC_API/UsbCdc.obj" \
"./SourceCode/USB_Common/usb_eventHandling.obj" \
"./SourceCode/USB_Common/usb.obj" \
"./SourceCode/USB_Common/dma.obj" \
"./SourceCode/USB_Common/descriptors.obj" \
"./SourceCode/USB_Common/UsbIsr.obj" \
"./SourceCode/main.obj" \
"./SourceCode/USBCDC_constructs.obj" \
-l"libc.a" \
"../lnk_msp430f5529.cmd" \
"../msp430f5529.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include SourceCode/subdir_vars.mk
-include SourceCode/USB_Common/subdir_vars.mk
-include SourceCode/USB_CDC_API/subdir_vars.mk
-include SourceCode/UART/subdir_vars.mk
-include SourceCode/SPI/subdir_vars.mk
-include SourceCode/Common/subdir_vars.mk
-include SourceCode/BQ76PL536/subdir_vars.mk
-include subdir_rules.mk
-include SourceCode/subdir_rules.mk
-include SourceCode/USB_Common/subdir_rules.mk
-include SourceCode/USB_CDC_API/subdir_rules.mk
-include SourceCode/UART/subdir_rules.mk
-include SourceCode/SPI/subdir_rules.mk
-include SourceCode/Common/subdir_rules.mk
-include SourceCode/BQ76PL536/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MSP430_BMS_PL536.out

# Tool invocations
MSP430_BMS_PL536.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.0/bin/cl430" -vmspx --abi=coffabi -O3 --opt_for_speed=5 -g --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full -z --stack_size=160 -m"MSP430_BMS_PL536.map" --heap_size=160 --use_hw_mpy=F5 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.0/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.0/include" --reread_libs --warn_sections --rom_model -o "MSP430_BMS_PL536.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "MSP430_BMS_PL536.out"
	-$(RM) "SourceCode\USBCDC_constructs.pp" "SourceCode\main.pp" "SourceCode\USB_Common\UsbIsr.pp" "SourceCode\USB_Common\descriptors.pp" "SourceCode\USB_Common\dma.pp" "SourceCode\USB_Common\usb.pp" "SourceCode\USB_Common\usb_eventHandling.pp" "SourceCode\USB_CDC_API\UsbCdc.pp" "SourceCode\UART\UART.pp" "SourceCode\SPI\spi_if.pp" "SourceCode\Common\TLV.pp" "SourceCode\Common\hal_UCS.pp" "SourceCode\Common\hal_pmm.pp" "SourceCode\BQ76PL536\bq_pack.pp" "SourceCode\BQ76PL536\data_flash.pp" 
	-$(RM) "SourceCode\USBCDC_constructs.obj" "SourceCode\main.obj" "SourceCode\USB_Common\UsbIsr.obj" "SourceCode\USB_Common\descriptors.obj" "SourceCode\USB_Common\dma.obj" "SourceCode\USB_Common\usb.obj" "SourceCode\USB_Common\usb_eventHandling.obj" "SourceCode\USB_CDC_API\UsbCdc.obj" "SourceCode\UART\UART.obj" "SourceCode\SPI\spi_if.obj" "SourceCode\Common\TLV.obj" "SourceCode\Common\hal_UCS.obj" "SourceCode\Common\hal_pmm.obj" "SourceCode\BQ76PL536\bq_pack.obj" "SourceCode\BQ76PL536\data_flash.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
