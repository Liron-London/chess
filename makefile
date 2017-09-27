# Declaration of variables
CC = gcc
CC_FLAGS = -std=c99 -Wall -Wextra -Werror -pedantic-errors -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main
 
# File names
EXEC = chessprog
SOURCES = $(wildcard *.c)
SOURCES += $(wildcard ./core/*.c)
SOURCES += $(wildcard ./gui/*.c)
SOURCES += $(wildcard ./util/*.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
all: $(OBJECTS)
	$(CC) $(OBJECTS) $(SDL_LIB) -o $(EXEC)
 
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)