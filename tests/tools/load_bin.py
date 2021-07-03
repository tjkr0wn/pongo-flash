import usbexec
import dfu
import sys
import time
import utilities
import struct

#device = usbexec.PwnedUSBDevice()
device = dfu.acquire_device()
if not device:
    quit("Couldn't get device handle")
#dfu.send_data(device, "A" * 400)
dfu.release_device(device)
dev = usbexec.PwnedUSBDevice()

with open(sys.argv[1], "rb") as f:
    dev.write_memory(0x1800B0800, f.read())
    dump = dev.read_memory(0x1800B0800, 0x800)
    print utilities.hex_dump(dump, 0x1800B0800)
    print dev.execute(0, 0x1800B0800)
