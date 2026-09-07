SIMPLE LINE EDITOR

PROJECT DESCRIPTION
A simple line-based text editor written in C.
It allows users to create, modify, display, save,
and load text documents through terminal commands.

FEATURES

Core Features:
- Insert a line
- Delete a line
- Display the document
- Save document to a .txt file
- Load document from a .txt file

Bonus Features:
- Search text
- Find and replace
- Undo last action
- Line and word count

DATA STRUCTURE

The document is stored using a 2D character array:

char doc[100][200];

Maximum:
100 lines
199 characters per line

COMMANDS

insert <n>
delete <n>
display
save <file>
load <file>
search <word>
replace <old> <new>
undo
count
help
quit

COMPILATION

gcc main.c -o editor

RUN

./editor

To load a file at startup:

./editor document.txt

EXAMPLE

> insert 1
Enter text: Hello world

> insert 2
Enter text: C programming

> display

> search Hello

> replace Hello Hi

> count

> save document.txt

> quit

FILES

main.c
    Source code of the editor.

help.txt
    Command documentation and usage examples.

README.txt
    Project overview and instructions.

TEAM

Team members:
1. __________________
2. __________________
3. __________________