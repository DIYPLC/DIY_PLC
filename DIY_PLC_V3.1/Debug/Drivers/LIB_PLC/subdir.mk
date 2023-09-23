################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LIB_PLC/Fb2PosControl.c \
../Drivers/LIB_PLC/Fb3PosControl.c \
../Drivers/LIB_PLC/FbBitsToWord.c \
../Drivers/LIB_PLC/FbBlink.c \
../Drivers/LIB_PLC/FbCounter.c \
../Drivers/LIB_PLC/FbDeadBand.c \
../Drivers/LIB_PLC/FbDelayN.c \
../Drivers/LIB_PLC/FbDeriveF.c \
../Drivers/LIB_PLC/FbEdgeNeg.c \
../Drivers/LIB_PLC/FbEdgePos.c \
../Drivers/LIB_PLC/FbFilterA.c \
../Drivers/LIB_PLC/FbFilterNaN.c \
../Drivers/LIB_PLC/FbGSS.c \
../Drivers/LIB_PLC/FbIntegrator.c \
../Drivers/LIB_PLC/FbLimit.c \
../Drivers/LIB_PLC/FbModeSelector.c \
../Drivers/LIB_PLC/FbPIDcontrol.c \
../Drivers/LIB_PLC/FbRamp.c \
../Drivers/LIB_PLC/FbScale.c \
../Drivers/LIB_PLC/FbSoftPWM.c \
../Drivers/LIB_PLC/FbTimerTof.c \
../Drivers/LIB_PLC/FbTimerTon.c \
../Drivers/LIB_PLC/FbTriggerRS.c \
../Drivers/LIB_PLC/FbTs.c \
../Drivers/LIB_PLC/FbWordToBits.c 

OBJS += \
./Drivers/LIB_PLC/Fb2PosControl.o \
./Drivers/LIB_PLC/Fb3PosControl.o \
./Drivers/LIB_PLC/FbBitsToWord.o \
./Drivers/LIB_PLC/FbBlink.o \
./Drivers/LIB_PLC/FbCounter.o \
./Drivers/LIB_PLC/FbDeadBand.o \
./Drivers/LIB_PLC/FbDelayN.o \
./Drivers/LIB_PLC/FbDeriveF.o \
./Drivers/LIB_PLC/FbEdgeNeg.o \
./Drivers/LIB_PLC/FbEdgePos.o \
./Drivers/LIB_PLC/FbFilterA.o \
./Drivers/LIB_PLC/FbFilterNaN.o \
./Drivers/LIB_PLC/FbGSS.o \
./Drivers/LIB_PLC/FbIntegrator.o \
./Drivers/LIB_PLC/FbLimit.o \
./Drivers/LIB_PLC/FbModeSelector.o \
./Drivers/LIB_PLC/FbPIDcontrol.o \
./Drivers/LIB_PLC/FbRamp.o \
./Drivers/LIB_PLC/FbScale.o \
./Drivers/LIB_PLC/FbSoftPWM.o \
./Drivers/LIB_PLC/FbTimerTof.o \
./Drivers/LIB_PLC/FbTimerTon.o \
./Drivers/LIB_PLC/FbTriggerRS.o \
./Drivers/LIB_PLC/FbTs.o \
./Drivers/LIB_PLC/FbWordToBits.o 

C_DEPS += \
./Drivers/LIB_PLC/Fb2PosControl.d \
./Drivers/LIB_PLC/Fb3PosControl.d \
./Drivers/LIB_PLC/FbBitsToWord.d \
./Drivers/LIB_PLC/FbBlink.d \
./Drivers/LIB_PLC/FbCounter.d \
./Drivers/LIB_PLC/FbDeadBand.d \
./Drivers/LIB_PLC/FbDelayN.d \
./Drivers/LIB_PLC/FbDeriveF.d \
./Drivers/LIB_PLC/FbEdgeNeg.d \
./Drivers/LIB_PLC/FbEdgePos.d \
./Drivers/LIB_PLC/FbFilterA.d \
./Drivers/LIB_PLC/FbFilterNaN.d \
./Drivers/LIB_PLC/FbGSS.d \
./Drivers/LIB_PLC/FbIntegrator.d \
./Drivers/LIB_PLC/FbLimit.d \
./Drivers/LIB_PLC/FbModeSelector.d \
./Drivers/LIB_PLC/FbPIDcontrol.d \
./Drivers/LIB_PLC/FbRamp.d \
./Drivers/LIB_PLC/FbScale.d \
./Drivers/LIB_PLC/FbSoftPWM.d \
./Drivers/LIB_PLC/FbTimerTof.d \
./Drivers/LIB_PLC/FbTimerTon.d \
./Drivers/LIB_PLC/FbTriggerRS.d \
./Drivers/LIB_PLC/FbTs.d \
./Drivers/LIB_PLC/FbWordToBits.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LIB_PLC/Fb2PosControl.o: ../Drivers/LIB_PLC/Fb2PosControl.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/Fb2PosControl.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/Fb3PosControl.o: ../Drivers/LIB_PLC/Fb3PosControl.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/Fb3PosControl.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbBitsToWord.o: ../Drivers/LIB_PLC/FbBitsToWord.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbBitsToWord.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbBlink.o: ../Drivers/LIB_PLC/FbBlink.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbBlink.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbCounter.o: ../Drivers/LIB_PLC/FbCounter.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbCounter.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbDeadBand.o: ../Drivers/LIB_PLC/FbDeadBand.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbDeadBand.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbDelayN.o: ../Drivers/LIB_PLC/FbDelayN.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbDelayN.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbDeriveF.o: ../Drivers/LIB_PLC/FbDeriveF.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbDeriveF.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbEdgeNeg.o: ../Drivers/LIB_PLC/FbEdgeNeg.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbEdgeNeg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbEdgePos.o: ../Drivers/LIB_PLC/FbEdgePos.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbEdgePos.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbFilterA.o: ../Drivers/LIB_PLC/FbFilterA.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbFilterA.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbFilterNaN.o: ../Drivers/LIB_PLC/FbFilterNaN.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbFilterNaN.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbGSS.o: ../Drivers/LIB_PLC/FbGSS.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbGSS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbIntegrator.o: ../Drivers/LIB_PLC/FbIntegrator.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbIntegrator.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbLimit.o: ../Drivers/LIB_PLC/FbLimit.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbLimit.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbModeSelector.o: ../Drivers/LIB_PLC/FbModeSelector.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbModeSelector.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbPIDcontrol.o: ../Drivers/LIB_PLC/FbPIDcontrol.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbPIDcontrol.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbRamp.o: ../Drivers/LIB_PLC/FbRamp.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbRamp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbScale.o: ../Drivers/LIB_PLC/FbScale.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbScale.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbSoftPWM.o: ../Drivers/LIB_PLC/FbSoftPWM.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbSoftPWM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbTimerTof.o: ../Drivers/LIB_PLC/FbTimerTof.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbTimerTof.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbTimerTon.o: ../Drivers/LIB_PLC/FbTimerTon.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbTimerTon.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbTriggerRS.o: ../Drivers/LIB_PLC/FbTriggerRS.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbTriggerRS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbTs.o: ../Drivers/LIB_PLC/FbTs.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbTs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/LIB_PLC/FbWordToBits.o: ../Drivers/LIB_PLC/FbWordToBits.c Drivers/LIB_PLC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/tcp" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/rtu" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/port" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/include" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/functions" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/ascii" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/FreeModbus/app" -I"C:/Users/xyz/STM32CubeIDE/workspace_1.6.1/DIY_PLC_V3.1/Drivers/LIB_PLC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/LIB_PLC/FbWordToBits.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

