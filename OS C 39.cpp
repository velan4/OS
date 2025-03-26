#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void csan(int arr[], int n, int head, int direction) {
    int seek_sequence[MAX], distance, seek_count = 0, cur_track;
    int i, j;

    // Sort the request array
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Find the index of the head
    int index = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] >= head) {
            index = i;
            break;
        }
    }

    // Move towards the end
    for (i = index; i < n; i++) {
        cur_track = arr[i];
        seek_count += abs(cur_track - head);
        head = cur_track;
        seek_sequence[i] = cur_track;
    }

    // Jump to the beginning
    if (direction == 1) {
        seek_count += abs(head - MAX);
        head = 0;
    }

    // Move towards the beginning
    for (i = 0; i < index; i++) {
        cur_track = arr[i];
        seek_count += abs(cur_track - head);
        head = cur_track;
        seek_sequence[n + i] = cur_track;
    }

    // Print the results
    printf("Seek Sequence is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Count is: %d\n", seek_count);
}

int main() {
    int arr[] = { 176, 79, 34, 60, 92, 11, 41, 114 };
    int head = 50;
    int direction = 1; // 1 for right, 0 for left
    int n = sizeof(arr) / sizeof(arr[0]);

    csan(arr, n, head, direction);
    return 0;
}
