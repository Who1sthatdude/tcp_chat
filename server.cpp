#include <iostream>
#include <winsock2.h>
#include <string>

SOCKET *allConnections = new SOCKET(100);
int connectionCounter = 0;

void chatHandler(int index) {
    char message[256];
    while (true) {
        recv(allConnections[index], message, sizeof(message), NULL);
        for (int i = 0; i < connectionCounter; i++) {
            if (i == index) { continue; }
            send(allConnections[i], message, sizeof(message), NULL);
        }
    }

}

int main(int argc, char *argv[]) {
    //Loading lib WSA
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) { //if lib is loaded startup will return 0
        std::cout << "Error lib is not loaded" << std::endl;
        exit(1);
    };

    //implementing info about socket address
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
    addr.sin_port = htons(3001); //port
    addr.sin_family = AF_INET;

    //listening
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR *) &addr, sizeof(addr));
    listen(sListen, SOMAXCONN);


    SOCKET connection;
    for (int i = 0; i < 100; i++) {
        int addrSize = sizeof(addr);//couldn't take reference of sizeof(addr) so had to do this
        connection = accept(sListen, (SOCKADDR *) &addr, &addrSize);
        if (connection == 0) {
            std::cout << "Client couldn't connect to server" << std::endl;
        } else {
            std::cout << "Client connected" << std::endl;
        }
        allConnections[i] = connection;
        connectionCounter++;
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)chatHandler, (LPVOID) (i), NULL, NULL);
    }
    return 0;
}
