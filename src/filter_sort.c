#include "process_info.h"

#include <ctype.h>
#include <string.h>

/* TODO for team member 3:
   Implement case-insensitive substring matching.
   Copy matching processes into results[] without exceeding capacity.
   Return the number of matching processes. */
int filter_by_name(const Process processes[], int count,
                   const char *keyword, Process results[], int capacity)
{
    if (processes == NULL || keyword == NULL || results == NULL ||
        capacity <= 0 || keyword[0] == '\0')
        return 0;

    int found = 0;
    for (int i = 0; i < count && found < capacity; ++i) {
        const char *name = processes[i].name;
        size_t name_len = strlen(name);
        size_t key_len = strlen(keyword);

        if (key_len > name_len)
            continue;

        for (size_t j = 0; j <= name_len - key_len; ++j) {
            size_t k = 0;
            while (k < key_len &&
                   tolower((unsigned char)name[j + k]) ==
                   tolower((unsigned char)keyword[k]))
                ++k;

            if (k == key_len) {
                results[found++] = processes[i];
                break;
            }
        }
    }
    return found;
}

/* TODO for team member 3:
   Implement ascending PID sort. A simple bubble sort is acceptable
   for this project because the process list is relatively small. */
void sort_by_pid(Process processes[], int count)
{
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (processes[j].pid > processes[j + 1].pid) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

/* TODO for team member 3:
   Implement descending memory sort (largest memory first). */
void sort_by_memory(Process processes[], int count)
{
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (processes[j].memory_kb < processes[j + 1].memory_kb) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
