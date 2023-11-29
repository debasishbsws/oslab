#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int socket_fd;
    struct sockaddr_in server_addr;
    
    // Create socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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
    
    printf("Client running...\n");
    
    // Send country name to server
    char country_name[] = "India"; // Replace with the country name
    sendto(socket_fd, country_name, strlen(country_name), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Sent country name to server: %s\n", country_name);
    
    // Receive capital name from server
    char capital_name[50];
    int addrlen = sizeof(server_addr);
    recvfrom(socket_fd, capital_name, sizeof(capital_name), 0, (struct sockaddr *)&server_addr, (socklen_t*)&addrlen);
    printf("Received capital name from server: %s\n", capital_name);
    
    close(socket_fd);
    
    return 0;
}

