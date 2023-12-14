#include "frame.h"

//用于从网卡接受一帧数据,同时根据以太网协议字段传递数据给相应的上层协议处理
void do_frame(int sock) {

  char frame_buf[2000];                // 存储一帧数据
  bzero(frame_buf, sizeof(frame_buf)); // 清空帧数据缓冲区
  int len = sizeof(frame_buf);         // 缓存长度
  int recv_num;                        // 接受字节数
  struct sockaddr_in addr;             // 发送方的地址信息

  // 从网卡接收一帧数据
  recv_num = recvfrom(sock, (char *)frame_buf, sizeof(frame_buf), 0,
                      (struct sockaddr *)&addr, (socklen_t *)&len);

  //所接收的包的总数自加1
  global.packet_num++;

  // 从网卡接收的字节总数
  global.bytes += recv_num;

  //打印接收的包是第几个包
  // printf("此帧数据长度: %d\n", recv_num );

  // 定义一个用于指向以太网帧的指针 (这里我们只考虑最常见的以太网帧的情况)
  struct ether_header *peth;

  // 让以太网头指针指向从网卡接受到的帧的数据的开头
  peth = (struct ether_header *)frame_buf;

  // 传递以太网帧首地址给打印以太网帧信息的打印函数
  if (global.print_flag_frame)
    print_frame(peth);

  // 定义一个数据指针,用于指向以太网帧的数据部分
  char *pdata;

  // 让 pdata 指向以太网帧的数据部分
  pdata = frame_buf + sizeof(struct ether_header);

  // 根据以太网帧的协议字段进行数据分用 －
  // 也就是进行数据拆封，根据协议字段调用相应层的处理函数
  switch (ntohs(peth->ether_type)) {
  case ETHERTYPE_PUP:
    break;
  case ETHERTYPE_IP:
    do_ip(pdata);
    break;
  default:
    printf("Unkonw ethernet type  %d %x.\n", ntohs(peth->ether_type),
           ntohs(peth->ether_type));
    break;
  }
}

// 打印以太网帧的包头信息
void print_frame(struct ether_header *peth) {
  // mac地址
  char buf[18];

  printf("\n==================================   %dth Packet  "
         "=======================================\n\n",
         global.packet_num);
  printf("=================== Eth  Frame ===================\n");
  char *shost = (char *)peth->ether_shost;
  mac_to_str(shost, buf);
  printf("Source MAC :  %s\n", buf);

  char *dhost = (char *)peth->ether_dhost;
  mac_to_str(dhost, buf);
  printf("Dest   MAC  :%s\n", buf);
}
