################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/parse_srec/src/parse-srec.c 

OBJS += \
./src/parse_srec/src/parse-srec.o 

C_DEPS += \
./src/parse_srec/src/parse-srec.d 


# Each subdirectory must supply rules for building sources it contributes
src/parse_srec/src/%.o: ../src/parse_srec/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/parse_srec/src/parse-srec.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


