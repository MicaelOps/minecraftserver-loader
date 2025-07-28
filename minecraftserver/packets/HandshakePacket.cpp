//
// Created by Micael Cossa on 26/07/2025.
//

#include "HandshakePacket.h"
#include "../server_utils.h"
#include <iostream>

#define PROTOCOL_VERSION_1_8 47

void HandshakePacket::readFromBuffer(const char* buffer, int bytePosition) {

    bytePosition = readVarInt(buffer, &protocolVersion, bytePosition);

}

void HandshakePacket::writeToBuffer(const char* buffer) {
    std::cout << "Unsupported call to writeToBuffer";

}

void HandshakePacket::handlePacket(QUEUED_CONNECTION_CONTEXT* connectionContext) {

    printInfo("Protocol version " , protocolVersion);

    if(protocolVersion != PROTOCOL_VERSION_1_8) {
        printInfo("A non 1.8.x connection has tried to initiate a handshake..");
        closeConnection(connectionContext);
        return;
    }

    sendPacket();

}

