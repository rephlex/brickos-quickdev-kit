#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make main.lx && dll main.lx

