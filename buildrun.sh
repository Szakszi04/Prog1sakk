#!/bin/bash

clear && \
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -B build -Wno-dev && \
cmake --build build && \
build/chess
