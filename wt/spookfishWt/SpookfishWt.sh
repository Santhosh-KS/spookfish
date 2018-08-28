#!/bin/sh

cd ./build
cmake ..
make clean
make
cd ..
./build/SpookfishWt --docroot . --http-address 0.0.0.0 --http-port 8080
