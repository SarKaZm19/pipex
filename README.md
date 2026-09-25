# pipex

A small Unix process and pipe exercise written in **C**, developed as part of the 42 curriculum.

The goal is to reproduce the data flow of a shell pipeline by connecting processes manually with `pipe()`, `fork()`, `dup2()` and `execve()`.

## What it reproduces

The mandatory program:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

behaves like:

```bash
< infile cmd1 | cmd2 > outfile
```

Instead of delegating that work to a shell, pipex has to build the pipeline itself: open the files, create the pipe, fork the children, redirect their standard input/output and resolve each executable before calling `execve()`.

## Highlights

- Unix pipes and file descriptors
- Process creation with `fork()`
- Input/output redirection with `dup2()`
- Command execution with `execve()`
- Executable lookup through `PATH`
- Support for commands containing arguments
- File opening and permission/error handling
- Child-process synchronization with `waitpid()`
- Bonus support for multiple commands
- Bonus `here_doc` mode

## How the mandatory pipeline works

For:

```bash
./pipex infile "grep hello" "wc -l" outfile
```

the program creates the equivalent of:

```text
infile
  │
  ▼
cmd1 process
  │ stdout
  ▼
 pipe
  │ stdin
  ▼
cmd2 process
  │
  ▼
outfile
```

The first child redirects the input file to `STDIN_FILENO` and the pipe's write end to `STDOUT_FILENO`.

The second child redirects the pipe's read end to `STDIN_FILENO` and the output file to `STDOUT_FILENO`.

Unused file descriptors are closed in each process before execution. The parent closes its own pipe descriptors and waits for the children.

## Command resolution

Commands are parsed into an argument array before execution.

If the command contains a path, pipex checks that path directly. Otherwise, it extracts the directories from the environment's `PATH` variable and searches them until it finds an executable candidate.

That turns a command such as:

```text
grep hello
```

into the `argv` expected by `execve()`, while resolving `grep` to its executable path.

## Bonus

The bonus version generalizes the same model to an arbitrary command chain:

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```

Conceptually:

```text
infile → cmd1 → pipe → cmd2 → pipe → cmd3 → ... → cmdN → outfile
```

It dynamically creates the required pipes and connects each command to the previous and next stage.

It also implements heredoc-style input:

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" ... outfile
```

In this mode, input is collected until `LIMITER` is reached and the output file is opened in append mode, mirroring the shell pattern:

```bash
cmd1 << LIMITER | cmd2 >> outfile
```

## Build

Mandatory:

```bash
make
```

Bonus:

```bash
make bonus
```

Clean generated objects and binaries:

```bash
make fclean
```

## Example

```bash
echo -e "hello\nworld\nhello again" > input.txt

./pipex input.txt "grep hello" "wc -l" output.txt
cat output.txt
```

Expected output:

```text
2
```

## What this project demonstrates

pipex is small, but it exposes several mechanisms normally hidden behind a shell command.

A single `|` in a terminal represents process creation, file-descriptor routing, executable lookup, synchronization and careful resource management. Rebuilding that path manually makes the Unix process model much more concrete.

---

Part of my developer portfolio: **[github.com/Overflow-ADW](https://github.com/Overflow-ADW)**  
Professional work: **[Avenue du Web](https://avenueduweb.be)**
