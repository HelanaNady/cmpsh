# the compiler to use
CC=gcc

# for warnings
CFLAGS=-c -Wall

# name of exe file
TARGET = cmpsh

# source file
SRC = cmpsh.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


# clean
clean:
	rm -f $(OBJ) $(TARGET)

# Run the shell after compiling
run: $(TARGET)
	./$(TARGET)
