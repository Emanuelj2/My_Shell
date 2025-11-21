#include "net_commands.h"
#include "../utils/platform.h"
#include <stdio.h>
#include <stdlib.h>

void cmd_ping(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ping <host>\n");
        return;
    }
    
#ifdef PLATFORM_WINDOWS
    char command[256];
    snprintf(command, sizeof(command), "ping -n 4 %s", argv[1]);
    system(command);
#else
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", argv[1]);
    system(command);
#endif
}

void cmd_ifconfig(int argc, char **argv) {
    (void)argc;  // Unused parameter
    (void)argv;  // Unused parameter
    
#ifdef PLATFORM_WINDOWS
    printf("Network Configuration (ipconfig):\n");
    system("ipconfig");
#else
    printf("Network Configuration (ifconfig):\n");
    system("ifconfig");
#endif
}

void cmd_curl(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: curl <url>\n");
        return;
    }
    
    // Simple implementation using system curl
    char command[512];
    snprintf(command, sizeof(command), "curl %s", argv[1]);
    
    printf("Fetching %s...\n", argv[1]);
    int result = system(command);
    
    if (result != 0) {
        printf("\nNote: curl must be installed on your system\n");
    }
}