#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    
    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }
    
    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }
    
    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        return 1;
    }
    
    printf("Connected to server...\n");
    
    // Send username to server
    char username[] = "Anubhavk"; // Replace with the username
    send(client_socket, username, strlen(username), 0);
    printf("Sent username to server: %s\n", username);
    
    // Send password to server
    char password[] = "A@1234"; // Replace with the password
    send(client_socket, password, strlen(password), 0);
    printf("Sent password to server: %s\n", password);
    
    // Receive verification result from server
    char verification_result[20];
    recv(client_socket, verification_result, sizeof(verification_result), 0);
    printf("Received verification result from server: %s\n", verification_result);
    
    close(client_socket);
    
    return 0;
}

