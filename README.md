# minishell
Simple command-line interpreter as project at 42School.

Advanced line editing implemented with autocompletion. Use the
following shortcuts for editing input:

Shift + Page Up   - move cursor up one line,

Shift + Page Down - move cursor down one line,

Shift + Left      - move cursor left by one word,

Shift + Right     - move cursor right by one word,

Shift + Home      - move cursor to the begining of the line,

Shift + End       - move cursor to the end of the line,

Ctrl + A - copy all the line to clipboard,

Ctrl + B - copy the line before cursor to clipboard,

Ctrl + F - copy the line from cursor to the end to clipboard,

Ctrl + X - cut all the line to clipboard,

Ctrl + U - cut the line before cursor to clipboard,

Ctrl + K - cut the line from cursor to the end to clipboard,

Ctrl + P - paste from clipboard,

TAB      - launch autocompletion.


Also terminating of launched commmand is available with Ctrl+C.

Pipes and IO redirection are being implemented.
