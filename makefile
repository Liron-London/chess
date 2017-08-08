CC = gcc
OBJS = array_list.o minimax.o game.o game_commands.o file_handler.o settings.o main.o
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
array_list_unit_test.o: array_list_unit_test.c array_list.o
	$(CC) $(COMP_FLAG) -c $*.c
array_list.o: array_list.h array_list.c
	$(CC) $(COMP_FLAG) -c $*.c
	
	
	# from ex3
	
SPFIARParser: $(PARSER_TEST_OBJS)
	$(CC) $(PARSER_TEST_OBJS) -o $@
SPMiniMaxUnitTest: $(MINMAX_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMiniMaxNodeUnitTest: $(MINMAXNode_TEST_OBJ)
	$(CC) $(MINMAXNode_TEST_OBJ) -o $@
SPMainAuxUnitTest: $(MAINAUX_TEST_OBJS)
	$(CC) $(MAINAUX_TEST_OBJS) -o $@
SPFIARGameUnitTest.o: SPFIARGameUnitTest.c unit_test_util.h SPArrayList.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARParserUnitTest.o: SPFIARParserUnitTest.c SPFIARParser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxUnitTest.o: SPMiniMaxUnitTest.c SPMiniMax.h SPFIARGame.h SPMiniMaxNode.h unit_test_util
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNodeUnitTest.o: SPMiniMaxNodeUnitTest.c SPMiniMaxNode.h unit_test_util SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARGame.o: SPFIARGame.c SPFIARGame.h SPArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
SPFIARParser.o: SPFIARParser.c SPFIARParser.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c 
SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h SPFIARGame.h
	$(CC) $(COMP_FLAG) -c $*.c
SPMainAux.o: SPMainAux.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c
main.o: main.c SPMainAux.h SPFIARGame.h SPMiniMax.h
	$(CC) $(COMP_FLAG) -c $*.c


clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
