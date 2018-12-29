#!/bin/sh

rm -rf build
mkdir -p build
cd build
cmake -D PLAT=$1 -D BIN_NAME=$2 ../src
make

if [ $# -eq 3 ]; then

    if [ $3 =  "bin" ]; then
        riscv64-unknown-elf-objdump -d nvdla.elf > ./nvdla.dump
        riscv64-unknown-elf-objcopy -O binary -R .note -R .comment -S nvdla.elf nvdla.bin

        mkdir output
        python ../convert.py -i nvdla.bin
        python ../convert-ipdv.py -i nvdla.bin

        cd output
        dir=$(date +'%Y%m%d-%H%M%S')
        dir="${dir}.${1}_${2}"
        mkdir $dir

        cp gpsram_blk_*.hex $dir
        cp nvdla.bin.dat  "${dir}/${dir}.dat"
        cp ../nvdla.dump "${dir}/${dir}.dump"
        cp ../nvdla.elf  "${dir}/${dir}.elf"
        cp $dir /mnt/share -r
    else
        echo "invalid parameter 3"
    fi
fi
