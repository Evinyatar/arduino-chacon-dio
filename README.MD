arduino-chacon
==============

Control Chacon DIO devices using an Arduino and a RF433 OOK module.

Usage:
send < sender >,< interruptor >,< state > to the serial port.

See send.sh for an example of how to use from linux.

Pairing
-------

The receiver needs to be paired to the sender id you've chosen. To do that, plug it in and send an ON command (state = 1) immediately after (while the led is blinking). The device will switch on an off to confirm.

