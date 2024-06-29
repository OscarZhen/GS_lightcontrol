#include <iostream>
#include <iomanip>
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

    while (true) {
        sockaddr_in senderAddr;
        int senderAddrLen = sizeof(senderAddr);

        int numBytesReceived = recvfrom(sockfd, buffer, bufferSize - 1, 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
        if (numBytesReceived == SOCKET_ERROR) {
            std::cerr << "Failed to receive broadcast message" << std::endl;
            closesocket(sockfd);
            WSACleanup();
            return;
        }

        std::cout << "Received message from " << inet_ntoa(senderAddr.sin_addr) << ": ";

        for (int i = 0; i < numBytesReceived; i++) {
            // Print each byte in hexadecimal format with leading zeros
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(buffer[i])) << " ";
        }
        std::cout << std::dec << std::endl;  // Reset to decimal format

        break;  // Terminate the loop after receiving a message
    }

    closesocket(sockfd);
    WSACleanup();
}