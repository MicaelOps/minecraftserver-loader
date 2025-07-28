//
// Created by Micael Cossa on 26/07/2025.
//

#include "packet.h"
#include <iostream>

void Packet::readFromBuffer(const char* buffer, int bytePosition) {
    std::cout << "Unsupported call to readFromBuffer";
}

void Packet::writeToBuffer(const char* buffer) {
    std::cout << "Unsupported call to writeToBuffer";
}

void Packet::handlePacket(QUEUED_CONNECTION_CONTEXT* connectionContext){
    std::cout << "Unsupported call to serverHandle";
}

