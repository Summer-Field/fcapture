#include "util.h"

// 全局变量
int sockfd = -1;
struct global_info global;

// 初始化全局信息
void init_global(struct global_info *var) {
  var->c_start = clock();

  var->bytes = 0;
  var->packet_num = 0;

  var->packet_ip = 0;
  var->packet_tcp = 0;
  var->packet_udp = 0;

  var->print_flag_frame = 0;
  var->print_flag_ip = 0;
  var->print_flag_tcp = 0;
  var->print_flag_udp = 0;
}

// 一个用于打印全局信息的函数
void print_global(struct global_info var) {
  var.c_end = clock();
  printf("\n\n************** Global Info **************\n\n");
  printf("Execution Time: %f ms.\n", difftime(var.c_end, var.c_start));
  printf("Accepted  Bytes Number: %d kbytes.\n", var.bytes / 1024);
  printf("Accepted  Packets Number: %d\n\n", var.packet_num);

  if (var.packet_ip)
    printf("Accepted  IP  Packets Number: %d\n", var.packet_ip);

  if (var.packet_tcp)
    printf("Accepted  TCP Packets Number: %d\n", var.packet_tcp);
  if (var.packet_udp)
    printf("Accepted  udp Packets Number: %d\n", var.packet_udp);

  printf("\n");
}

// 打印错误信息并退出
void error_and_exit(char *msg, int exit_code) {
  perror(msg);
  exit(exit_code);
}

// 设置网卡模式成混帐模式,这样的话可以截获以太网帧数据
void set_card_promisc(char *interface_name, int sock) {
  // 用于套接口ioctl的接口请求结构体
  struct ifreq ifr;

  // 复制网卡名称进入请求结构体的名称元素
  memset(&ifr, 0, sizeof(struct ifreq));
  strncpy(ifr.ifr_name, interface_name, IFNAMSIZ - 1);

  //通过ioctl获得相应信息
  if ((ioctl(sock, SIOCGIFFLAGS, &ifr) == -1)) {
    perror("ioctl");
    error_and_exit("ioctl", 2);
  }

  // 设置网卡模式标志为混杂模式
  ifr.ifr_flags |= IFF_PROMISC;

  // 通过ioctl把参数传递给网卡
  if (ioctl(sock, SIOCSIFFLAGS, &ifr) == -1) {
    perror("ioctl");
    error_and_exit("ioctl", 3);
  }
}

// 把mac地址转换成字符串
void mac_to_str(char *buf, char *mac_buf) {
  sprintf(mac_buf, "%02x:%02x:%02x:%02x:%02x:%02x", (unsigned char)*buf,
          (unsigned char)(*(buf + 1)), (unsigned char)(*(buf + 2)),
          (unsigned char)(*(buf + 3)), (unsigned char)(*(buf + 4)),
          (unsigned char)(*(buf + 5)));
  mac_buf[17] = 0;
}

// 信号处理函数
void sig_int(int sig) {
  if (sig == SIGINT) {
    print_global(global);
    exit(0);
  }
}

// 解析命令行输入参数
void parse_opt(int argc, char **argv) {
  // 表示打印所有包头信息
  if (argc == 1) {
    global.card = "enp0s1";
    global.print_flag_frame = 1;
    global.print_flag_ip = 1;
    global.print_flag_tcp = 1;
    global.print_flag_udp = 1;
  } else {
    // 通过指定协议名称只打印某层些协议
    for (int i = 1; i < argc; i++) {
      if (!strcasecmp(argv[i], "frame"))
        global.print_flag_frame = 1;
      else if (!strcasecmp(argv[i], "ip"))
        global.print_flag_ip = 1;
      else if (!strcasecmp(argv[i], "tcp"))
        global.print_flag_tcp = 1;
      else if (!strcasecmp(argv[i], "udp"))
        global.print_flag_udp = 1;
    }
  }
}
