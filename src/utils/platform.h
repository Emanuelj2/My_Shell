#ifndef PLATFORM_H
#define PLATFORM_H

// Platform detection
#ifdef _WIN32
    #define PLATFORM_WINDOWS
    #include <windows.h>
    #include <direct.h>
    #include <io.h>
    #define PATH_SEPARATOR "\\"
    #define MAX_PATH_LEN MAX_PATH
    #define getcwd_wrapper _getcwd
    #define chdir_wrapper _chdir
    #define mkdir_wrapper(path) _mkdir(path)
    #define rmdir_wrapper _rmdir
    #define unlink_wrapper _unlink
    #define access_wrapper _access
    #define F_OK 0
#else
    #define PLATFORM_UNIX
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #define PATH_SEPARATOR "/"
    #define MAX_PATH_LEN 4096
    #define getcwd_wrapper getcwd
    #define chdir_wrapper chdir
    #define mkdir_wrapper(path) mkdir(path, 0755)
    #define rmdir_wrapper rmdir
    #define unlink_wrapper unlink
    #define access_wrapper access
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Platform-specific functions
void clear_screen(void);
void sleep_ms(int milliseconds);
int file_exists(const char *path);
int is_directory(const char *path);
char* get_home_directory(void);

#endif // PLATFORM_H