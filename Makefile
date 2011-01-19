CFLAGS = -Wall -pthread 
CC = g++
DEBUG = -g
RM =/bin/rm -rf
LIBS =


OBJS = main.o thread.o photon.o mutex.o layer.o boundary.o medium.o
#OBJS := $(wildcard *.o)

.cpp.o:
	 $(CC) -c $(CFLAGS) $*.cpp
#####


all : mcmlpthread 


mcmlpthread: $(OBJS)
	 $(CC) -o  $@ $(OBJS) $(CFLAGS) $(LIBS)


clean::
	 $(RM) mcmlpthread
	 $(RM) *.o

