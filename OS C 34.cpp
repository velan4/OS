#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

typedef struct {
    int id;
    char data[256];
} Record;

Record file[MAX_RECORDS];
int recordCount = 0;

void addRecord(int id, const char *data) {
    if (recordCount < MAX_RECORDS) {
        file[recordCount].id = id;
        snprintf(file[recordCount].data, sizeof(file[recordCount].data), "%s", data);
        recordCount++;
    } else {
        printf("File is full. Cannot add more records.\n");
    }
}

void readRecords() {
    for (int i = 0; i < recordCount; i++) {
        printf("Record ID: %d, Data: %s\n", file[i].id, file[i].data);
    }
}

int main() {
    addRecord(1, "First record");
    addRecord(2, "Second record");
    addRecord(3, "Third record");

    printf("Reading all records:\n");
    readRecords();

    return 0;
}
