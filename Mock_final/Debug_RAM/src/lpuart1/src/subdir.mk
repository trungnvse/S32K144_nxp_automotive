################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lpuart1/src/lpuart1.c 

OBJS += \
./src/lpuart1/src/lpuart1.o 

C_DEPS += \
./src/lpuart1/src/lpuart1.d 


# Each subdirectory must supply rules for building sources it contributes
src/lpuart1/src/%.o: ../src/lpuart1/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/lpuart1/src/lpuart1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


