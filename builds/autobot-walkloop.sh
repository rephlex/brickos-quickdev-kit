#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make autobot-walkloop.lx && dll autobot-walkloop.lx

