################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/flash/src/flash.c 

OBJS += \
./src/flash/src/flash.o 

C_DEPS += \
./src/flash/src/flash.d 


# Each subdirectory must supply rules for building sources it contributes
src/flash/src/%.o: ../src/flash/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/flash/src/flash.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


