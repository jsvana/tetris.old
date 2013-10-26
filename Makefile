CC=clang++
PROG=tetris
OBJS=main.o screens/main_screen.o screen.o shader_manager.o palette_manager.o \
	objs/cube.o objs/tetromino.o
LIBS=glfw3 glew
CXXFLAGS=-g -std=c++11 -stdlib=libc++ $(shell pkg-config --cflags ${LIBS})
LDFLAGS=$(shell pkg-config --static --libs ${LIBS}) -framework OpenAL -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDFLAGS) $(CFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(TEST_PROG) $(OBJS) $(TEST_OBJS)
