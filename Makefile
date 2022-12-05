all: main

CC = clang
override CFLAGS += -g -Wall -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o "$@"

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o "$@"

main-debug: $(OBJS)
	$(CC) $(CFLAGS) -O0 $^ -o "$@"

clean:
	rm -f main main-debug $(OBJS)