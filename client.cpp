#include <iostream>
#include <WinSock2.h>

SOCKET Connection;

void chatHandler() {
    char msg[256];
    while (true) {
        recv(Connection, msg, sizeof(msg), NULL);
        std::cout << msg << std::endl;
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

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR *) &addr, sizeof(addr)) != 0) {
        std::cout << "Couldn't connect" << std::endl;
        system("pause");
        exit(1);
    }
    std::cout << "Connected" << std::endl;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) chatHandler, NULL, NULL, NULL);
    char message[256];
    while (true) {
        std::cin.getline(message, sizeof(message));
        send(Connection, message, sizeof(message), NULL);
    }

    return 0;
}
