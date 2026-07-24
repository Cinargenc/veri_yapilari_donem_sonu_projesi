CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -I include
TARGET  = gorev_sistemi

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q src\*.o $(TARGET).exe 2>nul || true

run: all
	./$(TARGET)

.PHONY: all clean run
