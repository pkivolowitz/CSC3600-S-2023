CFLAGS	= -Wall -Iinclude -g -std=c++11 -DDEBUG
LFLAGS	= 

CC	= g++

srcs = $(wildcard *.cpp)
deps = $(srcs:.cpp=.d)

all:	server client

server: server.o
		$(CC) $^ -o $@ $(LFLAGS)

client: client.o
		$(CC) $^ -o $@ $(LFLAGS)

%.o: 	%.cpp
		$(CC) -MMD -MP $(CFLAGS) -c $< -o $@

.PHONY: clean

# $(RM) is rm -f by default
clean:
		$(RM) *.o $(deps) a.out core client server
		rm -rf .vscode/ipch/*

-include $(deps)
