################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SourceCode/SPI/spi_if.obj: ../SourceCode/SPI/spi_if.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.0/bin/cl430" -vmspx --abi=coffabi -O3 --opt_for_speed=5 -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.0/include" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/BQ76PL536" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/Common" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/SPI" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/UART" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/USB_CDC_API" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode/USB_Common" --include_path="C:/Users/stei/workspace_v5_2/begin_working_121108/SLAA478_1.2_A/CCS/SourceCode" --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="SourceCode/SPI/spi_if.pp" --obj_directory="SourceCode/SPI" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


