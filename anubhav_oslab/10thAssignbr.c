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
    
    // Send country name to server
    char country_name[] = "India"; // Replace with the country name
    send(client_socket, country_name, strlen(country_name), 0);
    printf("Sent country name to server: %s\n", country_name);
    
    // Receive capital name from server
    char capital_name[50];
    recv(client_socket, capital_name, sizeof(capital_name), 0);
    printf("Received capital name from server: %s\n", capital_name);
    
    close(client_socket);
    
    return 0;
}

