#include "../include/RadisServer.h"
#include<iostream>
using namespace std;


int main(int argc, char* argv[]) {
    int port = 6379; //default port
    if(argc >= 2) port = stoi(argv[1]);

    RedisServer server(port); //radis server object 



    return 0;
}