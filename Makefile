CC = gcc
CFLAGS = -Wall -g -std=c99

all: sensor_monitor

sensor_monitor: sensor_monitor.o
	$(CC) $(CFLAGS) -o sensor_monitor sensor_monitor.o

sensor_monitor.o: sensor_monitor.c
	$(CC) $(CFLAGS) -c sensor_monitor.c

clean:
	rm -f *.o sensor_monitor system_stats.log

run: sensor_monitor
	./sensor_monitor
	cat system_stats.log
