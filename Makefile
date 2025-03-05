CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = ./src/main.c ./src/srm.c
OBJS = $(SRCS:.c=.o)
TARGET = srm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
