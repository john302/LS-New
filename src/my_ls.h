#ifndef MY_LS_H_
#define MY_LS_H_

/* Emacs style mode select: -*- linux-c++ -*- */
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH_MAX 4096 /* # chars in a path name including nul */

/**
 * @brief Macro for making a system call using the syscall instruction.
 *
 * This macro allows you to make a system call using the syscall instruction in assembly.
 * It takes four arguments: the system call number (a), the first argument (D), the second argument (S),
 * and the third argument (d). The macro expands to an assembly instruction that performs the system call.
 *
 * @param a The system call number.
 * @param D The first argument.
 * @param S The second argument.
 * @param d The third argument.
 */

void list_files(const char *path) {

    struct dirent *entry;
    struct stat file_stat;
    char full_path[PATH_MAX];
    char buf[80];
    struct tm ts;

    /**
     * Opens a directory specified by the given path.
     *
     * @param path The path of the directory to be opened.
     * @return A pointer to the opened directory on success, or NULL on failure.
     */
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0) {
            continue;
        }

        /**
         * Constructs the full path by concatenating the given path and the name of the directory entry.
         *
         * @param full_path The buffer to store the full path.
         * @param path The base path.
         * @param entry The directory entry.
         */
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) < 0) {
            perror("stat");
            continue;
        }

        struct passwd *user_info = getpwuid(file_stat.st_uid);
        /**
         * Retrieves the group information for a given group ID.
         *
         * This function uses the `getgrgid` function from the C library to retrieve the group information
         * for the specified group ID. The group information includes details such as the group name, group
         * ID, and other attributes associated with the group.
         *
         * @param file_stat The `struct stat` object containing the file or directory information.
         * @return A pointer to a `struct group` object representing the group information, or NULL if the
         *         group information could not be retrieved.
         */
        struct group *group_info = getgrgid(file_stat.st_gid);

        printf("%s", S_ISDIR(file_stat.st_mode) ? "d" : "-");    // ,,,,,,,,,,,,,,,,,,,,,,,,,
        printf("%s", (file_stat.st_mode & S_IRUSR) ? "r" : "-"); // .........................
        printf("%s", (file_stat.st_mode & S_IWUSR) ? "w" : "-"); //  .......................
        printf("%s", (file_stat.st_mode & S_IXUSR) ? "x" : "-"); //   .....................
        printf("%s", (file_stat.st_mode & S_IRGRP) ? "r" : "-"); //    ...................
        printf("%s", (file_stat.st_mode & S_IWGRP) ? "w" : "-"); //     .................
        printf("%s", (file_stat.st_mode & S_IXGRP) ? "x" : "-"); //      ...............
        printf("%s", (file_stat.st_mode & S_IROTH) ? "r" : "-"); //       '''''''''''''
        printf("%s", (file_stat.st_mode & S_IWOTH) ? "w" : "-"); //        ...........
        /**
         * Prints the permission status of a file.
         * If the file is executable by others, it prints "x.".
         * Otherwise, it prints "-.".
         *
         * @param file_stat The struct containing the file's status information.
         */
        printf(" %-4s", (file_stat.st_mode & S_IXOTH) ? "x." : "-.");

        printf(" %-4ld", file_stat.st_nlink);
        printf(" %s", user_info->pw_name); // Removed extra space
        printf(" %s", group_info->gr_name); // Removed extra space

        if (file_stat.st_size > 1000000) {
    		  long file_size_bytes = file_stat.st_size;
    		  double file_size_mb = (double)file_size_bytes / (1024.0 * 1024.0);
    		printf(" %-5.2fMB \t", round(file_size_mb)); // Removed extra space
        } else if (file_stat.st_size > 1000) {
    	    long file_size_bytes = file_stat.st_size;
    	    double file_size_kb = (double)file_size_bytes / 1024.0;
    		printf(" %-5.2fKB \t", round(file_size_kb)); // Removed extra space
        } else {
    	    printf(" %-6ld\t", file_stat.st_size);
        }

        ts = *localtime(&file_stat.st_mtime); // Convert the epoch time to local time format.
        strftime(buf, sizeof(buf), "%m-%d %H:%M:%S", &ts); // Set a nice strftime format string.
        printf("%s \t", buf); // Print the file date easily.
        printf(" %s\n", entry->d_name); // Print the filename.
    }

    /**
     * Closes the directory stream.
     *
     * This function closes the directory stream associated with the specified directory pointer.
     *
     * @param dir A pointer to the directory stream to be closed.
     *
     * @return 0 on success, -1 on failure.
     */
    closedir(dir);
}

#endif
