#!/bin/sh

rm -rf build
mkdir -p build
cd build
cmake -D PLAT=nvdla ../src
make
riscv64-unknown-elf-objdump -d nvdla.elf > ./nvdla.dump
riscv64-unknown-elf-objcopy -O binary -R .note -R .comment -S nvdla.elf nvdla.bin
cd ..
rm -rf output
mkdir output
python convert.py -i build/nvdla.bin

