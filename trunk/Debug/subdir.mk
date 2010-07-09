################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CCardRegion.cpp \
../CCardStack.cpp \
../CGame.cpp \
../CardGraphics.cpp \
../font.cpp \
../main.cpp 

OBJS += \
./CCardRegion.o \
./CCardStack.o \
./CGame.o \
./CardGraphics.o \
./font.o \
./main.o 

CPP_DEPS += \
./CCardRegion.d \
./CCardStack.d \
./CGame.d \
./CardGraphics.d \
./font.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I.././includes -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


