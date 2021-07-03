#!/bin/sh

#jank city
bin=$(readlink -f ../../main_test.bin)
echo $bin
mv ./load_bin.py $1
python $1/load_bin.py $bin
mv $1/load_bin.py ./
