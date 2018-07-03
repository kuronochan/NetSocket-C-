//
// Created by mo on 18-6-29.
//
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include "unp.h"
#include "string.h"

char* sock_ntop(const sockaddr *sa, socklen_t salen)
{
    char portstr[8];
    static char str[128];

    switch(sa->sa_family)
    {
        case AF_INET:
        {
            struct sockaddr_in *sin = (sockaddr_in *)sa;
            if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                return (NULL);
            if(ntohs(sin->sin_port) != 0)
            {
                snprintf(portstr, sizeof(portstr), ":%d",
                ntohs(sin->sin_port));
                strcat(str, portstr);
            }
            return (str);
        }
        case AF_INET6:
        {
            struct sockaddr_in6 *sin = (sockaddr_in6 * )sa;
            if(inet_ntop(AF_INET6, &sin->sin6_addr, str, sizeof(str)) == NULL)
                return (NULL);
            if(ntohs(sin->sin6_port) != 0)
            {
                snprintf(portstr, sizeof(portstr), ":%d",
                ntohs(sin->sin6_port));
                strcat(str, portstr);
            }
            return (str);
        }
        default:
            return (NULL);

    }
    return (NULL);
}

ssize_t readn(int fd, void* vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;
    ptr = (char*)vptr;
    nleft = n;
    while(nleft > 0)
    {
        if( (nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);
}

ssize_t writen(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    char *ptr;

    ptr = (char*)vptr;
    nleft = n;
    while(nleft > 0)
    {
        if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c,*ptr;
    ptr = (char*)vptr;
    for(n = 1; n <maxlen; n++)
    {
        again:
        if( (rc = read(fd, &c, 1)) == 1)
        {
            *ptr++ = c;
            if(c == 'n')
                break;

        }
        else if(rc == 0)
        {
            *ptr = 0;
            return (n - 1);
        }
        else
        {
            if(errno == EINTR)
                goto again;
            return -1;
        }

    }
    *ptr = 0;
    return n;
}

