#!/bin/bash

clear && \
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -B build -Wno-dev && \
cmake --build build && \
build/nagyhazi
