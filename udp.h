#ifndef UDP_H
#define UDP_H

#include "tcp.h"
#include "util.h"
#include <netinet/udp.h>

// 函数原型
void do_udp(char *data);
void print_udp(struct udphdr *);
#endif // !UDP_H
