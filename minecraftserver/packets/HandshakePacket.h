//
// Created by Micael Cossa on 26/07/2025.
//

#ifndef MINECRAFTSERVER_HANDSHAKEPACKET_H
#define MINECRAFTSERVER_HANDSHAKEPACKET_H

#include <string>
#include "packet.h"
class HandshakePacket : public Packet {

private:
    int protocolVersion;
    std::string serverAddress;
    unsigned short port;
    int state;

public:

    void readFromBuffer(const char* buffer , int bytePosition) override;

    void handlePacket(QUEUED_CONNECTION_CONTEXT* connectionContext) override;

    void writeToBuffer(const char *buffer) override;

    HandshakePacket() {
        packetType = SERVER_PACKET;
        protocolVersion =-1;
        port = -1;
        state = -1;
    }
};


#endif //MINECRAFTSERVER_HANDSHAKEPACKET_H
