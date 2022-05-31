CC = g++
CFLAGS  = -g -Wall

TARGET = Dijkstra

SRCS = Dijkstra.cpp \
	edge.cpp \
	node.cpp \
	record.cpp \
	lsdb.cpp \
	nodeset.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)
	@echo  Dijkstra Compiled Successfully.

$(TARGET) : $(OBJS)
	$(RM) $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	$(RM) *.o

clean:
	$(RM) *.o $(TARGET)