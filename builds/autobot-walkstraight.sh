#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make autobot-walkstraight.lx && dll autobot-walkstraight.lx

