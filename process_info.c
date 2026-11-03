#include "process_info.h"

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Return 1 if text contains only decimal digits. */
static int is_numeric_name(const char *text)
{
    if (text == NULL || *text == '\0')
        return 0;

    for (const unsigned char *p = (const unsigned char *)text; *p; ++p) {
        if (!isdigit(*p))
            return 0;
    }
    return 1;
}

/* Read one /proc/PID/stat file.
   The process name is enclosed in parentheses and may contain spaces.
   We locate the final ')' before parsing the remaining fields. */
static int read_one_process(const char *pid_text, Process *process)
{
    char path[128];
    char line[4096];

    snprintf(path, sizeof(path), "/proc/%s/stat", pid_text);

    FILE *fp = fopen(path, "r");
    if (fp == NULL)
        return 0; /* Process may have exited while we were scanning. */

    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    fclose(fp);

    char *left = strchr(line, '(');
    char *right = strrchr(line, ')');
    if (left == NULL || right == NULL || right <= left)
        return 0;

    size_t name_length = (size_t)(right - left - 1);
    if (name_length >= sizeof(process->name))
        name_length = sizeof(process->name) - 1;

    memcpy(process->name, left + 1, name_length);
    process->name[name_length] = '\0';

    /* After ") " the fields begin at field 3:
       state (3), ppid (4), ... vsize (23), rss (24). */
    char *saveptr = NULL;
    char *token = strtok_r(right + 2, " ", &saveptr);
    if (token == NULL)
        return 0;

    process->state = token[0];

    token = strtok_r(NULL, " ", &saveptr); /* field 4: PPID */
    if (token == NULL)
        return 0;
    process->ppid = atoi(token);
    process->pid = atoi(pid_text);

    /* Skip fields 5 through 23 (19 fields) to reach RSS, field 24. */
    for (int field = 5; field <= 23; ++field) {
        token = strtok_r(NULL, " ", &saveptr);
        if (token == NULL)
            return 0;
    }

    token = strtok_r(NULL, " ", &saveptr); /* field 24: RSS pages */
    if (token == NULL)
        return 0;

    long rss_pages = atol(token);
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0)
        page_size = 4096;

    process->memory_kb = (unsigned long)((rss_pages > 0 ? rss_pages : 0) *
                                         page_size / 1024);
    return 1;
}

int get_processes(Process processes[], int capacity)
{
    if (processes == NULL || capacity <= 0)
        return 0;

    DIR *proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Could not open /proc");
        return 0;
    }

    int count = 0;
    struct dirent *entry;

    while ((entry = readdir(proc_dir)) != NULL && count < capacity) {
        if (!is_numeric_name(entry->d_name))
            continue;

        if (read_one_process(entry->d_name, &processes[count]))
            ++count;
    }

    closedir(proc_dir);
    return count;
}
