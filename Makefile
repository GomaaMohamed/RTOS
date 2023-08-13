#Home of the Work Space
#Edit the path of the project here
HOME := /home/gomaa/embedded/08-ARMCortex-M/RTOS
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
       
#Object Files      
OBJECTS += $(wildcard $(HOME)/output/*.o)
        


########### Rules ############
all : app.hex 
	@echo "===================================="
	@echo "===================================="
	@echo "........ Successfully Built ........"
	@date -R
	@echo "===================================="
	@echo "===================================="
#(CC) $(CFLAGS) -c $(SRCS) -g $(INCLUDES)
compile :  
	@make -s -C $(HOME)/output $@           

app.elf : linker.ld compile
	@$(LD) --print-map-discarded --print-map -T linker.ld -o app.elf $(OBJECTS)  > mapfile

app.hex : app.elf	
	@$(BIN) -O ihex app.elf app.hex

clean :
	@rm -f executable *.o *.s *.i *.exe *.hex *.elf *.bin *.asm mapfile
	@make -s -C $(HOME)/output $@ 
	@echo "===================================="
	@echo "===================================="
	@echo ".............. Done ................"
	@date -R
	@echo "===================================="
	@echo "===================================="

flash : app.hex
	@$(STL)  --format ihex write app.hex
	@echo "===================================="
	@echo "===================================="
	@echo "The Program was successfully flashed"
	@date -R
	@echo "===================================="
	@echo "===================================="
	
erase :
	@$(STL) erase
	@echo "===================================="
	@echo "===================================="
	@echo "..The Rom was Successfully erased.."
	@date -R
	@echo "===================================="
	@echo "===================================="
