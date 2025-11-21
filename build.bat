@echo off
echo Building My Shell for Windows...

REM Create build directory
if not exist build mkdir build

REM Compile all source files
gcc -Wall -Wextra -std=c11 -I./src -c src/main.c -o src/main.o
gcc -Wall -Wextra -std=c11 -I./src -c src/shell.c -o src/shell.o
gcc -Wall -Wextra -std=c11 -I./src -c src/parser/parser.c -o src/parser/parser.o
gcc -Wall -Wextra -std=c11 -I./src -c src/commands/fs_commands.c -o src/commands/fs_commands.o
gcc -Wall -Wextra -std=c11 -I./src -c src/commands/file_read_commands.c -o src/commands/file_read_commands.o
gcc -Wall -Wextra -std=c11 -I./src -c src/commands/sys_commands.c -o src/commands/sys_commands.o
gcc -Wall -Wextra -std=c11 -I./src -c src/commands/proc_commands.c -o src/commands/proc_commands.o
gcc -Wall -Wextra -std=c11 -I./src -c src/commands/net_commands.c -o src/commands/net_commands.o
gcc -Wall -Wextra -std=c11 -I./src -c src/utils/platform.c -o src/utils/platform.o

REM Link all object files
gcc -o build/my_shell.exe src/main.o src/shell.o src/parser/parser.o src/commands/fs_commands.o src/commands/file_read_commands.o src/commands/sys_commands.o src/commands/proc_commands.o src/commands/net_commands.o src/utils/platform.o

if %errorlevel% equ 0 (
    echo Build successful! Executable: build\my_shell.exe
    echo.
    echo To run: build\my_shell.exe
) else (
    echo Build failed!
)

pause