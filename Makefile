# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -g

# 目标文件和依赖项
TARGET = capture
SRCS = capture.c frame.c ip.c tcp.c udp.c util.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJS): $(SRCS) 
	$(CC) $(CFLAGS) -c -o $@ $*.c

# 清理中间文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)
