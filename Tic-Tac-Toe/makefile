CC = gcc
OBJS = main.o SPTicTacToe.o SPTicTacToeGUIManager.o SPTicTacToeGameWin.o SPTicTacToeMainWin.o  
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

COMP_FLAG = -std=c99 -Wall -Wextra -Werror $(SDL_CFLAGS) $(SDL_LDFLAGS)


$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
ttt: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

main.o: SPTicTacToeGUIManager.c SPTicTacToeGUIManager.h main.c  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPTicTacToe.o: SPTicTacToe.c SPTicTacToe.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPTicTacToeGameWin.o: SPTicTacToeWindow.h SPTicTacToe.c SPTicTacToe.h SPTicTacToeGameWin.h SPTicTacToeGameWin.c 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPTicTacToeGUIManager.o: SPTicTacToeGUIManager.c SPTicTacToeGUIManager.h SPTicTacToeGameWin.c SPTicTacToeGameWin.h SPTicTacToeMainWin.h SPTicTacToeMainWin.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPTicTacToeMainWin.o: SPTicTacToeMainWin.h SPTicTacToeMainWin.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(OBJS)
