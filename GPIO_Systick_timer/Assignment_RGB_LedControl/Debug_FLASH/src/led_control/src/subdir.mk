################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/led_control/src/led_control.c 

OBJS += \
./src/led_control/src/led_control.o 

C_DEPS += \
./src/led_control/src/led_control.d 


# Each subdirectory must supply rules for building sources it contributes
src/led_control/src/%.o: ../src/led_control/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/led_control/src/led_control.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


