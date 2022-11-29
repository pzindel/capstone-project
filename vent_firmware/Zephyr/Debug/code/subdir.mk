################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/app_bass.c \
../code/app_customss.c \
../code/app_init.c \
../code/app_msg_handler.c \
../code/app_temperature_sensor.c 

OBJS += \
./code/app_bass.o \
./code/app_customss.o \
./code/app_init.o \
./code/app_msg_handler.o \
./code/app_temperature_sensor.o 

C_DEPS += \
./code/app_bass.d \
./code/app_customss.d \
./code/app_init.d \
./code/app_msg_handler.d \
./code/app_temperature_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m33 -march=armv8-m.main+dsp -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DRSL15_CID=202 -DCFG_FULL_BUILD_CONFIG -DCFG_FULL_BUILD_CONFIG -D_RTE_ -I"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr\include" -I"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr\RTE\CMSIS_Driver" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include/ble" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include/ble/profiles" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/ble_abstraction/ble_common/include" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/ble_abstraction/ble_profiles/include" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/swmTrace/include" -I"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/swmTrace/include/uart_common" -I"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE" -I"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE/CMSIS_Driver" -I"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE/Device/RSL15" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ARM/CMSIS/5.8.0/CMSIS/Driver/Include" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include/ble" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/include/ble/profiles" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/ble_abstraction/ble_common/include" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/ble_abstraction/ble_profiles/include" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/drivers" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/swmTrace/include" -isystem"C:/Users/James Le/AppData/Local/Arm/Packs/ONSemiconductor/RSL15/1.2.150/firmware/source/lib/swmTrace/include/uart_common" -isystem"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE" -isystem"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE/CMSIS_Driver" -isystem"D:\OneDrive - Conestoga College\Courses\EECE8040\capstone-project\vent_firmware\Zephyr/RTE/Device/RSL15" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


