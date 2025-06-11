# Simple Shell Project

This project implements a basic UNIX command line interpreter, or shell. It's a foundational step in understanding how operating systems and shell environments work.

## Features

-   **Command Execution**: Executes commands with arguments.
-   **Path Handling**: Searches for executables in the system's PATH.
-   **Built-in Commands**: (Future: Implement simple built-ins like `exit`, `env`).
-   **Error Handling**: Basic error messages for invalid commands or permissions.

## How to Compile and Run

To compile the shell:
```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh
./hsh
<span class="math-inline">\./hsh</span> # Type your commands here, e.g., ls -l /tmp
$ exit
bash
exit
