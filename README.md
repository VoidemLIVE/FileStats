# FileStats
#### Video Demo: https://youtu.be/YlS_C5c2PMo
#### Description:

FileStats is a simple command-line program that allows the user to select a directory of their choice, and then iterates through that directory getting the statistics of the contents inside of it. As the program starts, the user is prompted to enter the directory they would like to get the stats of, then they are prompted for whether hidden files should be included in the statistics or not. The program will then output all files and directories inside of the chosen directory and their size, it will then provide a summary at the end stating stats like the total size of the directory.

## <strong>Technical Overview</strong>

### `printStartup()`
The printStartup function starts of by creating an object for the current date and time, which uses the time.h header. The function then outputs ASCII art of "FileStats" and information about me required by CS50, including the formatted datetime object that was created earlier in the function.

### `main()`

The main function starts off by calling the `printStartup` function and then moves on to ask the user for the directory they'd like to use. The program does this by storing a string of the path by using a pointer to a char. Then the program checks whether the directory exists and it can be opened, once again using a pointer to the directory.

Next, the program initialises all the variables that will be used in the calculations and outputting of statistics, this includes defining two structs `*entry` and `fileStat`.

The program then asks the user whether hidden files should be included in the satistics or not. The user can enter "y" or "n" and will be reprompted if they do not answer with one of the two options. 

Now the program starts calculating the statistics of the directory. It starts off by using a while loop which reads through each file and folder in the directory one by one using `readdir()` until it returns NULL. As the while loop starts, it will check whether the item found is `.`(The current directory) or `..`(The parent directory), it will skip over these if found as these should not be added to the stats. 

The program then combines two strings together with a / in the middle, these two strings are the directory path and the filename which creates `path_to_directory/file.txt`. `snprintf` was used for this which stores the result of the combined strings in the `fullPath` buffer variable, which has a max character limit of 1024. The reason that `snprintf` was used here is because it prevents buffer overflow, meaning that it will never write more characters than specified.

Next, the program checks if file information was found with the `stat(fullPath, &fileStat)` function. If the function returns `-1` it means that the operation has failed, which then returns `Failed to get file status`. Next, the code will check if the file is hidden by checking if it starts with a fullstop, for example `.hiddenfile`, and a popular hidden file that is used a lot is `.gitignore`. 

The program will then check if the current item is a directory rather than a normal file by using `S_ISDIR(fileStat.st_mode)`, this function returns 0 (false) if the item is not a directory and returns 1 (true) if the item IS a directory. If the function returns true then the code will check whether the directory is hidden and will add it to the count.

And then the code uses the `S_ISREG(fileStat.st_mode)` function to check whether the current item is a normal file. Once again, it will return 1 (true) if it is a regular file and will return 0 (false) if it's not a regular file, like a directory etc.

The program will then count up the files, the file sizes and whether the files are hidden. Then running `printf("%-50s %8lld bytes", entry->d_name, (long long)fileStat.st_size)` to output to the console the individual file name and what the size of it is (in bytes).

Next the program will close the directory and free the path pointer from the memory as they're both no longer needed. It will then print out the summary of the directory and convert the total size's bytes into the closest measurement of either Bytes, KBs, or MBs. 

## <strong>Acknowledgments</strong>

Most of this program was created purely from the knowledge that I gained from the CS50 course, specifically from weeks 1 through 5, which helped me grasp the basics of the C programming language, basic memory management and data structures. Small parts of this project used Github Copilot, and they have been referenced in the code by comments. All other parts of the project that weren't in the lectures or from Copilot came from the following websites:

- https://manual.cs50.io
- https://www.geeksforgeeks.org
- https://stackoverflow.com