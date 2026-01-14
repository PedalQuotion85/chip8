CC = gcc
CFLAGS = -std=c17 -Wall -Wextra

UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(UNAME_S), Darwin)
	# For macOS
	INCLUDES = $(shell pkg-config --cflags sdl3)
	LDFLAGS = $(shell pkg-config --libs sdl3)
	START = ./$(TARGET)
else
	LIBS = .\SDL3-devel-3.4.0-mingw\SDL3-3.4.0\x86_64-w64-mingw32\lib
	INCLUDES = -I.\SDL3-devel-3.4.0-mingw\SDL3-3.4.0\x86_64-w64-mingw32\include
	LDFLAGS = -L$(LIBS) -lSDL3 -lmingw32 -mwindows
	START = $(TARGET)
endif

TARGET = chip8
SRC = chip8.c

all: start

$(TARGET): $(SRC)
	$(CC) chip8.c -o chip8 $(CFLAGS) $(INCLUDES) $(LDFLAGS)

start: $(TARGET)
	$(START)
