################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_program.c \
../SPI.c \
../main.c 

OBJS += \
./LCD_program.o \
./SPI.o \
./main.o 

C_DEPS += \
./LCD_program.d \
./SPI.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\Infrastructure" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\MCAL\DIO_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\MCAL\Sleep_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\MCAL\TIMER_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\MCAL\UART_driver" -I"C:\Users\mosta\Desktop\IMT-C\PC_UART_interfaceMaster\Registers" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


