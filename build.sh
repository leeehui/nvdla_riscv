#!/bin/sh

rm -rf build
mkdir -p build
cd build
#cmake -D PLAT=riscv_runtime ../src
cmake -D PLAT=ipdv_sim ../src
make
#riscv64-unknown-elf-objdump -d nvdla.elf > ./nvdla.dump
#riscv64-unknown-elf-objcopy -O binary -R .note -R .comment -S nvdla.elf nvdla.bin
#
#mkdir output
#python ../convert.py -i nvdla.bin
#python ../convert-ipdv.py -i nvdla.bin
#
#cd output
#dir=$(date +'%Y%m%d-%H%M%S')
#dir_ipdv="${dir}_ipdv"
#mkdir $dir
#mkdir $dir_ipdv
#
#cp gpsram_blk_*.hex $dir
#cp nvdla.bin.dat  "${dir_ipdv}/nvdla.${1}.dat"
#cp ../nvdla.dump "${dir_ipdv}/nvdla.${1}.dump"
#cp ../nvdla.elf  "${dir_ipdv}/nvdla.${1}.elf"
#cp ../nvdla.map  "${dir_ipdv}/nvdla.${1}.map"
#cp $dir /mnt/share -r
#cp $dir_ipdv /mnt/share -r
