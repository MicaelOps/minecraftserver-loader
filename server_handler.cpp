//
// Created by Micael Cossa on 26/07/2025.
//

#include <memory>
#include "server_handler.h"
#include "server_utils.h"
#include "server_connection.h"
#include "packets/HandshakePacket.h"




// std::unordered_map<int, Packet> packet_handler;
// std::unordered_set<player> players;

std::unique_ptr<Packet> (*packetFactory[256])() = {nullptr};

void setupPacketFactory() {
    packetFactory[0] = [] () -> std::unique_ptr<Packet> { return std::make_unique<HandshakePacket>(); };
}

void invokePacket(PacketBuffer* packetBuffer, PLAYER_CONNECTION_CONTEXT* connectionContext) {

    int packetId = packetBuffer->readVarInt();

    if(packetId > 255 || packetId < 0) {
        printInfo("invalid Packet id: ", packetId);
        return;
    }

    std::unique_ptr<Packet> packet = packetFactory[packetId]();
    packet->readFromBuffer(packetBuffer);
    packet->handlePacket(connectionContext->playerSocket);

}

/**
 * Packet format
 * - length (id + data)
 * - id
 * - data
 * @param packet
 * @param connectionContext
 */
void sendPacket(Packet* packet, SOCKET playerSocket) {

    std::unique_ptr<PacketBuffer> packetBuffer = std::make_unique<VectorBuffer>();

    packet->writeToBuffer(packetBuffer.get()); // write data + packet id
    packetBuffer->writeVarIntAttheBack(packetBuffer->getSize()); // write packet size var int as the first byte
    sendDataToConnection(packetBuffer.get(), playerSocket);


}
