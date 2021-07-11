#!/usr/bin/env zsh
set -e

PWD="$(pwd)"
DIR="$(dirname $(readlink $0))"
echo ${DIR}
#git submodule init
#git submodule update --recursive
cd ${DIR}/ipwndfu
rm -rf load_bin.py
cp ../load_bin.py load_bin.py
BIN=$(readlink -f ../../../main_test.bin.final)
echo ${BIN}
python2.7 ipwndfu -p
python2.7 load_bin.py ${BIN}
cd ${PWD}
