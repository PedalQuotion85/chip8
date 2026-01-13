CC = gcc
CFLAGS = -std=c17 -Wall -Wextra 
LIBS = .\SDL3-devel-3.4.0-mingw\SDL3-3.4.0\x86_64-w64-mingw32\lib 
INCLUDES = .\SDL3-devel-3.4.0-mingw\SDL3-3.4.0\x86_64-w64-mingw32\include
LDFLAGS = -L$(LIBS) -lSDL3 -lmingw32 -mwindows 

TARGET = chip8 
SRC = chip8.c

all: start

$(TARGET): $(SRC)
	$(CC) chip8.c -o chip8 $(CFLAGS) -I$(INCLUDES) $(LDFLAGS)

start: $(TARGET)
	$(TARGET)

