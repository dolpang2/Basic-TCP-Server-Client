//
// Created by lee on 10/14/15.
//

#ifndef TCPEXAMPLE_INET_H
#define TCPEXAMPLE_INET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // To use memset (not bzero)

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>  // To use fork()

#define SERV_UDP_PORT 6001
#define SERV_TCP_PORT 6001
#define SERV_HOST_ADDR "127.0.0.1"
#define MAXLINE 512

char *pname;

#endif //TCPEXAMPLE_INET_H
