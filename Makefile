# Compilador
CC = gcc

# Flags de compilación (avisa errores y usa C99)
CFLAGS = -Wall -Wextra -std=c99

# Archivos fuente
SRC = src/main.c

# Nombre del ejecutable
OUT = app1

# Regla principal
all: $(OUT)

# Cómo se compila el ejecutable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Limpiar archivos generados
clean:
	rm -f $(OUT)
	

