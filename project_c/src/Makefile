CC = gcc
PROG = programa
PKG = `pkg-config --cflags --libs glib-2.0`
CFLAGS = -g -std=c99 -Wall
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))





$(PROG): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(PKG)

%.o : %.c
	@$(CC) $(CFLAGS) $(PKG) -c $^

.PHONY: build
build: $(PROG)

.PHONY: run
run: $(PROG)
	@./$(PROG)

.PHONY : clean
clean: 
	-@rm *.o $(PROG)

.PHONY: gdb
gdb:
	gdb ./programa