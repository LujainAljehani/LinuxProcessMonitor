# Linux Process Monitor

A terminal-based Linux process monitor written in C for ICS 433 Operating Systems Lab.

## Requirements
- Ubuntu/Linux
- GCC
- Make

Install build tools if needed:

```bash
sudo apt update
sudo apt install build-essential
```

## Compile

From the project root:

```bash
make
```

Or compile manually:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o linux_process_monitor
```

## Run

```bash
./linux_process_monitor
```

## Modules

- `process_info.c`: reads process data from `/proc`.
- `display.c`: terminal menu and process table.
- `filter_sort.c`: filtering and sorting.
- `monitor.c`: periodic process refresh.
- `main.c`: connects the modules.

## Important notes

- This project uses the Linux `/proc` filesystem; it is not a kernel module.
- A process can exit while `/proc` is being read. Such entries are skipped.
- Memory is shown as resident set size (RSS), converted to KB.
- CPU percentage is not implemented in this starter version.

## Team TODOs

- Improve input validation and user experience.
- Add CPU usage calculation if selected by the team.
- Improve live-monitor exit handling.
- Add tests and document limitations.
