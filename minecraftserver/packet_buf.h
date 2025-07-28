//
// Created by Micael Cossa on 21/07/2025.
//

#ifndef MINECRAFTSERVER_PACKET_BUF_H
#define MINECRAFTSERVER_PACKET_BUF_H

#include <stdint.h>

void writeVarInt(int32_t varint);

int readVarInt(const char* buffer, int* value, int position);


#endif //MINECRAFTSERVER_PACKET_BUF_H
