#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Using fcntl to open a file
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) return 1;

    // Using lseek to move the file pointer
    lseek(fd, 0, SEEK_SET);

    // Using stat to get file information
    struct stat fileStat;
    stat("example.txt", &fileStat);

    // Using opendir to open a directory
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *entry;
        // Using readdir to read directory entries
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }

    // Close the file descriptor
    close(fd);
    return 0;
}