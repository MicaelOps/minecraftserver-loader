//
// Created by Micael Cossa on 26/07/2025.
//

#ifndef MINECRAFTSERVER_SERVER_HANDLER_H
#define MINECRAFTSERVER_SERVER_HANDLER_H


#include "server_connection.h"
#include "packets/packet.h"

void setupPacketFactory();
void invokePacket(int packetId , char* buffer, int currBytePos, QUEUED_CONNECTION_CONTEXT* connectionContext);
void sendPacket(Packet* packet, QUEUED_CONNECTION_CONTEXT* connectionContext);

#endif //MINECRAFTSERVER_SERVER_HANDLER_H