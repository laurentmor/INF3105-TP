#!/bin/sh
export base=$PWD
cd frequencier
make clean
make 
cd $base

