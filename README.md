# 21sh | minishell

A command line interface as project at 42School.

## Installing

To compile this project termcap library installed on your computer will be required on Linux.
For example on Ubuntu termcap library may be added using
```
sudo apt-get install libncurses5-dev
```
After termcap is installed
```
make
```

## Launching shell

Shell can be launched as interactive application:
```
./21sh
```
or for executing instructions from file:
```
./21sh [file]
```

## Features

Shell syntax supports the following command delimiters with behaviour as in all of shells:
```
; || && |
```

The following I/O redirections supported:
```
>, <, >>, <<.
```
Text followed after unquoted '#' considered as a comment.

Shell has the following builtin functions:
```
echo, pwd, cd, env, setenv, unsetenv, exit, help
```
To see builtin command usage use the following syntax:
```
help [builtin name]
```

Implemented hash table for storing binary files paths.

## Shortcuts
Note: depending on OS shortcuts may not work.

Input editing shortcuts:

| Command | Description |
| :---: | --- |
| Shift + Page Up | Move cursor up one line |
| Shift + Page Down | Move cursor down one line |
| Shift + Left | Move cursor left by one word |
| Shift + Right | Move cursor right by one word |
| Shift + Home | Move cursor to the begining of the line |
| Shift + End | Move cursor to the end of the line |
| Ctrl + A | Copy all the line to clipboard |
| Ctrl + B | Copy the line before cursor to clipboard |
| Ctrl + F | Copy the line from cursor to the end to clipboard |
| Ctrl + X | Cut all the line to clipboard |
| Ctrl + U | Cut the line before cursor to clipboard |
| Ctrl + K | Cut the line from cursor to the end to clipboard |
| Ctrl + P | Paste from clipboard |
| TAB      | Launch autocompletion |
| Ctrl + C | Stop launched process |
| Ctrl + R | Reverse history search |

