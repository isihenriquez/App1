CC = gcc

CFLAGS = -Wall -Wextra -std=c99

SRC = src/main.c

OUT = app1

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
	

