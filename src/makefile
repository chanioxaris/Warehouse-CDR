CC = gcc

PROG = werhauz
HDRS = functions.h structs.h structs_heap.h
SRCS = main.c functions.c heap.c

OBJS = $(SRCS:.c=.o)

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

clean :
	rm -f $(OBJS) $(PROG)