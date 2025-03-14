#!/bin/bash


##################################################################
#                       CONFIGURATION                            #
##################################################################

# Download GNU Arm Embdedded Toolchains from https://developer.arm.com/downloads/-/gnu-rm
# Update url and toolchain name below with latest version
GNU_ARM_TOOLCHAIN_DOWNLOAD='https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=D484B37FF37D6FC3597EBE2877FB666A41D5253B'
GNU_ARM_TOOLCHAIN=gcc-arm-none-eabi-10.3-2021.10

# Template repo to clone into templates
STM32_TEMPLATE_REPO_NAME='STM32-base-F1-template'

##################################################################
##################################################################

TOOLS=tools
GNU_ARM_TOOLCHAIN_TARBALL="gnu_arm_toolchain.tar.bz2"

# Download GNU Arm Toolchain
if [ ! -f "$GNU_ARM_TOOLCHAIN_TARBALL" ]; then
    echo "Downloading GNU Arm Toolchain from: $GNU_ARM_TOOLCHAIN_DOWNLOAD"
    curl -L "$GNU_ARM_TOOLCHAIN_DOWNLOAD" > "$GNU_ARM_TOOLCHAIN_TARBALL"
fi
if [ ! -d "tools/arm-none-eabi" ]; then
    echo "Unpacking tarball"
    tar xjf "$GNU_ARM_TOOLCHAIN_TARBALL"
    echo "Setting up tools"
    mkdir -p "$TOOLS"
    mv "$GNU_ARM_TOOLCHAIN"/* "$TOOLS"
    rm -r "$GNU_ARM_TOOLCHAIN" "$GNU_ARM_TOOLCHAIN_TARBALL"
fi

# Clone STM32-base and STM32-base-STM32Cube repositories
if [ ! -d "STM32-base" ]; then
    echo "Cloning STM32-base"
    git clone git@github.com:STM32-base/STM32-base.git
fi
if [ ! -d "STM32-base-STM32Cube" ]; then
    echo "Cloning STM32-base-STM32Cube"
    git clone git@github.com:STM32-base/STM32-base-STM32Cube.git
fi

# Clone template
if [ ! -d "templates/STM32-base-F1-template" ]; then
    echo "Cloning $STM32_TEMPLATE_REPO_NAME"
    mkdir -p templates
    (cd templates && git clone git@github.com:STM32-base/$STM32_TEMPLATE_REPO_NAME.git)
fi

# Link template to STM32-base and STM32-base-STM32Cube
if [ ! -f "templates/$STM32_TEMPLATE_REPO_NAME/STM32-base" ]; then 
    (
        cd "templates/$STM32_TEMPLATE_REPO_NAME"
        ln -s ../../STM32-base
    )
fi
if [ ! -f "templates/$STM32_TEMPLATE_REPO_NAME/STM32-base-STM32Cube" ]; then 
    (
        cd "templates/$STM32_TEMPLATE_REPO_NAME"
        ln -s ../../STM32-base-STM32Cube
    )
fi