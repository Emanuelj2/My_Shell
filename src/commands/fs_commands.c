#include "fs_commands.h"
#include "../utils/platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PLATFORM_UNIX
#include <dirent.h>
#include <sys/stat.h>
#endif

void cmd_mkdir(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Usage: mkdir <directory>\n");
        return;
    }
    
    if (mkdir_wrapper(argv[1]) == 0)
    {
        printf("Directory created: %s\n", argv[1]);
    } 
    else 
    {
        perror("mkdir failed");
    }
}

void cmd_rmdir(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Usage: rmdir <directory>\n");
        return;
    }
    
    if (rmdir_wrapper(argv[1]) == 0) 
    {
        printf("Directory removed: %s\n", argv[1]);
    } 
    else 
    {
        perror("rmdir failed");
    }
}

void cmd_rm(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Usage: rm <file>\n");
        return;
    }
    
    if (unlink_wrapper(argv[1]) == 0) 
    {
        printf("File removed: %s\n", argv[1]);
    } 
    else 
    {
        perror("rm failed");
    }
}

void cmd_touch(int argc, char **argv) 
{
    if (argc < 2) 
    {
        printf("Usage: touch <file>\n");
        return;
    }
    
    FILE *fp = fopen(argv[1], "a");
    if (fp) 
    {
        fclose(fp);
        printf("File created/touched: %s\n", argv[1]);
    } 
    else 
    {
        perror("touch failed");
    }
}

void cmd_ls(int argc, char **argv) 
{
    const char *path = (argc > 1) ? argv[1] : ".";
    
#ifdef PLATFORM_WINDOWS
    WIN32_FIND_DATAA findData;
    char search_path[MAX_PATH_LEN];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    
    HANDLE hFind = FindFirstFileA(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        perror("ls failed");
        return;
    }
    
    do 
    {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) 
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
            {
                printf("[DIR]  %s\n", findData.cFileName);
            } 
            else 
            {
                printf("       %s\n", findData.cFileName);
            }
        }
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
#else
    DIR *dir = opendir(path);
    if (!dir) 
    {
        perror("ls failed");
        return;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
        {
            
            char full_path[MAX_PATH_LEN];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            
            if (is_directory(full_path)) 
            {
                printf("[DIR]  %s\n", entry->d_name);
            } 
            else 
            {
                printf("       %s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
#endif
}

void cmd_cd(int argc, char **argv) 
{
    const char *path;
    
    if (argc < 2) 
    {
        path = get_home_directory();
    } 
    else 
    {
        path = argv[1];
    }
    
    if (chdir_wrapper(path) == 0) 
    {
        char cwd[MAX_PATH_LEN];
        if (getcwd_wrapper(cwd, sizeof(cwd))) 
        {
            printf("Changed directory to: %s\n", cwd);
        }
    } 
    else 
    {
        perror("cd failed");
    }
}

void cmd_pwd(int argc, char **argv) 
{
    char cwd[MAX_PATH_LEN];
    if (getcwd_wrapper(cwd, sizeof(cwd))) 
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("pwd failed");
    }
}

void cmd_cp(int argc, char **argv) 
{
    if (argc < 3) 
    {
        printf("Usage: cp <source> <destination>\n");
        return;
    }
    
    FILE *src = fopen(argv[1], "rb");
    if (!src) 
    {
        perror("Cannot open source file");
        return;
    }
    
    FILE *dst = fopen(argv[2], "wb");
    if (!dst) 
    {
        perror("Cannot create destination file");
        fclose(src);
        return;
    }
    
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) 
    {
        fwrite(buffer, 1, bytes, dst);
    }
    
    fclose(src);
    fclose(dst);
    printf("Copied %s to %s\n", argv[1], argv[2]);
}

void cmd_mv(int argc, char **argv) {
    if (argc < 3) 
    {
        printf("Usage: mv <source> <destination>\n");
        return;
    }
    
    if (rename(argv[1], argv[2]) == 0) 
    {
        printf("Moved %s to %s\n", argv[1], argv[2]);
    } 
    else 
    {
        perror("mv failed");
    }
}

static void print_tree_recursive(const char *path, int depth) 
{
    for (int i = 0; i < depth; i++) 
    {
        printf("  ");
    }
    
#ifdef PLATFORM_WINDOWS
    WIN32_FIND_DATAA findData;
    char search_path[MAX_PATH_LEN];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    
    HANDLE hFind = FindFirstFileA(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) return;
    
    do 
    {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) 
        {
            
            for (int i = 0; i < depth; i++) printf("  ");
            printf("|-- %s\n", findData.cFileName);
            
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
            {
                char subpath[MAX_PATH_LEN];
                snprintf(subpath, sizeof(subpath), "%s\\%s", path, findData.cFileName);
                print_tree_recursive(subpath, depth + 1);
            }
        }
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
#else
    DIR *dir = opendir(path);
    if (!dir) return;
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
        {
            
            for (int i = 0; i < depth; i++) printf("  ");
            printf("|-- %s\n", entry->d_name);
            
            char subpath[MAX_PATH_LEN];
            snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
            
            if (is_directory(subpath)) 
            {
                print_tree_recursive(subpath, depth + 1);
            }
        }
    }
    closedir(dir);
#endif
}

void cmd_tree(int argc, char **argv) 
{
    const char *path = (argc > 1) ? argv[1] : ".";
    printf("%s\n", path);
    print_tree_recursive(path, 0);
}