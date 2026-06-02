#ifndef REDIS_SERVER_H // |-      // use macros case
#define REDIS_SERVER_H // |-| | -  This is called header guards in c/cpp
/*
Header guard : it do like if we define that file in different .cpp file then it will create same class aagin and again so redefinition of class error occurs

// with guard : first include -> not define -> include file then #define marks it as already included . second include-> alrady defiend -> skip entire file

Alternative-/

Modern C++:

#pragma once

Simpler and widely used.
*/

#include <string>
#include <atomic> // use for thread safe varible: if not multiple thread read wrong value 
//it guarante safe concurrent read/write

class RedisServer {
public:
    RedisServer(int port);
    void run();
    void shutdown();

private:
    int port;
    int server_socket;
    /*
            In linux everything is file descriptor: os assign some id to opened file
            socket is like a file in linux
            socket: create communication endpoint
        */
    std::atomic<bool> running;

    // Setup signal handling for graceful shutdown (ctrl + c) 
    void setupSignalHandler();
};

#endif