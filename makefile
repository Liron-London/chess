CC = gcc
OBJS = array_list.o minimax.o game.o game_commands.o file_handler.o setting.o GUI.o move.o 
TEST_OBJS = setting_test.o array_list_unit_test.o game_unit_test.o game_command_unitest.o
EXEC = chessprog
ARRAY_LIST_TEST_OBJS = array_list.o array_list_unit_test.o
GAME_TEST_OBJS = array_list.o game.o moves.o
GAME_COMMANDS_TEST_OBJS = array_list.o game.o game_commands.o setting.o game_command_unitest.o moves.o file_handler.o minimax.o
FILE_HANDLER_TEST_OBJS = file_handler.o
MINIMAX_TEST_OBJ = array_list.o game.o
SETTINGS_TEST_OBJ = array_list.o game.o setting_test.o setting.o game_commands.o moves.o file_handler.o minimax.o
GAME_TEST_OBJ = array_list.o game.o setting.o game_unit_test.o game_commands.o moves.o
GUI_OBJS = GUI.o game.o
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

# COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors $(SDL_CFLAGS)
# COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors
COMP_FLAG = -std=c99
LINK_FLAG = $(SDL_LDFLAGS)

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main


$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
array_list_unit_test: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
setting_test: $(SETTINGS_TEST_OBJ)
	$(CC) $(SETTINGS_TEST_OBJ) -o $@
game_unit_test: $(GAME_TEST_OBJ)
	$(CC) $(GAME_TEST_OBJ) -o $@
game_command_unitest: $(GAME_COMMANDS_TEST_OBJS)
	$(CC) $(GAME_COMMANDS_TEST_OBJS) -o $@
gui_test: $(GUI_OBJS)
	$(CC) $(GUI_OBJS) $(SDL_LIB) -o $@  
	
array_list_unit_test.o: array_list_unit_test.c array_list.h array_list.c
	$(CC) $(COMP_FLAG) -c $*.c
moves.o: moves.c moves.h game.c game.h
	$(CC) $(COMP_FLAG) -c $*.c
file_handler.o: file_handler.h file_handler.c
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c game.h array_list.c array_list.h
	$(CC) $(COMP_FLAG) -c $*.c
minimax.o: minimax.c minimax.h game.c game.h moves.c moves.h	
	$(CC) $(COMP_FLAG) -c $*.c
array_list.o: array_list.c array_list.h
	$(CC) $(COMP_FLAG) -c $*.c
setting.o: game_commands.c game_commands.h game.c game.h setting.c setting.h array_list.c array_list.h
	$(CC) $(COMP_FLAG) -c $*.c
game_commands.o: moves.h moves.c game_commands.c game_commands.h game.c game.h array_list.c array_list.h file_handler.c file_handler.h minimax.c minimax.h
	$(CC) $(COMP_FLAG) -c $*.c

setting_test.o: moves.c moves.h game_commands.c game_commands.h game.c game.h setting.c setting.h array_list.c array_list.h setting_test.c
	$(CC) $(COMP_FLAG) -c $*.c
game_unit_test.o: game.c game.h moves.c moves.h setting.c setting.h array_list.c array_list.h
	$(CC) $(COMP_FLAG) -c $*.c
game_command_unitest.o: game.c game.h setting.c setting.h array_list.c array_list.h game_commands.h game_commands.c moves.c moves.h minimax.c minimax.h 
	$(CC) $(COMP_FLAG) -c $*.c

GUI.o: GUI.c GUI.h game.c game.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(OBJS) $(TEST_OBJS)
