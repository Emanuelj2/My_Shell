#include "proc_commands.h"
#include "../utils/platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <tlhelp32.h>
#else
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

void cmd_ps(int argc, char **argv) {
    (void)argc;  // Unused parameter
    (void)argv;  // Unused parameter
    
#ifdef PLATFORM_WINDOWS
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to create process snapshot\n");
        return;
    }
    
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    printf("%-10s %-40s\n", "PID", "Process Name");
    printf("-----------------------------------------------------\n");
    
    if (Process32First(hSnapshot, &pe32)) {
        do {
            printf("%-10lu %-40s\n", pe32.th32ProcessID, pe32.szExeFile);
        } while (Process32Next(hSnapshot, &pe32));
    }
    
    CloseHandle(hSnapshot);
#else
    printf("Running 'ps aux' command:\n");
    system("ps aux");
#endif
}

void cmd_kill(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: kill <pid>\n");
        return;
    }
    
    int pid = atoi(argv[1]);
    
#ifdef PLATFORM_WINDOWS
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to open process %d\n", pid);
        return;
    }
    
    if (TerminateProcess(hProcess, 0)) {
        printf("Process %d terminated\n", pid);
    } else {
        printf("Failed to terminate process %d\n", pid);
    }
    
    CloseHandle(hProcess);
#else
    if (kill(pid, SIGTERM) == 0) {
        printf("Process %d terminated\n", pid);
    } else {
        perror("kill failed");
    }
#endif
}

void cmd_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: run <program> [args...]\n");
        return;
    }
    
    // Build command string
    char command[1024] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) strcat(command, " ");
    }
    
    printf("Running: %s\n", command);
    int result = system(command);
    printf("Program exited with code: %d\n", result);
}