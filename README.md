this is team project done by Augustine Osuji and Jesse Abuaja

# simple_shell

---

## ALX Team Project

Authors: Augustine Osuji & Jesse Abuaja

---

This is an ALX team project on Simple Shell with C.

---

Project was done using C language, Betty linter, Shell and other relevant tools

---

## How our simple shell works

It Prints a prompt and waits for a command from the user
Creates a child process in which the command is checked
Checks for built-ins, aliases in the PATH, and local executable programs
The child process is replaced by the command, which accepts arguments
When the command is done, the program returns to the parent process and prints the prompt
The program is ready to receive a new command
To exit: press Ctrl-D or enter "exit" (with or without a status)
Works also in non interactive mode

Command for compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \*.c -o hsh

---

## All Tasks

- 0. Betty would be proud
     Write a beautiful code that passes the Betty checks

- 1. Simple shell 0.1
     Write a UNIX command line interpreter.

- 2. Simple shell 0.2
     Simple shell 0.1 + Handle command lines with arguments

- 3. Simple shell 0.3

  - Simple shell 0.2 +
  - Handle the "PATH"
  - fork must not be called if the command doesn’t exist

- 4. Simple shell 0.4

  - Simple shell 0.3 +
  - Implement the exit built-in, that exits the shell
  - Usage: exit
  - You don’t have to handle any argument to the built-in exit

- 5. Simple shell 1.0

  - Simple shell 0.4 +
  - Implement the env built-in, that prints the current environment

- 6. Simple shell 0.1.1
     -Simple shell 0.1 +

  - -Write your own getline function
    -Use a buffer to read many chars at once and call the least possible the read system call
    -You will need to use static variables
    -You are not allowed to use getline
    -You don’t have to: be able to move the cursor

- 7. Simple shell 0.2.1
     -Simple shell 0.2 +
     -You are not allowed to use strtok

- 8. Simple shell 0.4.1

  - Simple shell 0.4 +

  - handle arguments for the built-in exit
  - Usage: exit status, where status is an integer used to exit the shell

- 9. setenv, unsetenv

  - Simple shell 1.0 +

  - Implement the setenv and unsetenv builtin commands

  - setenv
  - Initialize a new environment variable, or modify an existing one
  - Command syntax: setenv VARIABLE VALUE
  - Should print something on stderr on failure
  - unsetenv
  - Remove an environment variable
  - Command syntax: unsetenv VARIABLE
  - Should print something on stderr on failure

- 10. cd

  - Simple shell 1.0 +

    - Implement the builtin command cd:

    - Changes the current directory of the process.
    - Command syntax: cd [DIRECTORY]
    - If no argument is given to cd the command must be interpreted like cd $HOME
    - You have to handle the command cd -
    - You have to update the environment variable PWD when you change directory
    - man chdir, man getcwd

- 11. ;

  - Simple shell 1.0 +

  - Handle the commands separator ;

- 12. && and ||

  - Simple shell 1.0 +

  - Handle the && and || shell logical operators

- 13. alias

  - Simple shell 1.0 +

  - Implement the alias builtin command
  - Usage: alias [name[='value'] ...]
  - alias: Prints a list of all aliases, one per line, in the form name='value'
  - alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the - form name='value'
  - alias name='value' [...]: Defines an alias for each name whose value is given. - If name is already an alias, replaces its value with value

- 14. Variables

  - Simple shell 1.0 +

  - Handle variables replacement
  - Handle the $? variable
  - Handle the $$ variable

- 15. Comments

  - Simple shell 1.0 +

  - Handle comments (#)

- 16. File as input

  - Simple shell 1.0 +

    - Usage: simple_shell [filename]
    - Your shell can take a file as a command line argument
    - The file contains all the commands that your shell should run before exiting
    - The file should contain one command per line
    - In this mode, the shell should not print a prompt and should not read from stdin
