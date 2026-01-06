<img height="50" align="right" src="https://raw.githubusercontent.com/fchavonet/fchavonet/refs/heads/main/assets/images/logo-holberton_school.webp" alt="Holberton School logo">

# Simple Shell
A simple UNIX command line interpreter implemented in C as part of the Holberton School curriculum.

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black)
## Table of Contents

- [Description](#description)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Interactive Mode](#interactive-mode)
  - [Non-Interactive Mode](#non-interactive-mode)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Function Descriptions](#function-descriptions)
- [Built-in Commands](#built-in-commands)
- [Error Handling](#error-handling)
- [Technical Details](#technical-details)
- [Limitations](#limitations)
- [Authors](#authors)

## Description

This project is a basic implementation of a UNIX shell that can execute commands, handle the PATH environment variable, and provide both interactive and non-interactive modes.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- **Operating System**: Linux or Unix-based system (Ubuntu 20.04 LTS or similar)
- **Compiler**: GCC (GNU Compiler Collection)
- **Standard C Library**: glibc
- **Shell**: Access to a terminal/command line interface
- **Git**: For cloning the repository
- **Permissions**: User privileges to compile and execute programs

### Installation

1. Clone the repository:
```bash
git clone https://github.com/benji3106/holbertonschool-simple_shell.git
```

2. Navigate to the project directory:
```bash
cd holbertonschool-simple_shell
```

3. Compile the shell:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shellobscur
```

4. Run the shell:
```bash
./shellobscur
```

## Usage

### Interactive Mode

Run the shell without any arguments:

```bash
./shellobscur
```

You'll see the prompt `shellobscur ` where you can type commands:

```bash
shellobscur ls -l
shellobscur /bin/pwd
shellobscur exit
```

### Non-Interactive Mode

You can also pipe commands into the shell:

```bash
echo "ls -la" | ./shellobscur
```

Or use input redirection:

```bash
./shellobscur < commands.txt
```

## Examples

```bash
$ ./shellobscur
shellobscur pwd
/home/user/holbertonschool-simple_shell
shellobscur ls
env.c  execute.c  exit.c  main.c  path.c  print_env.c  prompt.c  README.md  shell.h  tokenize.c
shellobscur env
HOME=/home/user
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
PWD=/home/user/holbertonschool-simple_shell
...
shellobscur exit
$
```

## Project Structure

| File | Description |
|------|-------------|
| `shell.h` | Header file containing function prototypes and includes |
| `main.c` | Entry point and main loop of the shell |
| `execute.c` | Handles command execution using `fork()` and `execve()` |
| `tokenize.c` | Splits input line into tokens (arguments) |
| `path.c` | Resolves command paths using the PATH environment variable |
| `env.c` | Retrieves environment variable values |
| `print_env.c` | Implements the `env` built-in command |
| `exit.c` | Implements the `exit` built-in command |
| `prompt.c` | Displays the shell prompt in interactive mode |

## Function Descriptions

### Main Functions

- **`main()`**: Shell entry point, handles the main read-eval loop
- **`process_line()`**: Parses and executes a single line of input
- **`execute_cmd()`**: Forks and executes a command using `execve()`
- **`tokenize()`**: Splits input string into array of arguments
- **`resolve_path()`**: Searches for executable in PATH or validates absolute/relative path
- **`get_env_value()`**: Retrieves value of an environment variable
- **`print_env()`**: Prints all environment variables
- **`handle_exit()`**: Cleans up and exits the shell
- **`print_prompt()`**: Displays prompt in interactive mode

## Built-in Commands

### `exit` or `osokour`
Exits the shell with the status of the last executed command.

### `env`
Prints all environment variables to standard output.

## Error Handling

The shell handles various error conditions:
- Command not found (exit status 127)
- Fork failures
- Memory allocation failures
- Invalid commands

Error messages follow the format: `shell_name: line_number: command: not found`

## Technical Details

- **Language**: C (C89 standard)
- **System Calls Used**: `fork()`, `execve()`, `wait()`, `waitpid()`, `getline()`, `access()`, `write()`
- **Memory Management**: All dynamically allocated memory is properly freed
- **Maximum Arguments**: 64 arguments per command (MAX_ARGS)

## Limitations

- No support for command separators (`;`, `&&`, `||`)
- No pipe (`|`) or redirection (`>`, `<`, `>>`) operators
- No environment variable expansion (`$VAR`)
- No wildcard expansion (`*`, `?`)
- No command history or line editing
- No job control (background processes, `fg`, `bg`)

## Authors

|    | Name               | GitHub                                          |
|:--:|--------------------|-------------------------------------------------|
| 👩‍💻 | Benjamin BOMMIER   | [@benji3106](https://github.com/benji3106) |
| 👨‍💻 | Matéo MARQUES      | [@serkam31](https://github.com/serkam31)         |

*Students at [Holberton School](https://www.holbertonschool.com/)*
