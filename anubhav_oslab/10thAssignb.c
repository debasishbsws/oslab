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
    
    printf("Client connected.\n");
    
    // Receive country name from client
    char country_name[50];
    recv(new_socket, country_name, sizeof(country_name), 0);
    printf("Received country name from client: %s\n", country_name);
    
    // Search for country-capital pair
    char capital_name[50] = "NOT FOUND";
    for (int i = 0; i < sizeof(countryCapitalPairs) / sizeof(countryCapitalPairs[0]); i++) {
        if (strcmp(countryCapitalPairs[i].country, country_name) == 0) {
            strcpy(capital_name, countryCapitalPairs[i].capital);
            break;
        }
    }
    
    // Reply capital name back to client
    send(new_socket, capital_name, strlen(capital_name), 0);
    printf("Replied capital name to client: %s\n", capital_name);
    
    close(new_socket);
    close(server_socket);
    
    return 0;
}

