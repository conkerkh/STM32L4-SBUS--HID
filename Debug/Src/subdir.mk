################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/gpio.c \
../Src/main.c \
../Src/ringbufferdma.c \
../Src/sbus.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c \
../Src/usart.c \
../Src/usb_device.c \
../Src/usbd_conf.c \
../Src/usbd_custom_hid_if.c \
../Src/usbd_desc.c 

OBJS += \
./Src/dma.o \
./Src/gpio.o \
./Src/main.o \
./Src/ringbufferdma.o \
./Src/sbus.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o \
./Src/usart.o \
./Src/usb_device.o \
./Src/usbd_conf.o \
./Src/usbd_custom_hid_if.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/dma.d \
./Src/gpio.d \
./Src/main.d \
./Src/ringbufferdma.d \
./Src/sbus.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d \
./Src/usart.d \
./Src/usb_device.d \
./Src/usbd_conf.d \
./Src/usbd_custom_hid_if.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L432xx -I"/Users/khockuba/STM32/sbusToHid/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/khockuba/STM32/sbusToHid/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/khockuba/STM32/sbusToHid/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/Users/khockuba/STM32/sbusToHid/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/khockuba/STM32/sbusToHid/Drivers/CMSIS/Include"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


