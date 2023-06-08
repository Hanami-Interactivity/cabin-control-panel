################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\WS2812b_Effect\subdir.mk
-include libraries\WS2812FX\src\subdir.mk
-include libraries\Adafruit_NeoPixel\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release\arduino.ar \

ELF += \
cabin_control_panel.elf \

HEX += \
cabin_control_panel.hex \



#bootloaderTest
BurnBootLoader: 
	@echo trying to burn bootloader ${bootloader.tool}
	${tools.${bootloader.tool}.erase.pattern}
	${tools.${bootloader.tool}.bootloader.pattern}

uploadWithBuild: all
	@echo trying to build and upload with upload tool ${upload.tool}
	${tools.${upload.tool}.upload.pattern}

uploadWithoutBuild: 
	@echo trying to upload without build with upload tool ${upload.tool}
	${tools.${upload.tool}.upload.pattern}
    
uploadWithProgrammerWithBuild: all
	@echo trying to build and upload with programmer ${program.tool}
	${tools.${program.tool}.program.pattern}

uploadWithProgrammerWithoutBuild: 
	@echo trying to upload with programmer ${program.tool} without build
	${tools.${program.tool}.program.pattern}

# All Target
all: cabin_control_panel

# Tool invocations
cabin_control_panel: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"L:\Sloeber\arduinoPlugin\packages\teensy\tools\teensy-compile\11.3.1/arm/bin/arm-none-eabi-size" -A "C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release/cabin_control_panel.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"L:\Sloeber\arduinoPlugin\packages\teensy\tools\teensy-compile\11.3.1/arm/bin/arm-none-eabi-gcc-ar" rcs    C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

cabin_control_panel.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"L:\Sloeber\arduinoPlugin\packages\teensy\tools\teensy-compile\11.3.1/arm/bin/arm-none-eabi-gcc" -O2 -Wl,--gc-sections,--relax "-TL:/Sloeber/arduinoPlugin/packages/teensy/hardware/avr/1.58.1/cores/teensy4/imxrt1062_t41.ld"  -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -o "C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release/cabin_control_panel.elf"   $(LINK_OBJ)   C:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release/arduino.ar  "-LC:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release" -larm_cortexM7lfsp_math -lm -lstdc++
	@echo 'Finished building: $@'
	@echo ' '

cabin_control_panel.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${recipe.objcopy.eep.pattern}
	${recipe.objcopy.hex.pattern}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ..\makefile.targets
