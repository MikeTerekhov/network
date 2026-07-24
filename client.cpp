#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main()
{
   cout << "Client is running ..." << endl;

   int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

   sockaddr_in serverAddress;
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(8080);
   serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

   if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
      perror("connect");
      return 1;
   }

   string message;

   while (true) {
      cout << "Send message to server: ";
      getline(cin, message);
      const char* cstr = message.c_str();
      if (!strcmp(cstr, "quit")) {
         cout << "we are quitting" << endl;
         break;
      }
      else {
         cout << "sent message: " << message << "to server" << endl;
         if (send(clientSocket, message, strlen(message), 0) < 0) {
            perror("send");
            return 1;
         }
      }

   }

   close(clientSocket);

   return 0;
}