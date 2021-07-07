# pongo-flash

`What is this repo?`

--This is a WIP driver for the pongoOS pre-boot environment. It's meant to be updated incrementally and for a multitude of tests to be done on a device before any code is considered stable or safe.

`What is this driver for?`

--This driver aims to bring a stable and easy interface with Apple's SPI to pongoOS, and even builds on this SPI layer to interface with the NAND chip present on pongoOS devices (if applicable).

`How is this driver being developed?`

--I am reverse engineering the secureROM of an iPhone to analyze and identify important functions and data structures that will be necessary to successfully operate this driver. A systematic approach is being taken by reversing and taking bits of the driver present in the ROM, running them, identifying potential issues, and reimplementing them to be suitable for a pongoOS driver.

`Can I run this code?`

--Unless you are 100% sure you know what you're doing: **DO NOT RUN THIS CODE**. This is meant for development of the driver until there is an official announcement or this README says otherwise. Everything in here is not guaranteed to behave/work properly on everyone's device.

`What devices will this driver support?`

--For now, driver support for the _T8015_ Apple SoC on an iPhone 8 is in development, and is planned to be supported first.

`Why is this driver useful?`

--This driver is mostly a fun summer project for me, but it can prove to be extremely useful. Things like loading kexts from Cydia can be possible, or providing an easy way for others to have a deeper look into the NAND chip on an Apple device.
