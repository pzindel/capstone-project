################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/clock.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/flash_copier.c \
../RTE/Device/RSL15/gpio_driver.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/lsad.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/power_modes.c \
../RTE/Device/RSL15/pwm_driver.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/rffe.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/sassert.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/cmsis/source/sbrk.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/cmsis/source/start.c \
../RTE/Device/RSL15/system_rsl15.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/trim.c \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/uart.c 

S_UPPER_SRCS += \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/acs_write_asm.S \
C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/go_to_sleep_asm.S \
../RTE/Device/RSL15/startup.S 

OBJS += \
./RTE/Device/RSL15/acs_write_asm.o \
./RTE/Device/RSL15/clock.o \
./RTE/Device/RSL15/flash_copier.o \
./RTE/Device/RSL15/go_to_sleep_asm.o \
./RTE/Device/RSL15/gpio_driver.o \
./RTE/Device/RSL15/lsad.o \
./RTE/Device/RSL15/power_modes.o \
./RTE/Device/RSL15/pwm_driver.o \
./RTE/Device/RSL15/rffe.o \
./RTE/Device/RSL15/sassert.o \
./RTE/Device/RSL15/sbrk.o \
./RTE/Device/RSL15/start.o \
./RTE/Device/RSL15/startup.o \
./RTE/Device/RSL15/system_rsl15.o \
./RTE/Device/RSL15/trim.o \
./RTE/Device/RSL15/uart.o 

S_UPPER_DEPS += \
./RTE/Device/RSL15/acs_write_asm.d \
./RTE/Device/RSL15/go_to_sleep_asm.d \
./RTE/Device/RSL15/startup.d 

C_DEPS += \
./RTE/Device/RSL15/clock.d \
./RTE/Device/RSL15/flash_copier.d \
./RTE/Device/RSL15/gpio_driver.d \
./RTE/Device/RSL15/lsad.d \
./RTE/Device/RSL15/power_modes.d \
./RTE/Device/RSL15/pwm_driver.d \
./RTE/Device/RSL15/rffe.d \
./RTE/Device/RSL15/sassert.d \
./RTE/Device/RSL15/sbrk.d \
./RTE/Device/RSL15/start.d \
./RTE/Device/RSL15/system_rsl15.d \
./RTE/Device/RSL15/trim.d \
./RTE/Device/RSL15/uart.d 


# Each subdirectory must supply rules for building sources it contributes
RTE/Device/RSL15/acs_write_asm.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/acs_write_asm.S RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -D_RTE_ -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/clock.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/clock.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/flash_copier.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/flash_copier.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/go_to_sleep_asm.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/go_to_sleep_asm.S RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -D_RTE_ -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/%.o: ../RTE/Device/RSL15/%.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/lsad.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/lsad.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/power_modes.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/power_modes.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/rffe.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/rffe.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/sassert.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/sassert.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/sbrk.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/cmsis/source/sbrk.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/start.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/cmsis/source/start.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/%.o: ../RTE/Device/RSL15/%.S RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -D_RTE_ -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/trim.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/trim.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

RTE/Device/RSL15/uart.o: C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/HAL/source/uart.c RTE/Device/RSL15/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DRSL15_CID=202 -D_RTE_ -I"S:\pieri\onsemi-workspace\motor_pwm_driver\include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -I"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/pieri/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE" -isystem"S:\pieri\onsemi-workspace\motor_pwm_driver/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


