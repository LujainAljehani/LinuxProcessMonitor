#include "process_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* TODO for team member 4:
   Implement live monitoring:
   - Repeat until the user presses a chosen key (for example q).
   - Each refresh: collect processes, clear terminal, display timestamp
     or refresh count, and print the process table.
   - Sleep for refresh_seconds between updates.
   Hint: use select() or noncanonical terminal input if you want
   non-blocking keyboard input. A simpler first version can run a
   fixed number of refreshes and then return to the menu. */
void monitor_processes(int refresh_seconds)
{
    if (refresh_seconds < 1)
        refresh_seconds = 2;

    Process processes[MAX_PROCESSES];

    /* Starter version: show five updates, then return to menu.
       Replace this with keyboard-controlled monitoring if desired. */
    for (int update = 1; update <= 5; ++update) {
        int count = get_processes(processes, MAX_PROCESSES);

        printf("\033[2J\033[H"); /* Clear terminal and move cursor home. */
        printf("LIVE MONITOR - refresh %d/5 (every %d seconds)\n",
               update, refresh_seconds);
        display_processes(processes, count);
        fflush(stdout);

        if (update < 5)
            sleep((unsigned int)refresh_seconds);
    }
}
