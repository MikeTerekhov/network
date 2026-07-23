#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

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

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    char buffer[1024] = {0};
    ssize_t n = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        cout << "Message from client: " << buffer << endl;
    } else if (n == 0) {
        cout << "0 bytes sent" << endl;
    } else {
        perror("recv");
    }
    

    close(serverSocket);

    return 0;
}