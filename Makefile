# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -I./src

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = build/my_shell.exe
    RM = del /Q
    MKDIR = if not exist build mkdir build
    LIBS = 
else
    TARGET = build/my_shell
    RM = rm -f
    MKDIR = mkdir -p build
    LIBS = 
endif

# Source files
SRC = src/main.c \
      src/shell.c \
      src/parser/parser.c \
      src/commands/fs_commands.c \
      src/commands/file_read_commands.c \
      src/commands/sys_commands.c \
      src/commands/proc_commands.c \
      src/commands/net_commands.c \
      src/utils/platform.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJ)
	$(MKDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)
	@echo Build complete: $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	del /Q /S *.o 2>nul || exit 0
	del /Q build\*.exe 2>nul || exit 0
else
	$(RM) $(OBJ)
	$(RM) $(TARGET)
endif
	@echo Clean complete

# Run the shell
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run