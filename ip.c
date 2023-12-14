#include "ip.h"

// 全局变量
struct ip_pair ip_pair[10000];

// 处理IP信息
void do_ip(char *data) {
  global.packet_ip++;

  struct iphdr *pip;
  pip = (struct iphdr *)data; /* pip = point to ip layer */
  if (global.print_flag_ip)
    print_ip(pip);

  ip_count(pip);

  char *pdata = data + pip->ihl * 4;

  switch (pip->protocol) {
  case IPPROTO_TCP:
    do_tcp(pdata);
    break;
  case IPPROTO_UDP:
    do_udp(pdata);
    break;
  default:
    printf("IP: Can't find upper layer protocol\n");
    break;
  }
}

// 打印IP信息
void print_ip(struct iphdr *iph) {
  printf("=================== IP  Header ===================\n");
  printf("Version         (4 bits) : %d\n", iph->version);
  printf("IHL             (4 bits) : %d\n", iph->ihl * 4);
  printf("Type-of-Service (8 bits) : %d\n", iph->tos);
  printf("Total  Length   (16bits) : %d\n", ntohs(iph->tot_len));
  printf("Identification  (16bits) : %d\n", ntohs(iph->id));
  printf("Flags           (3bits)  : \n");
  printf("Frag   Offset   (13bits) : %d\n", ntohs(iph->frag_off));
  printf("Time-to-live    (8 bits) : %d\n", iph->ttl);
  printf("Protocol        (8 bits) : %d\n", iph->protocol);
  printf("Header Checksum (16bits) : %d\n", ntohs(iph->check));
  printf("Source Address  (32bits) : %s\n",
         inet_ntoa(*(struct in_addr *)(&iph->saddr)));
  printf("Dest   Address  (32bits) : %s\n",
         inet_ntoa(*(struct in_addr *)(&iph->daddr)));
}

// 计算IP个数
void ip_count(struct iphdr *iph) {
  ip_pair[global.packet_ip - 1].source_ip = iph->saddr;
  ip_pair[global.packet_ip - 1].dest_ip = iph->daddr;
}
