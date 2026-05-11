CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2
TARGET  = gorev_sistemi

SRCS = main.c task.c array_list.c linked_list.c \
       linear_ds.c priority_queue.c bst.c hash_table.c \
       graph.c category_tree.c performance.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q *.o $(TARGET).exe 2>nul || true

run: all
	./$(TARGET)

.PHONY: all clean run
