//
// Created by Micael Cossa on 25/07/2025.
//
#include "packet_buf.h"
#include <iostream>

#define MAXIMUM_VARINT_BITS 5
#define COMPLETION_BIT_MASK 0x80
#define SEGMENT_BITS 0x7F

void writeVarInt(int32_t varint) {

}

int readVarInt(const char* buffer, int* value , int position) {

    int final_result = 0, shifts = 0;

    while(position <= MAXIMUM_VARINT_BITS) {

        final_result |= (buffer[position] & SEGMENT_BITS) << (shifts*7);

        if ((buffer[position] & COMPLETION_BIT_MASK) == 0) break;

        position++;
        shifts++;

    }

    *value = final_result;

    return position;
}