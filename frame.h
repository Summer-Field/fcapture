#ifndef FRAME_H
#define FRAME_H

#include "ip.h"
#include "util.h"
#include <net/ethernet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

// 函数原型
void do_frame(int sockfd);
void print_frame(struct ether_header *peth);

#endif // !FRAME_H
