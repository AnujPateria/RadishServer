#include "include/RadisServer.h"

#include <iostream>
#include <sys/socket.h> // provide socket, listen , bind api
#include <unistd.h> // use to close socket, pipes, files
#include <netinet/in.h> // contains sockaddr_in  htons() Internet address structures. use for ipv4 networking

static RedisServer* globalServer = nullptr;  // point to radis server why not server directly(singe handler) -> they are not part of the class give me shutdown is not defined because it belong to obkect 

RedisServer:: RedisServer(int port) : port(port), server_socket(-1), running(true) {
    globalServer = this;
}  //initializer list better than assignment inside constructor ] efficiet & direct initilization
// server socket = -1 invalid socket initially (Common systems programming convention.)

void RedisServer::shutdown() {
    running = false;
    if (server_socket != -1) {
        close(server_socket);
    }
    std::cout<<"Server Shutdown Complete!\n";
}/*Important

If not closed:

file descriptor leak
memory/resource exhaustion

Production servers must always close sockets.
*/

void RedisServer::run() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //[ AF_INET -> ipv4 alternative is AF_INET6(ipv6)], [SOCK_STREAM -> TCP (alternative UDP (SOCK_DGRAM)) connection why? because tcp guarante everthing ]  -> both return file descriptor
    if(server_socket < 0 ) {
        std:: cerr << "Error Creating Server Socket \n";
        return ;
    } // if socket server failed 

    int opt = 1 ;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));/*
    set socket option tells kernel socket to behave in particular way
    opt = 1; linux socket api use integr for true
    server socket -> use particular socket and apply thing on that
    sol socket -> this option belong to the socket layerit say Configure general socket behavior
    they are other levels two for tcp IPPROTO_TCP and for ip IPPROTO_IP for thier setting
    
    SO_REUSEADDR: allow reuse of an address/port (immediately restart)
    without this bind: addresss already in use (tcp enter time wait) kernel think i still need to keep information about connection 

    &opt : address of varibale 
    size of(opt) -> how many byter should i read
    
    */

    sockaddr_in serverAddr{}; // Creates an IPv4 address structure. 
    // equivalent to memset(&serverAddr, 0, sizeof(serverAddr)); it contain garbage that hsow unexpected behaviour
    serverAddr.sin_family = AF_INET; //otherwise family mismnatch bind may fail
    serverAddr.sin_port = htons(port); // why not simple serverAddr.sin_port = port; ? because computer and netwerok store byter differently
    //htons (host to netwrok short) convert cpu format to netwrok format without this kernel interpret wront port number
    serverAddr.sin_addr.s_addr = INADDR_ANY; // listen on all available network interface  also we can write serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); for local host only

    /*Interview Question

Why use htons()?
Answer:
Network protocols use big-endian byte order, while host machines may use little-endian. htons() converts the port number from host byte order to network byte order before sending it to the kernel.*/



    if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){ // attach socket to server without this os does not know which port server owns 
        std::cerr << "Error Binding Server Socket \n";
        return ;
    }

    if(listen(server_socket, 10) < 0) { // turn socket into waiting server now client connect
        std:: cerr << "Error Listening On Server Socket \n";
        return ;
    }

    std::cout << "Redis Server Listening On Port " << port << "\n";


}