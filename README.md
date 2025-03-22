# Embedded Programming with STM32 Microprocessors

This repo was created around the use of the [STM32F103C8T6](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html) Blue Pill board.

## Getting Started

_Gathered from reference setup [here](https://stm32-base.org/guides/setup)_

Ensure that the following tools are installed:
- git
- make
- [STLink Tools](https://github.com/stlink-org/stlink#installation)


Run `setup.sh`

**NOTE**: The below `setup.sh` script assumes you are working with an **STM32F103C8T6** board with a **Linux** machine. If you are working with something else, update the configuration section of the setup script.**

```bash
bash setup.sh
```

## GNU Arm Toolchain Useful Commands

### `arm-none-eabi-gcc` 

Compiles, assembles and links input code

#### Flags

- `-c` compile and assemble, but don't link
- `-o file` link to output file, named file
- `-g` generate debugging info in executable
- `Wall` enable all warning messages
- `Werror` treat warnings as errors
- `I [DIR]` include a directory for header files
- `ansi` use the American National Standards Institute (ANSI) standard
- `std` specify a standard version (eg. C11)
- `-v` verbose output from GCC

#### Architecture specific flags

- `mcpu=[Name]` specify target ARM processor (ex. `-mcpu=cortex-m4`)
- `-march=[Name]` specify target ARM architecture (ex. `-march-armv7-m`)
- `-mtune=[Name]` optimize for specific ARM processor (ex. `-mtune=cortex-m4`)
- `-mthumb` generate code for the Thumb instruction set
- `-marm` generate code for the ARM instruction set
- `-mlittle-endian` generate code for little-endian mode
- `-mbig-endian` generate code for big-endian mode

Example `arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -mlittle-endian main.c -o main.o`

### `arm-none-eabi-nm`

Lists symbols from object files

### `arm-none-eabi-size`

Lists section sizes of object/executable files

### `arm-none-eabi-objdump`

Dumps information about object files

### `arm-none-eabi-readelf`

Displays information about ELF files

### `arm-none-eabi-objcopy`

Converts/copies object files between formats