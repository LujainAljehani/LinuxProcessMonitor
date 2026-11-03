CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
TARGET = linux_process_monitor
SOURCES = src/main.c src/process_info.c src/display.c src/filter_sort.c src/monitor.c

all: $(TARGET)

$(TARGET): $(SOURCES) include/process_info.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
