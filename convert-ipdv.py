#! /usr/bin/python

import os
import argparse
import struct

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', action = 'store', help='input binary file')
    parser.add_argument('-o', action = 'store', default = 'output/', help='output directory')

    args = parser.parse_args()
    input_file = args.i
    output_dir = args.o


    counter = 0

    # read file to bytearray
    with open(input_file, "rb") as f:
        data = f.read()
        f.close()

    print(len(data))
    new_file = open(output_dir + input_file + ".dat","w")
    new_file.writelines('{\n')
    # split bytearray according to requirement
    while counter != len(data):

        line_string = "{{offset:{0:#x}, size:{1:d}, payload:0x{2:02x} 0x{3:02x} 0x{4:02x} 0x{5:02x}}} ,\n"
        line_string = line_string.format(counter, 4, data[counter], data[counter+1], data[counter+2], data[counter+3])

        counter = counter + 4
        new_file.writelines(line_string)

    new_file.writelines('}\n')
    new_file.close()


if __name__ == '__main__':
    main()
