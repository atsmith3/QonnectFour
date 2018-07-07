CC=clang++
CFLAGS= -g -std=c++11 
OBJS= main.o game.o



program: $(OBJS)
	$(CC) $(CFLAGS) -v -lm -o program.exe $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f *.o output/* program.exe
