#ifndef REDIS_SERVER_H // |-      // use macros case
#define REDIS_SERVER_H // |-| | -  This is called header guards in c/cpp
/*
Header guard : it do like if we define that file in different .cpp file then it will create same class aagin and again so redefinition of class error occurs

// with guard : first include -> not define -> include file then #deine marks it as already included . second include-> alrady defiend -> skip entire file

Alternative-/

Modern C++:

#pragma once

Simpler and widely used.
*/


#include <string> // why not c string? -> dangerous, buffer overflow, manual memory handling -> ex: char name[5] strcpy(name, "verylong text"); overflow -> crash/security issue
//ie why it safer
#include <atomic> // use for thread safe varible: if not multiple thread read wrong value 
//it guarante safe concurrent read/write

class RedisServer { // use pascal case
    public:
        RedisServer(int port); 
        void run();
        void shutdown();


    private: 
        int port;
        int server_socket;
        std::atomic<bool> running;
        
};

#endif