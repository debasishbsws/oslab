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
    
    // Send IP address to server
    char ip_address[] = "192.168.1.1"; // Replace with your IP address
    send(client_socket, ip_address, strlen(ip_address), 0);
    printf("Sent IP address to server: %s\n", ip_address);
    
    // Receive network id from server
    char network_id[20];
    recv(client_socket, network_id, sizeof(network_id), 0);
    printf("Received network ID from server: %s\n", network_id);
    
    close(client_socket);
    
    return 0;
}

