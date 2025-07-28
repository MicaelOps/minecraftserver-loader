//
// Created by Micael Cossa on 26/07/2025.
//

#ifndef MINECRAFTSERVER_PACKET_H
#define MINECRAFTSERVER_PACKET_H


#include "../packet_buf.h"
#include "../server_handler.h"


enum PacketType {
    WORLD_PACKET, SERVER_PACKET
};

class Packet {

public:

    PacketType packetType = SERVER_PACKET;

    virtual ~Packet() = default;

    virtual void readFromBuffer(const char *buffer, int bytePosition);

    virtual void writeToBuffer(const char *buffer);

    virtual void handlePacket(QUEUED_CONNECTION_CONTEXT* connectionContext);
};


#endif //MINECRAFTSERVER_PACKET_H
