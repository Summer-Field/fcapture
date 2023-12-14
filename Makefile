CC = gcc
CFLAGS = -Wall -Wextra -g

SRCDIR = src
INCDIR = include

SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRC_FILES))

.PHONY: all clean

all: capture

capture: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f capture $(OBJ_FILES)
