#include "platform.h"


void clear_screen(void)
{
    #ifdef PLATFORM_WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}

void sleep_ms(int milliseconds)
{
    #ifdef PLATFORM_WINDOWS
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

int file_exist(const char *path)
{
    return access_wrapper(path, F_OK) == 0;
}

int is_directory(const char *path)
{
    #ifdef PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES && 
            (attrs & FILE_ATTRIBUTE_DIRECTORY));
    #else
        struct stat st;
        if (stat(path, &st) == 0) {
            return S_ISDIR(st.st_mode);
        }
        return 0;
    #endif
}

char* get_home_directory(void)
{
    static char home[MAX_PATH_LEN];
    #ifdef PLATFORM_WINDOWS
        char *drive = getenv("HOMEDRIVE");
        char *path = getenv("HOMEPATH");
        if (drive && path) {
            snprintf(home, MAX_PATH_LEN, "%s%s", drive, path);
            return home;
        }
        return "C:\\";
    #else
        char *home_env = getenv("HOME");
        if (home_env) {
            strncpy(home, home_env, MAX_PATH_LEN - 1);
            return home;
        }
        return "/";
    #endif
}