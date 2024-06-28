#include <iostream>
#include <string>
#include <Winsock2.h>
#include <WS2tcpip.h>


void receiveMessage(int localPort, int bufferSize) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return;
    }

    sockaddr_in recvAddr;
    memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(localPort);
    recvAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket" << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return;
    }

    char buffer[bufferSize];
    memset(buffer, 0, sizeof(buffer));

    std::cout << "Waiting for broadcast message..." << std::endl;

    int numBytesReceived = recv(sockfd, buffer, bufferSize - 1, 0);
    if (numBytesReceived == SOCKET_ERROR) {
        std::cerr << "Failed to receive broadcast message" << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return;
    }

    std::string message = buffer;

    std::cout << "Received message: " << message << std::endl;

    closesocket(sockfd);
    WSACleanup();
}