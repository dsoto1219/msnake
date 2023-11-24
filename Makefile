CC := gcc
CFLAGS := -ggdb3 -std=c11 -Wall -Wpedantic -lncursesw
SRC := main.c direction.c snake.c
EXEC := snake

$(EXEC): $(SRC)
	@$(CC) $(SRC) $(CFLAGS) -o $(EXEC) 

.PHONY: clean
clean:
	@rm -f *.o $(EXEC) 
