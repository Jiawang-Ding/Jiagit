#CROSSCOMPILE := arm-linux-
CROSSCOMPILE :=

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/.

#LDFLAGS := -lm -lfreetype

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS :=cycle_queue.o \
	   cycle_queue_test.o \

all: $(OBJS)
	$(CC) $(LDFLAGS) -o test_queue $^

clean:
	rm -f test_queue 
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

