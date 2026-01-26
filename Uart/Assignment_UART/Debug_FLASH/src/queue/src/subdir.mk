################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/queue/src/queue.c 

OBJS += \
./src/queue/src/queue.o 

C_DEPS += \
./src/queue/src/queue.d 


# Each subdirectory must supply rules for building sources it contributes
src/queue/src/%.o: ../src/queue/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/queue/src/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


