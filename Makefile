CC = g++
CFLAGS = -Wall
PROG = ConwaysGameOfLife

SRCS = ConwaysGameOfLife.cpp Cell.cpp ConwayLogic.cpp

LIBS = # i.e. -lX11 -lCImg 


all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)