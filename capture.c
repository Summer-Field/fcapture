#include "capture.h"

// 主函数, 处理命令行输入, 设置好全局变量, 并调用接受和处理帧的函数
int main(int argc, char **argv) {

  // 初始化全局变量
  init_global(&global);

  // 解析命令行传入参数
  parse_opt(argc, argv);

  // 通过协议族AF_PACKET类信SOCK_RAW,
  // 类型SOCK_RAW创建一个用于可以接受网卡帧数据的套接口,同时返回套就口文件描述符
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1) {
    error_and_exit("socket", 1); // 如果发生错误，返回错误值, 并退出
  }

  // 设定网卡成混杂模式
  set_card_promisc("enp0s1", sockfd);

  // 设定信号处理函数, 下面是设置当我们按下ctrl-c时所调用的处理函数
  signal(SIGINT, sig_int);

  // 无限循环接收以太网卡数据帧, 并进行数据分用,直到你按下ctrl-c
  while (1) {
    do_frame(sockfd);
  }

  return 0;
}
