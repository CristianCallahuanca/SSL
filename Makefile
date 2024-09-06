EXEC = prog
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c tabla.c conversion.c
OBJ = $(SRC:.c=.o)
all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: 
	rm -f $(OBJ) $(EXEC)