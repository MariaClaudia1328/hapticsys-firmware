# Hapticsys Firmware

## Description

<!-- TODO: give a better description -->
A firmware to actuate hapticsys signals

## Requirements

- PlatformIO [VS Code extension]
- Linux Operating System

## Troubleshooting (PlatformIO)

### PlatformIO cannot find the serial port 

First, garantee that your OS knows about the serial port. To that, you can use the command on terminal:

```bash 
ls /dev/tty*
```

This commando will give you a list of all serial ports. Your serial port will look like `/ttyUSB*` or `ttyACM*`.

Then, you can give permission to access, write and read the serial port using the following command:

```bash 
sudo chmod a+rw /dev/ttyUSB* #or /dev/ttyACM*
```

After that, you can try the flash via PlatformIO again.

## Notes

- This hasn't been tested on Windows or WSL
