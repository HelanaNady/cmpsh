# compiler to use
CC=gcc

# warnings
CFLAGS=-c -Wall

# executable name
TARGET = file_handler

# source files
SRC = main.c file_handler.c

# .c files to .o files conversion
OBJ = $(SRC:.c=.o)

# target
all: $(TARGET)

# object and executables linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# cleanups
clean:
	rm -f $(OBJ) $(TARGET)

# running after compiling
run: $(TARGET)
	./$(TARGET)
