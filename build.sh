#!/bin/sh
echo "Build script pour exercises du livre CPP"
cd exercises_livre_cpp
echo "Build exercises"
make clean
make
cd ../TP2
echo "Build TP2 "
make clean
make


