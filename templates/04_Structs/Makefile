CC=../../tools/bin/arm-none-eabi-gcc
BIN=../../tools/bin/arm-none-eabi-objcopy
CFLAGS=-c -mcpu=cortex-m3 -mthumb -std=gnu11
LDFLAGS=-nostdlib -T stm32_ls.ld -Wl,-Map=blink.map
STL=st-flash

all : sos.bin

main.o : main.c 
	$(CC) $(CFLAGS) $^ -o $@ 

stm32f103_startup.o : stm32f103_startup.c 
	$(CC) $(CFLAGS) $^ -o $@ 

sos.elf : main.o stm32f103_startup.o
	$(CC) $(LDFLAGS) $^ -o $@ 

sos.bin : sos.elf 
	$(BIN) -O binary $^ $@


# load :
# 	openocd -f board/stm32f103c8_blue_pill.cfg

clean:
	rm -f *.o *.elf *.map

erase:
	$(STL) erase

flash:
	$(STL) write sos.bin 0x8000000 
