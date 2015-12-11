OBJS = ray_tracer.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

ray_tracer : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ray_tracer

ray_tracer.o : ray_tracer.cpp
	$(CC) $(CFLAGS) ray_tracer.cpp

clean:
	\rm *.o *~ ray_tracer

tar:
	tar cfv ray_tracer.tar 
