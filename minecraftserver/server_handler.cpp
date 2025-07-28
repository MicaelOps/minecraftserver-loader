//
// Created by Micael Cossa on 26/07/2025.
//
#include "server_handler.h"
#include "packets/HandshakePacket.h"
#include "server_utils.h"


//constexpr std::unordered_map<int, Packet> packet_handler;
//constexpr std::unordered_set<player> players;

Packet* (*packetFactory[256])() = {nullptr};

void setupPacketFactory() {
    packetFactory[0] = [] () -> Packet* { return new HandshakePacket(); };
}

void invokePacket(int packetId , char* buffer, int currBytePos, QUEUED_CONNECTION_CONTEXT* connectionContext) {

    if(packetId > 255 || packetId < 0) {
        printInfo("invalid Packet id: ", packetId);
        return;
    }

    Packet* packet = packetFactory[packetId]();
    packet->readFromBuffer(buffer, currBytePos);
    packet->handlePacket(connectionContext);

    delete packet;
}
void sendPacket(Packet* packet, QUEUED_CONNECTION_CONTEXT* connectionContext) {


}
