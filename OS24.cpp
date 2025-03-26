#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) return 1;

    write(fd, "Hello, UNIX!\n", 14);
    close(fd);

    fd = open("example.txt", O_RDONLY);
    char buffer[20];
    read(fd, buffer, 14);
    buffer[14] = '\0'; // Null-terminate the string
    printf("%s", buffer);
    close(fd);

    unlink("example.txt"); // Delete the file
    return 0;
}