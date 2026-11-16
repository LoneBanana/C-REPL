# C-REPL

A minimalist way to run snippets of C without writing a full program, built on temporary files.

## Overview

Testing a small piece of C usually means creating a file, writing `#include` lines and a `main` function, compiling, and running. This project removes that boilerplate: you type only the statements you want to try, and the program wraps them in a complete C file, compiles it, and runs it.

Under the hood it creates a secure temporary file with `mkstemp`, writes `#include` lines for the C standard library headers, opens `int main(int argc, char **argv) {`, appends your code, and closes it with `return 0; }`. It then compiles the file with `cc`, runs the result, and deletes it.

## What's inside

- `main.c` - the whole program.

## Building and running

```sh
cc main.c -o crepl
./crepl
```

Type the body of `main`, then press Ctrl+D to end input:

```
int x = 6 * 7;
printf("%d\n", x);
^D
42
```

Input can also be piped in:

```sh
printf 'puts("hello");\n' | ./crepl
```

## Status

Early but working. The current version is one-shot: it reads one snippet until end of input, runs it, and exits. It does not loop yet, and it does not keep state between snippets. Input is limited to 2047 bytes. The list of included headers contains newer ones (`<stdckdint.h>` from C23 and `<stdcountof.h>`), so an older compiler may fail on them.

## Tech

C, POSIX (`mkstemp`, `fdopen`, `unlink`), and the system C compiler (`cc`).
