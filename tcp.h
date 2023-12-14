#ifndef TCP_H
#define TCP_H

#include "util.h"
#include <netinet/tcp.h>

// 函数原型
void do_tcp(char *data);
void print_tcp(struct tcphdr *);
#endif // !TCP_H
