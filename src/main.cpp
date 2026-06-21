#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) { // "We use argc and argv to accept command-line arguments when the program starts. In a server application like Redis, users may provide configuration files, port numbers, or startup options through the terminal. argc tells us how many arguments were passed, and argv contains the actual argument values. This allows the server to be configured dynamically at startup without modifying the source code."
    int port = 6379; // default
    if (argc >=2) port = std::stoi(argv[1]); 

    if (RedisDatabase::getInstance().load("dump.my_rdb"))
        std::cout << "Database Loaded From dump.my_rdb\n";
    else 
        std::cout << "No dump found or load failed; starting with an empty database.\n";

    RedisServer server(port); // constructor 

    // Backgroung persistance: dump the database every 300 seconds. (5 * 60 seconds save database)
    std::thread persistanceThread([](){
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(300));  
            if (!RedisDatabase::getInstance().dump("dump.my_rdb"))
                std::cerr << "Error Dumping Database\n";
            else 
                std::cout << "Database Dumped to dump.my_rdb\n";
        }
    });
    persistanceThread.detach();
    
    server.run();
    return 0;
}