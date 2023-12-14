#include "udp.h"

// 打印dup信息
void print_udp(struct udphdr *pudp) {
  printf("=================== UDP Header ===================\n");
  printf("Source Port   (16bits) : %d\n", ntohs(pudp->source));
  printf("Dest   Port   (16bits) : %d\n", ntohs(pudp->dest));
  printf("UDP    Length (16bits) : %d\n", ntohs(pudp->len));
  printf("Checksum      (16bits) : %d\n", ntohs(pudp->check));
  if (ntohs(pudp->len) != sizeof(struct udphdr) && ntohs(pudp->len) < 20) {
    char *data = (char *)pudp + sizeof(struct udphdr);
    printf("UDP Payload: %s\n", data);
  }
}

// 处理UDP
void do_udp(char *data) {
  global.packet_udp++;

  struct udphdr *pudp = (struct udphdr *)data;
  if (global.print_flag_udp)
    print_udp(pudp);
}
