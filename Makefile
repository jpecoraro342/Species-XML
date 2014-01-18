OBJS = Species.o Tree.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

tree : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o tree

Species.o : Species.h
	$(CC) $(CFLAGS) Species.cpp

Tree.o : Tree.h TreeNode.h
	$(CC) $(CFLAGS) Tree.cpp

main.o : main.cpp Tree.cpp TreeNode.h Species.h rapidxml.hpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o *~ tree