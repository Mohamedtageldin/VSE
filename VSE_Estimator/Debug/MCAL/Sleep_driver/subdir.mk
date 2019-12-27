################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Sleep_driver/SleepModes.c 

OBJS += \
./MCAL/Sleep_driver/SleepModes.o 

C_DEPS += \
./MCAL/Sleep_driver/SleepModes.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Sleep_driver/%.o: ../MCAL/Sleep_driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\Infrastructure" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\DIO_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\Sleep_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\TIMER_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\MCAL\UART_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interface\Registers" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


