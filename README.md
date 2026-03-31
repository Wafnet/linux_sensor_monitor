# Linux Sensor Monitor

A simple C program that monitors Linux system statistics by reading from the `/proc` filesystem.

## Features
- Reads system uptime, memory usage (total + free), and basic CPU usage
- Uses a `struct` to organize sensor data
- Logs data with timestamps to `system_stats.log`
- Built with a clean `Makefile`

## Build & Run

```bash
make          # Compile
make run      # Build and run
make clean    # Clean build files
