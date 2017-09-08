CC = gcc
OBJS = main.o SPTicTacToe.o graphics/SPTicTacToeGUIManager.o graphics/SPTicTacToeGameWin.o  
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

COMP_FLAG = -std=c99 -Wall -Wextra -Werror $(SDL_CFLAGS) $(SDL_LDFLAGS)


$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
ttt: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

main.o: graphics/SPTicTacToeGUIManager.c graphics/SPTicTacToeGUIManager.h main.c  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPTicTacToe.o: SPTicTacToe.c SPTicTacToe.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPTicTacToeGameWin.o: graphics/SPTicTacToeWindow.c graphics/SPTicTacToeWindow.h SPTicTacToe.c SPTicTacToe.h graphics/SPTicTacToeGameWin.h graphics/SPTicTacToeGameWin.c 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
graphics/SPTicTacToeGUIManager.o: graphics/SPTicTacToeGUIManager.c graphics/SPTicTacToeGUIManager.h graphics/SPTicTacToeGameWin.c graphics/SPTicTacToeGameWin.h graphics/SPTicTacToeMainWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

clean:
	rm -f *.o $(EXEC) $(OBJS)
