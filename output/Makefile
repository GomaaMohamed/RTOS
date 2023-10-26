#Home of the Work Space
#Edit the path of the project here
HOME := /home/gomaa/embedded/08-ARMCortex-M/rtos
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as 
LD = arm-none-eabi-ld 
BIN = arm-none-eabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3


#Directories that will be searched for Headers
INCLUDES +=  -I $(HOME)/mcal/include \
             -I $(HOME)/hal/include \
			 -I $(HOME)/app/include \
			 -I $(HOME)/lib/include \
			 -I $(HOME)/service/include
 
#Source Files of the Project
SRCS += $(wildcard $(HOME)/*.c) \
        $(wildcard $(HOME)/mcal/sources/*.c) \
		$(wildcard $(HOME)/hal/sources/*.c) \
		$(wildcard $(HOME)/app/sources/*.c) \
		$(wildcard $(HOME)/lib/sources/*.c) \
		$(wildcard $(HOME)/service/sources/*.c) \
		$(wildcard $(HOME)/service/sources/*.s) 
       
compile :  
	@$(CC) $(CFLAGS) -c $(SRCS) -g $(INCLUDES)

clean :
	@rm -f *.o *.s *.i  *.asm 
	
	
