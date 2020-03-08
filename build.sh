#!/bin/sh
export base=$PWD
cd frequencier
make clean
make
./frequencier 
./frequencier big
cd $base

