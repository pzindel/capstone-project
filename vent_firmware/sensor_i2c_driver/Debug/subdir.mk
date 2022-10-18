################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HDC2080.c \
../app.c 

OBJS += \
./HDC2080.o \
./app.o 

C_DEPS += \
./HDC2080.d \
./app.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\sensor_i2c_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE" -I"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE/CMSIS_Driver" -I"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE" -isystem"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE/CMSIS_Driver" -isystem"S:\pieri\onsemi-workspace\sensor_i2c_driver/RTE/Device/RSL15" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


