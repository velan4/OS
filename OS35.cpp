#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100  // Total blocks in the system
#define MAX_FILES 10    // Maximum number of files

// File structure
typedef struct {
    int id;             // File ID
    int indexBlock;     // Index block storing block pointers
    int blockCount;     // Number of blocks allocated
    int *blocks;        // Pointer to dynamically allocated block array
} File;

// File System
typedef struct {
    File files[MAX_FILES];
    int fileCount;
    int freeBlocks[MAX_BLOCKS]; // 1 = Free, 0 = Allocated
} FileSystem;

// Initialize File System
void initializeFileSystem(FileSystem *fs) {
    fs->fileCount = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        fs->freeBlocks[i] = 1;  // Mark all blocks as free
    }
}

// Allocate a free block
int allocateBlock(FileSystem *fs) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (fs->freeBlocks[i]) {
            fs->freeBlocks[i] = 0;
            return i;
        }
    }
    return -1;  // No free blocks available
}

// Create a new file with indexed allocation
void createFile(FileSystem *fs, int id, int size) {
    if (fs->fileCount >= MAX_FILES) {
        printf("?? Maximum file limit reached!\n");
        return;
    }

    int indexBlock = allocateBlock(fs);
    if (indexBlock == -1) {
        printf("?? No free blocks available for the index block!\n");
        return;
    }

    File *file = &fs->files[fs->fileCount];
    file->id = id;
    file->indexBlock = indexBlock;
    file->blockCount = size;
    file->blocks = (int *)malloc(size * sizeof(int));

    printf("? File %d created with Index Block %d\n", id, indexBlock);

    // Allocate blocks for the file
    for (int i = 0; i < size; i++) {
        int block = allocateBlock(fs);
        if (block == -1) {
            printf("?? Not enough free blocks! Deallocating...\n");
            free(file->blocks);
            return;
        }
        file->blocks[i] = block;
    }

    fs->fileCount++;
}

// Display the file system
void displayFileSystem(FileSystem *fs) {
    printf("\n?? File System Structure:\n");
    printf("File ID | Index Block | Data Blocks\n");
    printf("-----------------------------------\n");

    for (int i = 0; i < fs->fileCount; i++) {
        printf("%7d | %11d | ", fs->files[i].id, fs->files[i].indexBlock);
        for (int j = 0; j < fs->files[i].blockCount; j++) {
            printf("%d ", fs->files[i].blocks[j]);
        }
        printf("\n");
    }
}

// Search for a file
void searchFile(FileSystem *fs, int id) {
    for (int i = 0; i < fs->fileCount; i++) {
        if (fs->files[i].id == id) {
            printf("?? File Found! ID=%d, Index Block=%d, Data Blocks: ", id, fs->files[i].indexBlock);
            for (int j = 0; j < fs->files[i].blockCount; j++) {
                printf("%d ", fs->files[i].blocks[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("?? File with ID=%d not found!\n", id);
}

// Free allocated memory on exit
void freeMemory(FileSystem *fs) {
    for (int i = 0; i < fs->fileCount; i++) {
        free(fs->files[i].blocks);
    }
}

int main() {
    FileSystem fs;
    initializeFileSystem(&fs);

    int choice, id, size;

    while (1) {
        printf("\n1?? Create File\n2?? Display File System\n3?? Search File\n4?? Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter File ID: ");
                scanf("%d", &id);
                printf("Enter File Size (blocks): ");
                scanf("%d", &size);
                createFile(&fs, id, size);
                break;

            case 2:
                displayFileSystem(&fs);
                break;

            case 3:
                printf("Enter File ID to search: ");
                scanf("%d", &id);
                searchFile(&fs);
                break;

            case 4:
                printf("?? Exiting...\n");
                freeMemory(&fs);
                exit(0);

            default:
                printf("?? Invalid choice! Try again.\n");
        }
    }

    return 0;
}
