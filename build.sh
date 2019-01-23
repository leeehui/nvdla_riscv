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
        output_name="${1}_${2}"
        mkdir $dir

        cp gpsram_blk_*.hex $dir
        cp nvdla.bin.dat  "${dir}/${output_name}.dat"
        cp ../nvdla.dump "${dir}/${output_name}.dump"
        cp ../nvdla.elf  "${dir}/${output_name}.elf"
        cp ../nvdla.bin  "${dir}/${output_name}.bin"
        cp $dir /mnt/share -r
        #scp ${dir}/${output_name}.bin root@10.64.4.20:/media/card/devmem/
    else
        echo "invalid parameter 3"
    fi
fi
