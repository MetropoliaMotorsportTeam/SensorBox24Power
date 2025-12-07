################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sys/stm32g4xx_hal_msp.c \
../Core/Src/sys/stm32g4xx_it.c \
../Core/Src/sys/syscalls.c \
../Core/Src/sys/sysmem.c \
../Core/Src/sys/system_stm32g4xx.c 

OBJS += \
./Core/Src/sys/stm32g4xx_hal_msp.o \
./Core/Src/sys/stm32g4xx_it.o \
./Core/Src/sys/syscalls.o \
./Core/Src/sys/sysmem.o \
./Core/Src/sys/system_stm32g4xx.o 

C_DEPS += \
./Core/Src/sys/stm32g4xx_hal_msp.d \
./Core/Src/sys/stm32g4xx_it.d \
./Core/Src/sys/syscalls.d \
./Core/Src/sys/sysmem.d \
./Core/Src/sys/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sys/%.o Core/Src/sys/%.su Core/Src/sys/%.cyclo: ../Core/Src/sys/%.c Core/Src/sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Core/Inc/peripherals -I../Core/Inc/processes -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Core/Inc/sys -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sys

clean-Core-2f-Src-2f-sys:
	-$(RM) ./Core/Src/sys/stm32g4xx_hal_msp.cyclo ./Core/Src/sys/stm32g4xx_hal_msp.d ./Core/Src/sys/stm32g4xx_hal_msp.o ./Core/Src/sys/stm32g4xx_hal_msp.su ./Core/Src/sys/stm32g4xx_it.cyclo ./Core/Src/sys/stm32g4xx_it.d ./Core/Src/sys/stm32g4xx_it.o ./Core/Src/sys/stm32g4xx_it.su ./Core/Src/sys/syscalls.cyclo ./Core/Src/sys/syscalls.d ./Core/Src/sys/syscalls.o ./Core/Src/sys/syscalls.su ./Core/Src/sys/sysmem.cyclo ./Core/Src/sys/sysmem.d ./Core/Src/sys/sysmem.o ./Core/Src/sys/sysmem.su ./Core/Src/sys/system_stm32g4xx.cyclo ./Core/Src/sys/system_stm32g4xx.d ./Core/Src/sys/system_stm32g4xx.o ./Core/Src/sys/system_stm32g4xx.su

.PHONY: clean-Core-2f-Src-2f-sys

