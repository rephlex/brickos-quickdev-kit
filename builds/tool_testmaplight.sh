#!/bin/bash
rm *.lx
rm *.o
export RCXTTY=/dev/usb/legousbtower0
make tool_testmaplight.lx && dll tool_testmaplight.lx

