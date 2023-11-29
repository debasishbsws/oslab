#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

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
    
    // Accept incoming connection
    if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen)) == -1) {
        perror("accept");
        return 1;
    }
    
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Client connected: %s\n", client_ip);
    
    // Receive IP address from client
    char ip_address[INET_ADDRSTRLEN];
    recv(new_socket, ip_address, sizeof(ip_address), 0);
    printf("Received IP address from client: %s\n", ip_address);
    
    // Identify network id based on IP class
    char network_id[20];
    char ip_class = ip_address[0];
    if (ip_class >= 'A' && ip_class <= 'C') {
        strcpy(network_id, "Private Network");
    } else {
        strcpy(network_id, "Public Network");
    }
    
    // Reply network id back to client
    send(new_socket, network_id, strlen(network_id), 0);
    printf("Replied network ID to client: %s\n", network_id);
    
    close(new_socket);
    close(server_socket);
    
    return 0;
}

