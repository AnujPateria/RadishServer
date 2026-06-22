#ifndef REDIS_COMMAND_HANDLER_H
#define REDIS_COMMAND_HANDLER_H

#include <string>
using namespace std;
class RedisCommandHandler {
public:
    RedisCommandHandler();
    // Process a command from a client and return a RESP-formatted response.
    string processCommand(const std::string& commandLine);
};

#endif
