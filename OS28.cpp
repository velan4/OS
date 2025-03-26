#include <stdio.h>
#include <string.h>

void grep(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[256];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, pattern)) {
                printf("%s", line);
            }
        }
        fclose(file);
    } else {
        perror("File opening failed");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }
    grep(argv[1], argv[2]);
    return 0;
}