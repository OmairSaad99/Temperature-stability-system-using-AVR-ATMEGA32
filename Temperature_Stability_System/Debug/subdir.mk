################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_Prog.c \
../CLCD_program.c \
../DC_Motor_Prog.c \
../DIO_prog.c \
../EXTI_Prog.c \
../Global_prog.c \
../KPD_prog.c \
../PWM_prog.c \
../TWI_Prog.c \
../Temp_APP_Prog.c \
../main.c 

OBJS += \
./ADC_Prog.o \
./CLCD_program.o \
./DC_Motor_Prog.o \
./DIO_prog.o \
./EXTI_Prog.o \
./Global_prog.o \
./KPD_prog.o \
./PWM_prog.o \
./TWI_Prog.o \
./Temp_APP_Prog.o \
./main.o 

C_DEPS += \
./ADC_Prog.d \
./CLCD_program.d \
./DC_Motor_Prog.d \
./DIO_prog.d \
./EXTI_Prog.d \
./Global_prog.d \
./KPD_prog.d \
./PWM_prog.d \
./TWI_Prog.d \
./Temp_APP_Prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


