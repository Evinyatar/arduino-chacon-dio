#!/bin/bash
device=/dev/ttyUSB0
stty -F $device 9600 cs8 cread clocal
exec 3<> $device
sleep 2
echo "$1" >&3
cat <&3
exec 3>&-

