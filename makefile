CC = gcc
OBJS = array_list.o minimax.o game.o game_commands.o file_handler.o settings.o main.o
TEST_OBJS = setting_unit_test.o array_list_unit_test.o game_test.o
EXEC = chessprog
ARRAY_LIST_TEST_OBJS = array_list.o array_list_unit_test.o
GAME_TEST_OBJS = array_list.o game.o
GAME_COMMANDS_TEST_OBJS = array_list.o game.o game_commands.o
FILE_HANDLER_TEST_OBJS = file_handler.o
MINIMAX_TEST_OBJ = array_list.o game.o
SETTINGS_TEST_OBJ = array_list.o game.o

COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors



$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
array_list_unit_test: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
setting_unit_test: $(SETTINGS_TEST_OBJ)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@

array_list_unit_test.o: array_list_unit_test.c array_list.h array_list.c
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c game.h array_list.o
	$(CC) $(COMP_FLAG) -c $*.c
array_list.o: array_list.c array_list.h
	$(CC) $(COMP_FLAG) -c $*.c
setting.o: setting.c setting.h game.o
	$(CC) $(COMP_FLAG) -c $*.c
setting_unit_test.o: game.o setting.o 
	$(CC) $(COMP_FLAG) -c $*.c


clean:
	rm -f *.o $(EXEC) $(OBJS)
