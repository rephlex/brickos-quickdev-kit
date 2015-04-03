#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make battlebot-2.lx && dll battlebot-2.lx

