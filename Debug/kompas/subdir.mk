################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kompas/lis3mdltr.c 

OBJS += \
./kompas/lis3mdltr.o 

C_DEPS += \
./kompas/lis3mdltr.d 


# Each subdirectory must supply rules for building sources it contributes
kompas/lis3mdltr.o: ../kompas/lis3mdltr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303x8 -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../press -I"C:/STM_TEST/7SEG_DOSKA_FINAL/tlak_final" -I"C:/STM_TEST/7SEG_DOSKA_FINAL/kompas" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"kompas/lis3mdltr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

