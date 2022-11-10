################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Servo.c \
../app.c 

OBJS += \
./Servo.o \
./app.o 

C_DEPS += \
./Servo.d \
./app.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


