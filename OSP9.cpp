#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

void server() {
    HANDLE hPipe;
    char buffer[1024];
    DWORD bytesRead;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_INBOUND, // Read-only for server
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create named pipe\n");
        return;
    }

    printf("Waiting for client to send a message...\n");

    // Wait for client connection
    if (ConnectNamedPipe(hPipe, NULL) == FALSE) {
        printf("Failed to connect to named pipe\n");
        CloseHandle(hPipe);
        return;
    }

    // Read message from client
    if (ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
        buffer[bytesRead] = '\0'; // Null-terminate string
        printf("Received message: %s\n", buffer);
    } else {
        printf("Failed to read from pipe\n");
    }

    // Close the pipe
    CloseHandle(hPipe);
}

void client() {
    HANDLE hPipe;
    char message[1024];
    DWORD bytesWritten;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    // Connect to the named pipe
    hPipe = CreateFile(
        PIPE_NAME,
        GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to connect to named pipe\n");
        return;
    }

    // Send message to server
    if (!WriteFile(hPipe, message, strlen(message), &bytesWritten, NULL)) {
        printf("Failed to write to pipe\n");
    } else {
        printf("Message sent successfully!\n");
    }

    // Close the pipe
    CloseHandle(hPipe);
}

int main() {
    int choice;
    printf("Choose mode:\n1. Server (Receiver)\n2. Client (Sender)\nEnter choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    if (choice == 1) {
        server();
    } else if (choice == 2) {
        client();
    } else {
        printf("Invalid option\n");
    }

    return 0;
}