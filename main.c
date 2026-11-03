#include "process_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    Process processes[MAX_PROCESSES];
    Process results[MAX_PROCESSES];

    int choice;

    while (1) {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        if (choice == 0) {
            printf("Exiting Linux Process Monitor. Goodbye!\n");
            break;
        }

        int count = get_processes(processes, MAX_PROCESSES);
        printf("\nCollected %d processes from /proc.\n", count);

        switch (choice) {
            case 1:
                display_processes(processes, count);
                break;

            case 2: {
                char keyword[MAX_NAME];
                printf("Enter process name (or part of it): ");
                scanf("%255s", keyword);

                int matches = filter_by_name(processes, count, keyword,
                                             results, MAX_PROCESSES);
                printf("\nSearch results for '%s':\n", keyword);
                display_processes(results, matches);
                break;
            }

            case 3:
                sort_by_pid(processes, count);
                display_processes(processes, count);
                break;

            case 4:
                sort_by_memory(processes, count);
                display_processes(processes, count);
                break;

            case 5:
                monitor_processes(2);
                break;

            default:
                printf("Unknown option. Please choose 0-5.\n");
        }
    }

    return 0;
}
