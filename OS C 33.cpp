#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3
#define PAGE_SIZE 10

void optimalPageReplacement(int pages[], int n) {
    int frame[FRAME_SIZE];
    int pageFaults = 0;
    int i, j, k, pos, max, flag;

    for (i = 0; i < FRAME_SIZE; i++)
        frame[i] = -1;

    for (i = 0; i < n; i++) {
        flag = 0;
        for (j = 0; j < FRAME_SIZE; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            for (j = 0; j < FRAME_SIZE; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    pageFaults++;
                    flag = 1;
                    break;
                }
            }
        }

        if (flag == 0) {
            max = -1;
            for (j = 0; j < FRAME_SIZE; j++) {
                int found = 0;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0) {
                    pos = j;
                    break;
                }
                if (found == 1 && k > max) {
                    max = k;
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            pageFaults++;
        }

        printf("Frame state after accessing page %d: ", pages[i]);
        for (j = 0; j < FRAME_SIZE; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    optimalPageReplacement(pages, n);
    return 0;
}
