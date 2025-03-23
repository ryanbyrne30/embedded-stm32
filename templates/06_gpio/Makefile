CC=../../tools/bin/arm-none-eabi-gcc
BIN=../../tools/bin/arm-none-eabi-objcopy
CFLAGS=-c -mcpu=cortex-m3 -mthumb -std=gnu11
LDFLAGS=-nostdlib -T stm32_ls.ld -Wl,-Map=blink.map
STL=st-flash
INC=-I./chip_headers/CMSIS/Include -I./chip_headers/CMSIS/Device/ST/STM32F1xx/Include

all : sos.bin

gpio.o : gpio.c 
	$(CC) $(INC) $(CFLAGS) $^ -o $@

main.o : main.c 
	$(CC) $(INC) $(CFLAGS) $^ -o $@ 

stm32f103_startup.o : stm32f103_startup.c 
	$(CC) $(CFLAGS) $^ -o $@ 

sos.elf : main.o gpio.o stm32f103_startup.o
	$(CC) $(LDFLAGS) $^ -o $@ 

sos.bin : sos.elf 
	$(BIN) -O binary $^ $@


# load :
# 	openocd -f board/stm32f103c8_blue_pill.cfg

clean:
	rm -f *.o *.elf *.map *.bin

erase:
	$(STL) erase

flash:
	$(STL) write sos.bin 0x8000000 
