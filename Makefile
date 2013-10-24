CC=clang++
PROG=tetris
OBJS=main.o tetromino.o screens/main_screen.o shader.o matrix.o
CFLAGS=-ggdb -stdlib=libc++ -std=c++0x $(shell pkg-config --cflags glfw3 glew gsl)
LDFLAGS=$(shell pkg-config --static --libs glfw3 glew gsl) -framework OpenAL -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDFLAGS) $(CFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(TEST_PROG) $(OBJS) $(TEST_OBJS)
