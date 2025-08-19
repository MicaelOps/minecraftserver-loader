//
// Created by Micael Cossa on 07/08/2025.
//

#ifndef MINECRAFTSERVER_SERVER_CONNECTION_H
#define MINECRAFTSERVER_SERVER_CONNECTION_H


#include <winsock2.h>
#include "concurrent_unordered_set.h"
#include "packet_buf.h"

#pragma comment(lib, "Ws2_32.lib")


enum CONNECTION_CONTEXT_TYPE {
    ACCEPT, RECEIVE, SEND
};
struct IO_SERVER_CONNECTION_THREAD_PARAM {
    SOCKET listenSocket;
    HANDLE listenPort;
};


struct PLAYER_CONNECTION_CONTEXT {

    explicit PLAYER_CONNECTION_CONTEXT() = default;

    PLAYER_CONNECTION_CONTEXT(const PLAYER_CONNECTION_CONTEXT&) = delete;
    PLAYER_CONNECTION_CONTEXT& operator=(const PLAYER_CONNECTION_CONTEXT&) = delete;

    ~PLAYER_CONNECTION_CONTEXT() {
        printf("player connection deleted");
        delete[] buffer.buf; // context takes ownership of the buffer
    }

    SOCKET playerSocket = INVALID_SOCKET;
    CONNECTION_CONTEXT_TYPE type = ACCEPT;
    OVERLAPPED overlapped {};
    WSABUF buffer{};
};

bool sendDataToConnection(PacketBuffer* buffer, SOCKET playerSocket);

bool startupServerSocket();

void closeServerSocket(HANDLE listenport);

void closeConnection(PLAYER_CONNECTION_CONTEXT* context);

void closeConnection(SOCKET* playerSocket);
#endif //MINECRAFTSERVER_SERVER_CONNECTION_H
