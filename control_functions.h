#ifndef FUNCTONS_H
#define FUNCTONS_H
#include <string>

unsigned char Check_sum(unsigned char* r_d, unsigned short Len);
unsigned char find_crc(unsigned char out_crc);

void send_broadcast(int targetPort);

void send_startframe(const std::string& targetIP, int targetPort);

void send_controlnum(const std::string& targetIP, int targetPort, int pixelNum);

void send_controllight(const std::string& targetIP, int targetPort);

void send_endframe(const std::string& targetIP, int targetPort);

void receiveMessage(int localPort, int bufferSize);

void send_randomlight22(const std::string& targetIP, int targetPort, int pixelNum);

#endif