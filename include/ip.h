#ifndef IP_H
#define IP_H

#include "tcp.h"
#include "udp.h"
#include "util.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>

// 目标/源地址
struct ip_pair {
  unsigned int source_ip;
  unsigned int dest_ip;
  unsigned int count;
};

// 函数原型
extern struct ip_pair ip_pair[10000];

void do_ip(char *data);
void print_ip(struct iphdr *);
void ip_count(struct iphdr *);

#endif // !IP_H
