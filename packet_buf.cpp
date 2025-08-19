//
// Created by Micael Cossa on 25/07/2025.
//
#include "packet_buf.h"
#include <algorithm>

#define MAXIMUM_VARINT_BITS 5
#define COMPLETION_BIT_MASK 0x80
#define SEGMENT_BITS 0x7F


int ArrayPacketBuffer::readVarInt() {
    int final_result = 0, shifts = 0;
    while(position <= MAXIMUM_VARINT_BITS) {

        final_result |= (buffer[position] & SEGMENT_BITS) << (shifts*7);

        position++;

        if ((buffer[position] & COMPLETION_BIT_MASK) == 0) break;

        shifts++;

    }

    return final_result;
}

void ArrayPacketBuffer::reserve(const size_t length) {
    char* oldbuffer = buffer;
    buffer = new char[size+length];
    if (oldbuffer) {
        std::copy(oldbuffer, oldbuffer + size, buffer);  // copy old data
        delete[] oldbuffer;                               // free old memory
    }
    size +=length;
}

char *ArrayPacketBuffer::getBuffer() {
    return buffer;
}

int ArrayPacketBuffer::getSize() {
    return PacketBuffer::getSize();
}


char *VectorBuffer::getBuffer() {
    return buffer.data();
}

int VectorBuffer::getSize() {
    return buffer.size();
}

int VectorBuffer::readVarInt() {
    return PacketBuffer::readVarInt();
}

void VectorBuffer::writeVarIntAttheBack(int value) {

}

void VectorBuffer::writeString(std::string &value) {

    if(size < value.length())
        reserve(value.length());

    // Write Size
    writeVarInt(static_cast<int>(value.length()));

    // Write UTF-8 Characters
    std::for_each(value.begin(), value.end(), [this](const char& c) {
        this->writeByte(c);
    });
}

void VectorBuffer::writeVarInt(int value) {
    do {
        int transfer_bits = (value & (SEGMENT_BITS));
        value >>= 7;

        // insert completion bit
        if(value != 0) {
            transfer_bits |= COMPLETION_BIT_MASK;
        }

        buffer[position] = static_cast<char>(transfer_bits);

    } while(value != 0);
}

void PacketBuffer::writeString(const std::string &value) {
    printf("Unsupported call to PacketBuffer ");
}

void PacketBuffer::writeByte(const char &byte) {
    printf("Unsupported call to PacketBuffer ");
}

void PacketBuffer::writeShort(const unsigned short& value) {
    printf("Unsupported call to PacketBuffer ");
}

void PacketBuffer::writeVarInt(const int& value) {
    printf("Unsupported call to PacketBuffer ");
}

void PacketBuffer::writeVarIntAttheBack(const int& value) {
    printf("Unsupported call to PacketBuffer ");
}

int PacketBuffer::getSize() {
    printf("Unsupported call to PacketBuffer ");
    return 0;
}

char *PacketBuffer::getBuffer() {
    printf("Unsupported call to PacketBuffer ");
    return nullptr;
}

int PacketBuffer::readVarInt() {
    printf("Unsupported call to PacketBuffer ");
    return 0;
}
