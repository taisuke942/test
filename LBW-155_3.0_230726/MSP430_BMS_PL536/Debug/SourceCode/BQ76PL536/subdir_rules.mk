################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
SourceCode/BQ76PL536/%.obj: ../SourceCode/BQ76PL536/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/bin/cl430" -vmspx --abi=coffabi --code_model=large --data_model=restricted --near_data=globals -O3 --opt_for_speed=5 -g --optimize_with_debug=on --include_path="C:/ti/ccs1220/ccs/ccs_base/msp430/include" --include_path="C:/ti/ccs1220/ccs/tools/compiler/msp430_4.1.1/include" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/BQ76PL536" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/Common" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/SPI" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/UART" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/USB_CDC_API" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode/USB_Common" --include_path="C:/ti/hashimoto/LBW-155_3.0_230628/MSP430_BMS_PL536/SourceCode" --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="SourceCode/BQ76PL536/$(basename $(<F)).d_raw" --obj_directory="SourceCode/BQ76PL536" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


