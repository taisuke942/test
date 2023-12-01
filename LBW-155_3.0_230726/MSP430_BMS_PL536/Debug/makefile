################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./SourceCode/BQ76PL536/bq_pack.obj" \
"./SourceCode/BQ76PL536/data_flash.obj" \
"./SourceCode/Common/TLV.obj" \
"./SourceCode/Common/hal_UCS.obj" \
"./SourceCode/Common/hal_pmm.obj" \
"./SourceCode/SPI/spi_if.obj" \
"./SourceCode/UART/UART.obj" \
"./SourceCode/USBCDC_constructs.obj" \
"./SourceCode/main.obj" \
"./SourceCode/USB_CDC_API/UsbCdc.obj" \
"./SourceCode/USB_Common/UsbIsr.obj" \
"./SourceCode/USB_Common/descriptors.obj" \
"./SourceCode/USB_Common/dma.obj" \
"./SourceCode/USB_Common/usb.obj" \
"./SourceCode/USB_Common/usb_eventHandling.obj" \
"../lnk_msp430f5529.cmd" \
"../msp430f5529.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/lib/libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include SourceCode/BQ76PL536/subdir_vars.mk
-include SourceCode/Common/subdir_vars.mk
-include SourceCode/SPI/subdir_vars.mk
-include SourceCode/UART/subdir_vars.mk
-include SourceCode/subdir_vars.mk
-include SourceCode/USB_CDC_API/subdir_vars.mk
-include SourceCode/USB_Common/subdir_vars.mk
-include subdir_rules.mk
-include SourceCode/BQ76PL536/subdir_rules.mk
-include SourceCode/Common/subdir_rules.mk
-include SourceCode/SPI/subdir_rules.mk
-include SourceCode/UART/subdir_rules.mk
-include SourceCode/subdir_rules.mk
-include SourceCode/USB_CDC_API/subdir_rules.mk
-include SourceCode/USB_Common/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MSP430_BMS_PL536.out \

EXE_OUTPUTS__QUOTED += \
"MSP430_BMS_PL536.out" \

BIN_OUTPUTS += \
MSP430_BMS_PL536.hex \

BIN_OUTPUTS__QUOTED += \
"MSP430_BMS_PL536.hex" \


# All Target
all: MSP430_BMS_PL536.out secondary-outputs

# Tool invocations
MSP430_BMS_PL536.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/bin/cl430" -vmspx --abi=coffabi --code_model=large --data_model=restricted --near_data=globals -O3 --opt_for_speed=5 -g --optimize_with_debug=on --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full -z --stack_size=160 -m"MSP430_BMS_PL536.map" --heap_size=160 --use_hw_mpy=F5 -i"C:/ti/ccs1220/ccs/ccs_base/msp430/include" -i"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/lib" -i"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/include" -i"C:/ti/ccs1220/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" --reread_libs --warn_sections --xml_link_info="MSP430_BMS_PL536_linkInfo.xml" --rom_model -o "MSP430_BMS_PL536.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

MSP430_BMS_PL536.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/bin/hex430" --memwidth=8 --romwidth=8 --diag_wrap=off -o "MSP430_BMS_PL536.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "SourceCode\BQ76PL536\bq_pack.obj" "SourceCode\BQ76PL536\data_flash.obj" "SourceCode\Common\TLV.obj" "SourceCode\Common\hal_UCS.obj" "SourceCode\Common\hal_pmm.obj" "SourceCode\SPI\spi_if.obj" "SourceCode\UART\UART.obj" "SourceCode\USBCDC_constructs.obj" "SourceCode\main.obj" "SourceCode\USB_CDC_API\UsbCdc.obj" "SourceCode\USB_Common\UsbIsr.obj" "SourceCode\USB_Common\descriptors.obj" "SourceCode\USB_Common\dma.obj" "SourceCode\USB_Common\usb.obj" "SourceCode\USB_Common\usb_eventHandling.obj" 
	-$(RM) "SourceCode\BQ76PL536\bq_pack.d" "SourceCode\BQ76PL536\data_flash.d" "SourceCode\Common\TLV.d" "SourceCode\Common\hal_UCS.d" "SourceCode\Common\hal_pmm.d" "SourceCode\SPI\spi_if.d" "SourceCode\UART\UART.d" "SourceCode\USBCDC_constructs.d" "SourceCode\main.d" "SourceCode\USB_CDC_API\UsbCdc.d" "SourceCode\USB_Common\UsbIsr.d" "SourceCode\USB_Common\descriptors.d" "SourceCode\USB_Common\dma.d" "SourceCode\USB_Common\usb.d" "SourceCode\USB_Common\usb_eventHandling.d" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

