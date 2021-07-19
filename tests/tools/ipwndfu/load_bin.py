#!/usr/bin/python2.7

import sys, time, struct
import dfu, utilities
import SecureDBG_export

def print_response(r):
    o = str()
    for i in r:
        o = o + chr(i)
    print(o)

device = dfu.acquire_device()

if not device: quit("Couldn't get device handle")

print("We aren't hosed...")

with open(sys.argv[1], "rb") as f:
    print(sys.argv[1])
    try:
        if sys.argv[2] == "0":
            start_securedbg()
    except: pass
    print("start_securedbg")

    time.sleep(1)
    dfu.send_data(device, f.read())

    time.sleep(2)

    response = device.ctrl_transfer(0xa1, 2, 0x4001, 0, 0x800, 10000)
    print_response(response)

while True:
    try:
        time.sleep(2)

        response = device.ctrl_transfer(0xa1, 2, 0x4000, 0, 0x800, 5000)
        print_response(response)

    except KeyboardInterrupt:
        break

    except:
        print("No logs received")

dfu.release_device(device)
