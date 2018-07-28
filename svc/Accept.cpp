//
// Created by huangdunyu on 18-7-27.
//

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Sock.h"
#include "stdio.h"

Sock::Accept::Accept():port(0),listenfd(0)
{}

Sock::Accept::~Accept()
{}

void Sock::Accept::set(int port)
{
    this->port = port;
}

int Sock::Accept::init()
{
    return 0;
}

int Sock::Accept::fini()
{
    printf("close listenfd = %d", listenfd);
    ::close(listenfd);
    return 0;
}

void Sock::Accept::server_listen()
{
    struct sockaddr_in serveraddr;
    if((listenfd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("error");
        exit(1);
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

}
