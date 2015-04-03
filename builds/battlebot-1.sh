#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make battlebot-1.lx && dll battlebot-1.lx

