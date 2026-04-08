# sysmon-c - Linux System Monitor

A lightweight system monitoring tool written in C that reads data from the Linux `/proc` filesystem.

## Features
- Real-time CPU usage, memory usage, and system uptime
- Structured data using C structs
- Timestamped logging to `sysmon.log`
- Simple and clean Makefile
- Runs continuously until stopped (Ctrl+C)

## Build & Run

```bash
make          # Compile
./sysmon      # Run the monitor
make clean    # Clean build files
Linux System Monitor (Ctrl+C to stop)

[2026-04-08 16:25:24] CPU: 15.50% | Memory: 667636 KB free / 7573348 KB total (8.8%) | Uptime: 29187 sec
Technologies

C (gcc)
Linux /proc filesystem
Structs and pointers
File I/O and logging
Makefiles

Built as part of refreshing low-level C and Linux system programming skills.
GitHub: https://github.com/Wafnet/linux_sensor_monitor
