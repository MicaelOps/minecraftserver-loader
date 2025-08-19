//
// Created by Micael Cossa on 21/07/2025.
//

#ifndef MINECRAFTSERVER_PACKET_BUF_H
#define MINECRAFTSERVER_PACKET_BUF_H


#include <string>
#include <vector>

class PacketBuffer {

public:

    virtual char* getBuffer();

    virtual int getSize();

    virtual int readVarInt();

    virtual void writeVarIntAttheBack(const int& value);

    virtual void writeVarInt(const int& value);

    virtual void writeByte(const char& byte);

    virtual void writeShort(const unsigned short& value);

    virtual void writeString(const std::string& value);

 };

class ArrayPacketBuffer : public virtual PacketBuffer {

private:
    char* buffer;
    int size, position = 0;

public:

    explicit ArrayPacketBuffer(char* buffer, int size) : buffer(buffer) , size(size) {}
    void reserve(size_t length);
    char* getBuffer() override;
    int getSize() override;
    int readVarInt() override;
};

class VectorBuffer : public virtual PacketBuffer {

private:
    std::vector<char> buffer;

public:
    char* getBuffer() override;
    int getSize() override;
    void writeVarIntAttheBack(const int& value) override;
    void writeVarInt(const int& value) override;
    void writeString(const std::string& value)override;
};



#endif //MINECRAFTSERVER_PACKET_BUF_H
