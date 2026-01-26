################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board/clock_config.c \
../src/board/pin_config.c \
../src/board/systick_config.c 

OBJS += \
./src/board/clock_config.o \
./src/board/pin_config.o \
./src/board/systick_config.o 

C_DEPS += \
./src/board/clock_config.d \
./src/board/pin_config.d \
./src/board/systick_config.d 


# Each subdirectory must supply rules for building sources it contributes
src/board/%.o: ../src/board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/board/clock_config.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


