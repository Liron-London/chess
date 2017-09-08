CC = gcc
OBJS = main.o SPTicTacToe.o graphics/SPTicTacToeGUIManager.o graphics/SPTicTacToeGameWin.o  
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors $(SDL_CFLAGS) $(SDL_LDFLAGS)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
ttt: $(OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@

main.o: graphics/SPTicTacToeGUIManager.c graphics/SPTicTacToeGUIManager.h main.c  
	$(CC) $(COMP_FLAG) -c $*.c
SPTicTacToe.o: SPTicTacToe.c SPTicTacToe.h
	$(CC) $(COMP_FLAG) -c $*.c
graphics/SPTicTacToeGameWin.o: graphics/SPTicTacToeWindow.c graphics/SPTicTacToeWindow.h SPTicTacToe.c SPTicTacToe.h graphics/SPTicTacToeGameWin.h graphics/SPTicTacToeGameWin.c 
	$(CC) $(COMP_FLAG) -c $*.c
graphics/SPTicTacToeGUIManager.o: graphics/SPTicTacToeGUIManager.c graphics/SPTicTacToeGUIManager.h graphics/SPTicTacToeGameWin.c graphics/SPTicTacToeGameWin.h graphics/SPTicTacToeMainWin.h
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f *.o $(EXEC) $(OBJS)
