################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/boot/src/boot.c 

OBJS += \
./src/boot/src/boot.o 

C_DEPS += \
./src/boot/src/boot.d 


# Each subdirectory must supply rules for building sources it contributes
src/boot/src/%.o: ../src/boot/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/boot/src/boot.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


