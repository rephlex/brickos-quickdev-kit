#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make tool_test180degturn.lx && dll tool_test180degturn.lx

