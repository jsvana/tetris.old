CC=clang++
PROG=tetris
OBJS=main.o tetromino.o screens/main_screen.o shader.o screen.o
LIBS=glfw3 glew
CXXFLAGS=-ggdb -std=c++11 -stdlib=libc++ $(shell pkg-config --cflags ${LIBS})
LDFLAGS=$(shell pkg-config --static --libs ${LIBS}) -framework OpenAL -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDFLAGS) $(CFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(TEST_PROG) $(OBJS) $(TEST_OBJS)
