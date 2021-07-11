import binascii, datetime, getopt, hashlib, struct, sys, time
import dfu, nor, utilities
import alloc8, checkm8, image3_24Kpwn, limera1n, SHAtter, steaks4uce, usbexec
from dfuexec import *

def start_securedbg():
    try:
        with open("SecureDBG/debugger.bin", 'rb') as f:
            dbgdata = f.read()
    except IOError:
            print 'ERROR: Could not read file:', arg
            sys.exit(1)

    # our rwx view of AOP SRAM
    debugger_entryp = 0x234e00000
    dbgcodesz = len(dbgdata)
    print("debugger code size {}".format(hex(dbgcodesz)))

    device = dfu.acquire_device()

    # response = device.ctrl_transfer(0xa1, 2, 0xfffe, 0, 8, 50000)
    # print(response)
    # print(bytearray(response))
    # sys.exit(0)

    # We send the following:
    #  [copy size (4 bytes)]
    #  [copy offset (4 bytes)]
    #  [done boolean (4 bytes)]
    #  [current chunk of debugger code] */
    # The debugger code is sent in 0x800 byte chunks, since that's
    # the max USB packet size
    # chunk = 0
    offset = 0
    tosend = dbgcodesz
    # to account for metadata before
    maxsend = 2036
    done = 0

    while not done:
        cursendsz = maxsend

        if tosend < maxsend:
            cursendsz = tosend
            done = 1

        # print("Chunk {} tosend {} done: {}".format(hex(chunk), hex(tosend), done))
        dst = debugger_entryp + offset
        codechunk = dbgdata[offset:offset+cursendsz]

        # print("Dst {} cursendsz {} offset {} done: {}".format(hex(dst), hex(cursendsz), hex(offset), done))

        # dbgrequest = struct.pack("<QQII2024s", debugger_entryp, dst, chunk, done, codechunk)
        dbgrequest = struct.pack("<III2036s", cursendsz, offset, done, codechunk)

        # assert device.ctrl_transfer(0x21, 1, 0, 0, dbgrequest, 50000) == 0x800
        # response = device.ctrl_transfer(0xa1, 2, 0xfffe, 0, 8, 50000)
        assert device.ctrl_transfer(0x21, 1, 0, 0, dbgrequest, 5000) == 0x800
        try:
            response = device.ctrl_transfer(0xa1, 2, 0xfffe, 0, 8, 5000)
        except:
            print("Ignoring assert from 0xfffe ctrl transfer")

        offset += cursendsz
        tosend -= cursendsz
    print("Inited")
