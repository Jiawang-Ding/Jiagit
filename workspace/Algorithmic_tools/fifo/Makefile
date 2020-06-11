#CROSSCOMPILE := arm-linux-
CROSSCOMPILE :=

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/.

#LDFLAGS := -lm -lfreetype

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS :=fifo.o \
	   fifo_test.o \

all: $(OBJS)
	$(CC) $(LDFLAGS) -o fifo_test $^

clean:
	rm -f fifo_test 
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

