CC = g++

CFLAGS = -Wall -g

INCLUDES = -I/include

LFLAGS = -L/lib

LIBS = -lSDL2

SRCS = BaseClass.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = mycc

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it