#include "tcp.h"

// 处理TCP
void do_tcp(char *data) {
  global.packet_tcp++;

  struct tcphdr *ptcp;
  ptcp = (struct tcphdr *)data;

  if (global.print_flag_tcp)
    print_tcp(ptcp);
}

// 打印TCP信息
void print_tcp(struct tcphdr *ptcp) {
  printf("=================== TCP Header ===================\n");
  printf("Source Port    (16bits) : %d\n", ntohs(ptcp->source));
  printf("Destn  Port    (16bits) : %d\n", ntohs(ptcp->dest));
  printf("Seqe   Number  (32bits) : %u\n", ntohl(ptcp->seq));
  printf("Ack    Number  (32bits) : %u\n", ntohl(ptcp->ack_seq));
  printf("Data   Offset  (10bits) : %d\n", ptcp->doff * 4);
  printf("Flags          (6 bits) : \n");
  printf("- urg          (1 bits) : %d\n", ptcp->urg);
  printf("- ack          (1 bits) : %d\n", ptcp->ack);
  printf("- psh          (1 bits) : %d\n", ptcp->psh);
  printf("- rst          (1 bits) : %d\n", ptcp->rst);
  printf("- syn          (1 bits) : %d\n", ptcp->syn);
  printf("- fin          (1 bits) : %d\n", ptcp->fin);
  printf("Window Size    (16bits) : %d\n", ntohs(ptcp->window));
  printf("Checksum       (16bits) : %d\n", ntohs(ptcp->check));
  printf("Urgent Pointer (16bits) : %d\n", ntohs(ptcp->urg_ptr));

  if (ptcp->doff * 4 == 20) {
    printf("Reserverd: Null\n");
  } else {
    printf("Reserverd: %d bytes\n", ptcp->doff * 4 - 20);
  }

  char *data = (char *)ptcp;
  data += ptcp->doff * 4;
  printf("Payload Length: %ld bytes\n", strlen(data));
}
