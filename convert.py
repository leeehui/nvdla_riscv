#! /usr/bin/python

import os
import argparse
import struct

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', action = 'store', help='input binary file')
    parser.add_argument('-o', action = 'store', default = 'output', help='output directory')

    args = parser.parse_args()
    input_file = args.i
    output_dir = args.o


    byte_array_1 = bytearray();
    byte_array_2 = bytearray();

    counter = 0
    flag = False
    file_name = output_dir + "/gpsram_blk_"
    file_counter = 0
    file_len = 2048 * 8

    # read file to bytearray
    with open(input_file, "rb") as f:
        data = f.read()
        f.close()

    print(len(data))
    # split bytearray according to requirement
    while counter != len(data):
        if (flag == False):
            if (len(byte_array_1) < file_len):
                byte_array_1.append(data[counter])
            else:
                new_file_name = file_name + str(file_counter)
                print("writing file...", new_file_name)
                new_file = open(new_file_name, "wb")
                new_file.write(byte_array_1)
                new_file.close()
                byte_array_1.clear()
                byte_array_1.append(data[counter])
                file_counter = file_counter + 1
        else:
            if (len(byte_array_2) < file_len):
                byte_array_2.append(data[counter])
            else:
                new_file_name = file_name + str(file_counter)
                print("writing file...", new_file_name )
                new_file = open(new_file_name, "wb")
                new_file.write(byte_array_2)
                new_file.close()
                byte_array_2.clear()
                byte_array_2.append(data[counter])
                file_counter = file_counter + 1

        counter = counter + 1
        if (counter%8 == 0):
            flag = not(flag)

    # write left two partial data to file
    if (len(byte_array_1) != 0):
        new_file_name = file_name + str(file_counter)
        print("writing file...", new_file_name )
        new_file = open(new_file_name, "wb")
        new_file.write(byte_array_1)
        new_file.close()
        file_counter = file_counter + 1
    if (len(byte_array_2) != 0):
        new_file_name = file_name + str(file_counter)
        print("writing file...", new_file_name )
        new_file = open(new_file_name, "wb")
        new_file.write(byte_array_2)
        new_file.close()
        file_counter = file_counter + 1

    # convert binary to hex string
    while file_counter != 0:

        # read generated file according to file_counter
        file_counter = file_counter - 1
        new_file_name = file_name + str(file_counter)
        with open(new_file_name, "rb") as f:
            block_data = f.read()
            f.close()

        byte_counter = 0
        new_file = open(new_file_name + ".hex","w")
        while byte_counter < len(block_data):
            # 8bytes per line
            data = block_data[byte_counter: byte_counter+8]
            byte_counter = byte_counter + 8
            new_data = int.from_bytes(data, byteorder="little")
            # 16 characters per line
            string = "{0:0{1}X}".format(new_data, 16)
            new_file.writelines(string + '\n')

        new_file.close()

if __name__ == '__main__':
    main()
