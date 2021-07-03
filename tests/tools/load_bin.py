#!/usr/bin/python2.7

import usbexec
import dfu
import sys
import time
import utilities
import struct

device = dfu.acquire_device()
if not device:
    quit("Couldn't get device handle")
dfu.release_device(device)
dev = usbexec.PwnedUSBDevice()

with open(sys.argv[1], "rb") as f:
    dev.write_memory(0x180018620, f.read())
    dump = dev.read_memory(0x180018620, 0x800)
    print utilities.hex_dump(dump, 0x180018620)
    print([hex(i) for i in dev.execute(0, 0x180018620)])
