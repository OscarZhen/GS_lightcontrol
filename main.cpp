#include "control_functions.h"
#include <windows.h>

int main() {
    const std::string targetIP = "169.254.255.255";
    // const std::string targetIP = "169.254.169.94";
    int targetPort = 4628;
    int localPort = 8200;
    int bufferSize = 1500;

    // send_broadcast(targetPort);

    while (true) {
        send_startframe(targetIP, targetPort);

        send_controlnum(targetIP, targetPort, 4);

        // send_controllight(targetIP, targetPort);
        send_randomlight22(targetIP, targetPort, 4);

        send_endframe(targetIP, targetPort);
        
        receiveMessage(localPort, bufferSize);
        Sleep(1000);
    }


    // send_startframe(targetIP, targetPort);

    // send_controlnum(targetIP, targetPort, 1);

    // // send_controllight(targetIP, targetPort);
    // send_randomlight22(targetIP, targetPort, 1);

    // send_endframe(targetIP, targetPort);
    // receiveMessage(localPort, bufferSize);

    return 0;
}