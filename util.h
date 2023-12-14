#ifndef UTIL_H
#define UTIL_H

#include <error.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>

// 全局信息
extern int sockfd;
extern struct global_info {
  char *card;

  unsigned int bytes;
  unsigned int packet_num;

  unsigned int packet_ip;
  unsigned int packet_tcp;
  unsigned int packet_udp;

  int print_flag_frame;
  int print_flag_ip;
  int print_flag_tcp;
  int print_flag_udp;

  time_t c_start, c_end;
} global;

// 函数原型
void init_global(struct global_info *var);
void error_and_exit(char *msg, int exit_code);
void set_card_promisc(char *interface_name, int sock);
void mac_to_str(char *buf, char *mac_buf);
void print_global(struct global_info var);
void sig_int(int sig);
void parse_opt(int argc, char **argv);

#endif // !UTIL_H
