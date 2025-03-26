#include <stdio.h>
#include <stdlib.h>

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) fclose(file);
}

void writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "a");
    if (file) {
        fputs(content, file);
        fclose(file);
    }
}

void readFile(const char *filename) {
    char buffer[256];
    FILE *file = fopen(filename, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    }
}

void deleteFile(const char *filename) {
    remove(filename);
}

int main() {
    const char *filename = "example.txt";
    createFile(filename);
    writeFile(filename, "Hello, World!\n");
    readFile(filename);
    deleteFile(filename);
    return 0;
}