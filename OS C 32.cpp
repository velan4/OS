#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3
#define PAGE_SIZE 10

int frames[FRAME_SIZE];
int pageFaults = 0;

void initializeFrames() {
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;
    }
}

int isPageInFrames(int page) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

void replacePage(int page) {
    int lruIndex = 0;
    for (int i = 1; i < FRAME_SIZE; i++) {
        if (frames[i] == -1) {
            lruIndex = i;
            break;
        }
        if (frames[lruIndex] < frames[i]) {
            lruIndex = i;
        }
    }
    frames[lruIndex] = page;
}

void simulateLRU(int pages[], int n) {
    initializeFrames();
    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(pages[i])) {
            replacePage(pages[i]);
            pageFaults++;
        }
    }
}

int main() {
    int pages[] = {0, 1, 2, 0, 3, 0, 4, 3, 2, 1};
    int n = sizeof(pages) / sizeof(pages[0]);

    simulateLRU(pages, n);
    printf("Total Page Faults: %d\n", pageFaults);
    return 0;
}
