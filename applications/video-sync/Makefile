CC = g++
INC := -I./include
DEBUG_FLAGS = -g -DDEBUG
CFLAGS = -Wall $(INC) -fPIC -std=c++11

OBJDIR := obj
BINDIR := bin
LIBDIR := lib

LDFLAGS := -L$(LIBDIR) -lm -lavutil -lavcodec 

BIN := $(BINDIR)/video-sync
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))


$(BIN): $(OBJS) 
	if [ ! -d $(BINDIR) ]; then \
		mkdir $(BINDIR); \
	fi 
	$(CC) -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: src/%.cpp
	if [ ! -d $(OBJDIR) ]; then \
		mkdir $(OBJDIR); \
	fi
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(BINDIR) $(LIBDIR) $(OBJDIR) data/fft_out.data

