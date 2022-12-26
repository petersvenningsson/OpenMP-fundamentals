#! /bin/bash

rm -r build
mkdir build
cd build
cmake ..
make

for bin in hello
do
    echo "Single-threaded runtime ..."
    OMP_NUM_THREADS=1 hyperfine "./$bin" 2> /dev/null

    echo "Multi-threaded runtime ..."
    hyperfine "./$bin" 2> /dev/null
done
