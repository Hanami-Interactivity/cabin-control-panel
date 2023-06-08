################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.cpp 

C_SRCS += \
L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel\esp8266.c 

C_DEPS += \
.\libraries\Adafruit_NeoPixel\esp8266.c.d 

LINK_OBJ += \
.\libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.cpp.o \
.\libraries\Adafruit_NeoPixel\esp8266.c.o 

CPP_DEPS += \
.\libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.cpp.o: L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel\Adafruit_NeoPixel.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"L:\Sloeber\arduinoPlugin\packages\teensy\tools\teensy-compile\11.3.1/arm/bin/arm-none-eabi-g++" -c -O2 -g -Wall -ffunction-sections -fdata-sections -nostdlib -MMD -std=gnu++14 -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -D__IMXRT1062__ -DTEENSYDUINO=158 -DARDUINO=10812 -DARDUINO_TEENSY41 -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_FRENCH "-IC:\Users\natha\Documents\sloeber-workspace\cabin_control_panel\Release/pch"   -I"L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\cores\teensy4" -I"C:\Users\natha\Documents\Arduino\libraries\WS2812FX\src" -I"L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel" -I"D:\DMII - Gobelins\M2\Projet final\Librairies\WS2812b_Effect" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries\Adafruit_NeoPixel\esp8266.c.o: L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel\esp8266.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"L:\Sloeber\arduinoPlugin\packages\teensy\tools\teensy-compile\11.3.1/arm/bin/arm-none-eabi-gcc" -c -O2 -g -Wall -ffunction-sections -fdata-sections -nostdlib -MMD  -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -D__IMXRT1062__ -DTEENSYDUINO=158 -DARDUINO=10812 -DARDUINO_TEENSY41 -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_FRENCH   -I"L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\cores\teensy4" -I"C:\Users\natha\Documents\Arduino\libraries\WS2812FX\src" -I"L:\Sloeber\arduinoPlugin\packages\teensy\hardware\avr\1.58.1\libraries\Adafruit_NeoPixel" -I"D:\DMII - Gobelins\M2\Projet final\Librairies\WS2812b_Effect" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


