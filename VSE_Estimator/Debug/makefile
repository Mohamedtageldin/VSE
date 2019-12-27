################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART_driver/subdir.mk
-include MCAL/TIMER_driver/subdir.mk
-include MCAL/Sleep_driver/subdir.mk
-include MCAL/DIO_driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
PC_UART_interface.lss \

FLASH_IMAGE += \
PC_UART_interface.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: PC_UART_interface.elf secondary-outputs

# Tool invocations
PC_UART_interface.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PC_UART_interface.map -mmcu=atmega32 -o "PC_UART_interface.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PC_UART_interface.lss: PC_UART_interface.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PC_UART_interface.elf  >"PC_UART_interface.lss"
	@echo 'Finished building: $@'
	@echo ' '

PC_UART_interface.hex: PC_UART_interface.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex PC_UART_interface.elf  "PC_UART_interface.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PC_UART_interface.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PC_UART_interface.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PC_UART_interface.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
