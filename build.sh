#!/bin/sh
export base=$PWD
cd frequencier
make clean
make
./frequencier 
cd $base

