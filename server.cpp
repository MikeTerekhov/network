#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread> 

using namespace std;

void handle_client(int client_socket)
{
    char buffer[1024];
    std::cout << "[Server] Thread spawned for socket FD: " << client_socket << "\n";

    while (true) 
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received <= 0) {
            std::cout << "[Server] Client disconnected (FD: " << client_socket << ")\n";
            break;
        }

        std::cout << "[Client " << client_socket << "]: " << buffer << "\n";

        // Echo data back to the client
        send(client_socket, buffer, bytes_received, 0);
    }


    close(client_socket);
}

int main() 
{
    std::cout << "Server is running ..." << std::endl;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (::bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        perror("listen");
        return 1;
    }

    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        std::thread client_thread(handle_client, clientSocket);
        client_thread.detach();
    }

    close(serverSocket);

    return 0;
}