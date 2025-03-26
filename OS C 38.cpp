#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void scan(int arr[], int n, int head, int direction) {
    int seek_sequence[MAX], index = 0, distance, total_head_movement = 0;
    int i;

    sort(arr, n);

    int start = 0, end = n - 1;

    if (direction == 0) { // Left
        for (i = end; i >= 0; i--) {
            if (arr[i] < head) {
                start = i;
                break;
            }
        }
        for (i = start; i >= 0; i--) {
            seek_sequence[index++] = arr[i];
            distance = abs(head - arr[i]);
            total_head_movement += distance;
            head = arr[i];
        }
        total_head_movement += abs(head - 0);
        head = 0;
        for (i = 0; i <= end; i++) {
            seek_sequence[index++] = arr[i];
            distance = abs(head - arr[i]);
            total_head_movement += distance;
            head = arr[i];
        }
    } else { // Right
        for (i = 0; i < n; i++) {
            if (arr[i] > head) {
                start = i;
                break;
            }
        }
        for (i = start; i < n; i++) {
            seek_sequence[index++] = arr[i];
            distance = abs(head - arr[i]);
            total_head_movement += distance;
            head = arr[i];
        }
        total_head_movement += abs(head - MAX);
        head = MAX;
        for (i = end; i >= start; i--) {
            seek_sequence[index++] = arr[i];
            distance = abs(head - arr[i]);
            total_head_movement += distance;
            head = arr[i];
        }
    }

    printf("Seek Sequence: ");
    for (i = 0; i < index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main() {
    int arr[MAX], n, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    scan(arr, n, head, direction);

    return 0;
}
