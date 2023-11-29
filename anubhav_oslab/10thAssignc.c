#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    char username[50];
    char password[50];
} UserCredentials;

UserCredentials validUsers[] = {
    {"alice", "12345"},
    {"bob", "qwerty"},
    // Add more valid user credentials as needed
};

int verifyCredentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(validUsers) / sizeof(validUsers[0]); i++) {
        if (strcmp(validUsers[i].username, username) == 0) {
            if (strcmp(validUsers[i].password, password) == 0) {
                return 1; // Success
            } else {
                return 0; // Invalid password
            }
        }
    }
    return -1; // Invalid user
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(server_addr);
    
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }
    
    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return 1;
    }
    
    // Listen
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        return 1;
    }
    
    printf("Server listening on port %d...\n", PORT);
    
    while (1) {
        // Accept incoming connection
        if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) == -1) {
            perror("accept");
            return 1;
        }
        
        printf("Client connected.\n");
        
        // Receive username from client
        char username[50];
        recv(new_socket, username, sizeof(username), 0);
        printf("Received username from client: %s\n", username);
        
        // Receive password from client
        char password[50];
        recv(new_socket, password, sizeof(password), 0);
        printf("Received password from client: %s\n", password);
        
        // Verify user credentials
        int verification_result = verifyCredentials(username, password);
        char response[20];
        if (verification_result == 1) {
            strcpy(response, "Success");
        } else if (verification_result == 0) {
            strcpy(response, "Invalid password");
        } else {
            strcpy(response, "Invalid user");
        }
        
        // Reply verification result back to client
        send(new_socket, response, strlen(response), 0);
        printf("Replied verification result to client: %s\n", response);
        
        close(new_socket);
    }
    
    close(server_socket);
    
    return 0;
}

