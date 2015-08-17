ifndef CC
CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -Wformat -std=c11 -O0
endif
LD=$(CC)

PROJECTNAME=Test_FreeDcmTest

ODIR=build

LIBS= -I Dependencies

SOURCE=$(shell find . -follow -name "*.c")

.PHONY: all clean

all: $(OBJ)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $(LIBS) $(SOURCE) -lm -o $(ODIR)/$(PROJECTNAME)

clean:
	rm -rf $(ODIR) 
