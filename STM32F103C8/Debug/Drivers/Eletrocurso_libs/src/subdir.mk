################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Eletrocurso_libs/src/delay.c 

OBJS += \
./Drivers/Eletrocurso_libs/src/delay.o 

C_DEPS += \
./Drivers/Eletrocurso_libs/src/delay.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Eletrocurso_libs/src/delay.o: ../Drivers/Eletrocurso_libs/src/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I"C:/Users/guilh/OneDrive/Documents/Projetos/Microcontroladores/Eletrocursos/ProjetoSTM32F103C8/Drivers/Eletrocurso_libs/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Eletrocurso_libs/src/delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

