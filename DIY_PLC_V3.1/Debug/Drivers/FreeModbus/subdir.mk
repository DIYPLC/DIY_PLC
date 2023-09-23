################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FreeModbus/mb.c \
../Drivers/FreeModbus/mb_m.c 

OBJS += \
./Drivers/FreeModbus/mb.o \
./Drivers/FreeModbus/mb_m.o 

C_DEPS += \
./Drivers/FreeModbus/mb.d \
./Drivers/FreeModbus/mb_m.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FreeModbus/mb.o: ../Drivers/FreeModbus/mb.c Drivers/FreeModbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/FreeModbus/mb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/FreeModbus/mb_m.o: ../Drivers/FreeModbus/mb_m.c Drivers/FreeModbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/FreeModbus/mb_m.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

