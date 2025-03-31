/**
 * 
 * FileStats - CS50x Final Project, a simple directory stats program
 * Author: Callum Telfer
 * edX: callum_t07
 * Github: VoidemLIVE
 * Date created: 31st March 2025
 * 
 * CS50 Library used in cs50.c and cs50.h
 */

#include "cs50.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/**
 * Function to print the startup information
 */
void printStartup(void);

int main(void) 
{
    // Sets the console to UTF8 so i can print the custom ASCII art
    system("chcp 65001 > NUL");
    printStartup();

    // Prompts the user for the dir path and checks if its valid
    char *path = get_string("Enter the directory path: ");
    if (path == NULL) 
    {
        fprintf(stderr, "Failed to get path.\n");
        return 1;
    }

    // Opens the directory and checks if it was successful
    DIR *dir = opendir(path);
    if (dir == NULL) 
    {
        fprintf(stderr, "Failed to open directory: %s\n", path);
        free(path);
        return 1;
    }

    // defining all the variables that will be used for stats
    struct dirent *entry;
    struct stat fileStat;
    char fullPath[1024];
    int fileCount = 0;
    int dirCount = 0;
    long long totalSize = 0;
    int totalFiles = 0;
    int totalDirs = 0;
    int totalHiddenFiles = 0;
    int totalHiddenDirs = 0;
    long long totalHiddenFilesSize = 0;
    long long totalHiddenDirsSize = 0;
    int totalHiddenFilesCount = 0;
    int totalHiddenDirsCount = 0;

    // Prompts the user for if hidden files should be shown
    char *hiddenFilesStr;
    do 
    {
        hiddenFilesStr = get_string("Show hidden files? (y/n): ");
    } while (hiddenFilesStr == NULL || (strcmp(hiddenFilesStr, "y") != 0 && strcmp(hiddenFilesStr, "n") != 0));

    // Converts input into int for logic handling
    int showHiddenFiles;
    if (strcmp(hiddenFilesStr, "y") == 0) 
    {
        showHiddenFiles = 1;
    } else 
    {
        showHiddenFiles = 0;
    }
    // frees the hiddenfilesstr as its not needed anymore
    free(hiddenFilesStr);

    printf("Scanning directory: %s\n", path);
    printf("--------------------------------------------------\n");

    // Starts the actual scanning of the directory
    while ((entry = readdir(dir)) != NULL)
    {
        // skips the current and parent directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        // makes the full path to the files
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name); // Helped by Copilot

        // gets status info
        if (stat(fullPath, &fileStat) == -1)
        {
            fprintf(stderr, "Failed to get file status: %s\n", fullPath);
            continue;
        }

        // check if the file is hidden, some start with a dot (only show if user chose to)
        int isHidden = (entry->d_name[0] == '.');
        if (isHidden && !showHiddenFiles)
        {
            continue;
        }

        // Checks the directories
        if (S_ISDIR(fileStat.st_mode))
        {
            dirCount++;
            totalDirs++;

            if (isHidden)
            {
                totalHiddenDirs++;
                totalHiddenDirsSize += fileStat.st_size;
            }

            // Displays the directory info
            printf("%-50s [DIR]", entry->d_name); // Helped by Copilot
            if (isHidden)
            {
                printf(" [HIDDEN]");
            }
            printf("\n");
        }
        // Checks the files
        else if (S_ISREG(fileStat.st_mode))
        {
            fileCount++;
            totalFiles++;
            totalSize += fileStat.st_size;

            if (isHidden)
            {
                totalHiddenFiles++;
                totalHiddenFilesSize += fileStat.st_size;
            }

            // Displays the file info
            printf("%-50s %8lld bytes", entry->d_name, (long long)fileStat.st_size); // Helped by Copilot
            if (isHidden)
            {
                printf(" [HIDDEN]");
            }
            printf("\n");
        }
        // some file types may not be processed, it's a litle tempremental
    }

    // close the directory and free the path variable as not used anymore
    closedir(dir);
    free(path);

    // Summary of stats display
    printf("--------------------------------------------------\n");
    printf("Total files: %d\n", totalFiles);
    printf("Total directories: %d\n", totalDirs);
    if (totalSize > 1000)
    {
        printf("Total size: %.2f MB\n", (double)totalSize / (1024 * 1024));
    }
    else if (totalSize > 1)
    {
        printf("Total size: %.2f KB\n", (double)totalSize / 1024);
    }
    else
    {
        printf("Total size: %lld bytes\n", totalSize);
    }
    printf("Total hidden files: %d\n", totalHiddenFiles);
    printf("Total hidden directories: %d\n", totalHiddenDirs);
    printf("Total hidden files size: %lld bytes\n", totalHiddenFilesSize);
    printf("Total hidden directories size: %lld bytes\n", totalHiddenDirsSize);
    printf("---------------------------------------------------\n");
}

void printStartup(void)
{
    // Gets object for date & time
    time_t t;
    time(&t);

    printf("\n");
    printf("███████╗██╗██╗     ███████╗███████╗████████╗ █████╗ ████████╗███████╗\n");
    printf("██╔════╝██║██║     ██╔════╝██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██╔════╝\n");
    printf("█████╗  ██║██║     █████╗  ███████╗   ██║   ███████║   ██║   ███████╗\n");
    printf("██╔══╝  ██║██║     ██╔══╝  ╚════██║   ██║   ██╔══██║   ██║   ╚════██║\n");
    printf("██║     ██║███████╗███████╗███████║   ██║   ██║  ██║   ██║   ███████║\n");
    printf("╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝\n");
    printf("\n");
    printf("---------------------------------------------------------------------\n");
    printf("Project for CS50 - FileStats\n");
    printf("Author: Callum Telfer\n");
    printf("edX: callum_t07\n");
    printf("Github: VoidemLIVE\n");
    printf("Location: London, United Kingdom\n");
    printf("Date: %s\n", ctime(&t));
    printf("---------------------------------------------------------------------\n");
    printf("\n");
}






                                                                     