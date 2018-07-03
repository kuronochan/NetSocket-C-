//
// Created by mo on 18-6-29.
//

#ifndef SRV_UNP_H
#define SRV_UNP_H

#include "arpa/inet.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t salen);

ssize_t readn(int filedes, void *buff, size_t nbytes);
ssize_t writen(int filedes, void *buff, size_t nbytes);
ssize_t readline(int fd, void *vptr, size_t maxlen);

#endif //SRV_UNP_H
