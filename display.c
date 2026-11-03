#include "process_info.h"

#include <stdio.h>

void display_menu(void)
{
    printf("\n========== LINUX PROCESS MONITOR ==========\n");
    printf("1. Display all processes\n");
    printf("2. Search processes by name\n");
    printf("3. Sort processes by PID\n");
    printf("4. Sort processes by memory usage\n");
    printf("5. Live monitoring\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

void display_processes(const Process processes[], int count)
{
    printf("\n%-8s %-8s %-8s %-10s %s\n",
           "PID", "PPID", "STATE", "MEM(KB)", "NAME");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; ++i) {
        printf("%-8d %-8d %-8c %-10lu %s\n",
               processes[i].pid,
               processes[i].ppid,
               processes[i].state,
               processes[i].memory_kb,
               processes[i].name);
    }

    printf("\nTotal processes: %d\n", count);
}
