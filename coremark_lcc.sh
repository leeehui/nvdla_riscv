#!/bin/sh

rm -rf src/cMakeFiles
rm src/CMakeCache.txt
rm src/cmake_install.cmake

rm -rf build
mkdir -p build
cd build
cmake -D PLAT=lcc ../src
make
riscv64-unknown-elf-objdump -d lcc.elf > ./lcc.dump
riscv64-unknown-elf-objcopy -O binary -R .note -R .comment -S lcc.elf lcc.bin
#python3 ../script/bin2vhx.py -f hex -o lcc.vlog.hex -b 0xa0200000 -w 4 lcc.bin
#python3 ../script/bin2vhx.py -f hex -o lcc.vlog.hex -w 4 lcc.bin
#python3 ../script/stamp.py

