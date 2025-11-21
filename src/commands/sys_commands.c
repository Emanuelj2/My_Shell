#include "sys_commands.h"
#include "../utils/platform.h"
#include <stdio.h>
#include <time.h>

void cmd_clear(int argc, char **argv) {
    (void)argc;  // Unused parameter
    (void)argv;  // Unused parameter
    clear_screen();
}

void cmd_exit(int argc, char **argv, ShellState *state) {
    printf("Goodbye!\n");
    state->running = 0;
}

void cmd_sleep(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: sleep <milliseconds>\n");
        return;
    }
    
    int ms = atoi(argv[1]);
    printf("Sleeping for %d ms...\n", ms);
    sleep_ms(ms);
    printf("Done.\n");
}

void cmd_time(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: time <command> [args...]\n");
        return;
    }
    
    clock_t start = clock();
    
    // This would need to execute the command
    // For now, just measure the time
    printf("Command: %s (timing not fully implemented)\n", argv[1]);
    
    clock_t end = clock();
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %.4f seconds\n", cpu_time);
}

void cmd_help(int argc, char **argv) {
    printf("\n=== My Shell - Available Commands ===\n\n");
    
    printf("File System Commands:\n");
    printf("  mkdir <dir>           - Create a directory\n");
    printf("  rmdir <dir>           - Remove an empty directory\n");
    printf("  rm <file>             - Remove a file\n");
    printf("  touch <file>          - Create an empty file\n");
    printf("  ls [dir]              - List files in directory\n");
    printf("  cd [dir]              - Change directory\n");
    printf("  pwd                   - Show current directory\n");
    printf("  cp <src> <dst>        - Copy a file\n");
    printf("  mv <src> <dst>        - Move or rename a file\n");
    printf("  tree [dir]            - Print directory tree\n");
    
    printf("\nFile Operations:\n");
    printf("  cat <file>            - Print file contents\n");
    printf("  echo <text> [> file]  - Print text or write to file\n");
    
    printf("\nSystem Commands:\n");
    printf("  clear                 - Clear the screen\n");
    printf("  exit                  - Exit the shell\n");
    printf("  sleep <ms>            - Pause execution\n");
    printf("  time <cmd>            - Measure execution time\n");
    printf("  help                  - Show this help message\n");
    
    printf("\nShell Features:\n");
    printf("  history               - Show command history\n");
    printf("  alias <name> <cmd>    - Create command alias\n");
    printf("  set [key] [value]     - Set/list environment variables\n");
    printf("  export <key>=<value>  - Export environment variable\n");
    
    printf("\nProcess Commands:\n");
    printf("  ps                    - List processes\n");
    printf("  kill <pid>            - Kill a process\n");
    printf("  run <program>         - Run an executable\n");
    
    printf("\nNetwork Commands:\n");
    printf("  ping <host>           - ICMP ping\n");
    printf("  ifconfig/ipconfig     - Show network adapters\n");
    
    printf("\n");
}