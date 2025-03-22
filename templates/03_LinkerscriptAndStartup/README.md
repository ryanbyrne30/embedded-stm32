# 1. Compile

Compile main.c
```
arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -std=gnu11 main.c -o main.o
```

Compile startup code
```
arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -std=gnu11 stm32f103_startup.c -o stm32f103_startup.o
```

# 2. Link
```
arm-non-eabi-gcc -nostdlib -T stm32_ls.ld *.o -o 3_LinkerAndStartup.elf
```

# 3. Flash

In one terminal
```
openocd -f board/stm32f103c8_blue_pill.cfg
```

In another terminal
```
arm-none-eabi-gdb
target remote localhost:3333
monitor reset init
monitor flash write_image erase 3_LinkerAndStartup.elf
monitor reset init
monitor resume
```