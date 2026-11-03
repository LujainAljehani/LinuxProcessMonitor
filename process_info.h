#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#define _POSIX_C_SOURCE 200809L
#include <stddef.h>

#define MAX_PROCESSES 10000
#define MAX_NAME 256

typedef struct {
    int pid;
    int ppid;
    char name[MAX_NAME];
    char state;
    unsigned long memory_kb;
} Process;

/* Reads process information from /proc into the supplied array.
   Returns the number of processes collected. */
int get_processes(Process processes[], int capacity);

/* Display functions */
void display_processes(const Process processes[], int count);
void display_menu(void);

/* Filtering and sorting */
int filter_by_name(const Process processes[], int count,
                   const char *keyword, Process results[], int capacity);
void sort_by_pid(Process processes[], int count);
void sort_by_memory(Process processes[], int count);

/* Live monitoring */
void monitor_processes(int refresh_seconds);

#endif
