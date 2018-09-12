#!/bin/sh

rm -rf build
mkdir -p build
cd build
cmake -D PLAT=nvdla ../src
make
riscv64-unknown-elf-objdump -d nvdla.elf > ./nvdla.dump
riscv64-unknown-elf-objcopy -O binary -R .note -R .comment -S nvdla.elf nvdla.bin

