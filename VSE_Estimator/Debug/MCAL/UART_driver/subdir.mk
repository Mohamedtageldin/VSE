################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/UART_driver/UART.c 

OBJS += \
./MCAL/UART_driver/UART.o 

C_DEPS += \
./MCAL/UART_driver/UART.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/UART_driver/%.o: ../MCAL/UART_driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\Infrastructure" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\DIO_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\Sleep_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\TIMER_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\UART_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\Registers" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


