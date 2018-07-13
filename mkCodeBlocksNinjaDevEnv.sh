#!/bin/bash

# make the DEV_ENV directory
# cd into DEV_ENV
# call CMake starting with the directory that this file sits in, with target output of CodeBlocks with Unix Makefiles

mkdir DEV_ENV
cd DEV_ENV
cmake .. -G "CodeBlocks - Ninja"


