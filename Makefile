CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/auth.c src/policies.c src/claims.c src/customers.c src/reporting.c
OBJ = $(SRC:.c=.o)
EXEC = insurance_system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run