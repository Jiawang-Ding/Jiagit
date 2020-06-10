#CROSSCOMPILE := arm-linux-
CROSSCOMPILE :=

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/.

#LDFLAGS := -lm -lfreetype

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS :=dlist.o \
	   page.o \
	   page_test.o \

all: $(OBJS)
	$(CC) $(LDFLAGS) -o page_test $^

clean:
	rm -f page_test 
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

