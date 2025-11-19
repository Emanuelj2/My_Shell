# My Shell - Cross-Platform C Shell Implementation

A feature-rich command-line shell written in C that works on both Windows and Linux/Unix systems.

## Features

### File System Commands
- `mkdir <dir>` - Create a directory
- `rmdir <dir>` - Remove an empty directory
- `rm <file>` - Remove a file
- `touch <file>` - Create an empty file
- `ls [dir]` - List files in directory
- `cd [dir]` - Change directory (no args = home)
- `pwd` - Show current directory
- `cp <src> <dst>` - Copy a file
- `mv <src> <dst>` - Move or rename a file
- `tree [dir]` - Print directory tree

### File Operations
- `cat <file>` - Print file contents
- `echo <text> [> file]` - Print text or write to file

### System Commands
- `clear` - Clear the screen
- `exit` - Exit the shell
- `sleep <ms>` - Pause execution (milliseconds)
- `time <cmd>` - Measure execution time
- `help` - Show available commands

### Shell Features
- `history` - Show command history (up to 100 commands)
- `alias <name> <cmd>` - Create command alias
- `set [key] [value]` - Set/list environment variables
- `export KEY=VALUE` - Export environment variable

### Process Commands
- `ps` - List running processes
- `kill <pid>` - Kill a process by PID
- `run <program> [args]` - Run an executable

### Network Commands
- `ping <host>` - ICMP ping a host
- `ifconfig`/`ipconfig` - Show network adapters
- `curl <url>` - Make HTTP request (requires curl installed)

## Building

### Linux/Unix
```bash
make
./build/my_shell
```

### Windows
```bash
make
build\my_shell.exe
```

Or use the batch file:
```bash
build.bat
```

### Clean Build
```bash
make clean
```

## Project Structure

```
my_shell/
├── src/
│   ├── main.c              # Entry point
│   ├── shell.c             # Main shell logic
│   ├── shell.h             # Shell header
│   ├── parser/
│   │   ├── parser.c        # Command parser
│   │   └── parser.h
│   ├── commands/
│   │   ├── fs_commands.c   # File system commands
│   │   ├── fs_commands.h
│   │   ├── sys_commands.c  # System commands
│   │   ├── sys_commands.h
│   │   ├── file_read_commands.c  # cat, echo
│   │   ├── file_read_commands.h
│   │   ├── proc_commands.c # Process commands
│   │   ├── proc_commands.h
│   │   ├── net_commands.c  # Network commands
│   │   └── net_commands.h
│   └── utils/
│       ├── platform.c      # Platform abstraction
│       └── platform.h
├── build/                  # Compiled executables
├── Makefile               # Build system
├── build.bat              # Windows build script
└── README.md              # This file
```

## Platform Differences

The shell automatically handles platform-specific differences:

### Windows
- Uses `\` as path separator
- Uses Windows API for process listing
- Uses `_mkdir`, `_rmdir`, etc.
- Clears screen with `cls`

### Linux/Unix
- Uses `/` as path separator
- Uses POSIX APIs for process management
- Uses standard `mkdir`, `rmdir`, etc.
- Clears screen with `clear`

## Examples

### Basic Usage
```bash
# Navigate and list files
pwd
ls
cd Documents
mkdir new_folder
touch test.txt

# File operations
echo "Hello World" > test.txt
cat test.txt
cp test.txt backup.txt

# Process management
ps
run notepad.exe  # Windows
run gedit         # Linux

# Aliases
alias ll "ls"
ll

# Environment variables
set USER john
export PATH=/usr/bin
set
```

### Advanced Features
```bash
# Command history
history

# Directory tree
tree .

# Network operations
ping google.com
ifconfig

# Timing commands
time ls -la
```

## Requirements

- C compiler (GCC recommended)
- Make (for building)
- Windows: MinGW or Visual Studio
- Linux: Standard development tools

## Limitations

- No pipe (`|`) support yet
- No background processes (`&`)
- No input redirection (`<`)
- Network commands require external tools (curl)
- Limited error handling in some commands

## Future Enhancements

- [ ] Pipe support
- [ ] Input/output redirection
- [ ] Background process execution
- [ ] Tab completion
- [ ] Configuration file (.shellrc)
- [ ] Script execution
- [ ] More advanced networking (native implementation)
