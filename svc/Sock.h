//
// Created by huangdunyu on 18-7-27.
//

#ifndef SOCK_H
#define SOCK_H
#include "Thread.h"
namespace Sock
{
    class Accept: public Thread
    {
    public:
        Accept(void);
        virtual ~Accept(void);

        void set(int port);

        int init(void);

        int fini(void);

        void server_listen();

        virtual int accept_svc(int connfd);

        virtual void run_handler(void);

        virtual void exit_handler(void);
    private:
        int port;
        int listenfd;
    };

}

#endif //SOCK_H
