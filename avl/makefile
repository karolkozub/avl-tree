CC=g++
TAR=tar
ZIP=zip
RM=rm
CFLAGS=-Wall -g
DBGFLAGS=$(CFLAGS) -DDEBUG
SRC=tree.hh bst_tree.hh avl_tree.hh main.cc
FILES=$(SRC) makefile
EXEC=avl
TARF=$(EXEC).tar.bz2
ZIPF=$(EXEC).zip

all: $(SRC)
	$(CC) main.cc -o $(EXEC) $(CFLAGS)

debug: $(SRC)
	$(CC) main.cc -o $(EXEC) $(DBGFLAGS)

tar:
	$(TAR) cjvf $(TARF) $(FILES)

zip:
	zip $(ZIPF) $(FILES)

clean:
	-$(RM) -f *~ $(EXEC) $(TARF) $(ZIPF)
