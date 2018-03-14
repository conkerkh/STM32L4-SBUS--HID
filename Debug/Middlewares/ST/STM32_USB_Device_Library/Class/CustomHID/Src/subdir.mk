################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L432xx -I"/Users/khockuba/STM32/sbusToHid/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/khockuba/STM32/sbusToHid/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/khockuba/STM32/sbusToHid/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/khockuba/STM32/sbusToHid/Drivers/CMSIS/Include"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


