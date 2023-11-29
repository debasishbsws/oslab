#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    char country[50];
    char capital[50];
} CountryCapitalPair;

CountryCapitalPair countryCapitalPairs[] = {
    {"India", "New Delhi"},
    {"USA", "Washington, D.C."},
    {"Japan", "Tokyo"},
    {"Germany", "Berlin"},
    // Add more country-capital pairs as needed
};

int main() {
    int socket_fd;
    struct sockaddr_in server_addr, client_addr;
    int addrlen = sizeof(server_addr);
    
    // Create socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return 1;
    }
    
    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return 1;
    }
    
    printf("Server listening on port %d...\n", PORT);
    
    while (1) {
        // Receive country name from client
        char country_name[50];
        recvfrom(socket_fd, country_name, sizeof(country_name), 0, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);
        printf("Received country name from client: %s\n", country_name);
        
        // Search for country-capital pair
        char capital_name[50] = "NOT FOUND";
        for (int i = 0; i < sizeof(countryCapitalPairs) / sizeof(countryCapitalPairs[0]); i++) {
            if (strcmp(countryCapitalPairs[i].country, country_name) == 0) {
                strcpy(capital_name, countryCapitalPairs[i].capital);
                break;
            }
        }
        
        // Send capital name back to client
        sendto(socket_fd, capital_name, strlen(capital_name), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
        printf("Sent capital name to client: %s\n", capital_name);
    }
    
    close(socket_fd);
    
    return 0;
}

