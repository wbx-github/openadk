#!/bin/bash

OUTPUT_DIR=$1

if ! test -d "${OUTPUT_DIR}" ; then
    echo "ERROR: no output directory specified."
    echo "Usage: $0 OUTPUT_DIR"
    echo ""
    echo "Arguments:"
    echo "    OUTPUT_DIR    The OpenADK output directory."
    exit 1
fi

./host_x86_64-linux-gnu/usr/bin/openocd \
	-f interface/stlink.cfg -f board/stm32f7discovery.cfg \
-c "init" \
-c "reset init" \
-c "flash probe 0" \
-c "flash info 0" \
-c "flash write_image erase ${OUTPUT_DIR}/u-boot-dtb.bin 0x08000000" \
-c "reset run" \
-c "shutdown"
