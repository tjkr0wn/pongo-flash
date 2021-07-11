#!/usr/bin/python2.7

import sys, time, struct
import dfu, utilities

device = dfu.acquire_device()

if not device:
    quit("Couldn't get device handle")

print("We aren't hosed...")

with open(sys.argv[1], "rb") as f:
    dfu.send_data(device, "A" * 41)
    time.sleep(1)
    response = device.ctrl_transfer(0xa1, 2, 0x4001, 0, 0, 10000)
    print(response)
    print(bytearray(response))

dfu.release_device(device)
