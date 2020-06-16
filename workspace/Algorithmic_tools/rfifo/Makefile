#CROSSCOMPILE := arm-linux-
CROSSCOMPILE :=

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/.

LDFLAGS := -pthread 

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS :=rfifo.o \
	   rfifo_test.o \

all: $(OBJS)
	$(CC) $(LDFLAGS) -o test_rfifo $^

clean:
	rm -f test_rfifo 
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

