################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/peripherals/adc.c \
../Core/Src/peripherals/fdcan.c \
../Core/Src/peripherals/gpio.c \
../Core/Src/peripherals/tim.c 

OBJS += \
./Core/Src/peripherals/adc.o \
./Core/Src/peripherals/fdcan.o \
./Core/Src/peripherals/gpio.o \
./Core/Src/peripherals/tim.o 

C_DEPS += \
./Core/Src/peripherals/adc.d \
./Core/Src/peripherals/fdcan.d \
./Core/Src/peripherals/gpio.d \
./Core/Src/peripherals/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/peripherals/%.o Core/Src/peripherals/%.su Core/Src/peripherals/%.cyclo: ../Core/Src/peripherals/%.c Core/Src/peripherals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Core/Inc/peripherals -I../Core/Inc/processes -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Core/Inc/sys -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-peripherals

clean-Core-2f-Src-2f-peripherals:
	-$(RM) ./Core/Src/peripherals/adc.cyclo ./Core/Src/peripherals/adc.d ./Core/Src/peripherals/adc.o ./Core/Src/peripherals/adc.su ./Core/Src/peripherals/fdcan.cyclo ./Core/Src/peripherals/fdcan.d ./Core/Src/peripherals/fdcan.o ./Core/Src/peripherals/fdcan.su ./Core/Src/peripherals/gpio.cyclo ./Core/Src/peripherals/gpio.d ./Core/Src/peripherals/gpio.o ./Core/Src/peripherals/gpio.su ./Core/Src/peripherals/tim.cyclo ./Core/Src/peripherals/tim.d ./Core/Src/peripherals/tim.o ./Core/Src/peripherals/tim.su

.PHONY: clean-Core-2f-Src-2f-peripherals

