CC = g++
INC := -I./include
DEBUG_FLAGS = -g -DDEBUG
#CFLAGS = -Wall -Werror $(INC) -fPIC
CFLAGS = $(INC) -std=c++11  -Wall -Wconversion -O3 -fPIC -fopenmp -DCV_OMP

OBJDIR := obj
BINDIR := bin
LIBDIR := lib

LDFLAGS := -L$(LIBDIR) -llinear lib/blas.a

BIN := $(BINDIR)/stock-market
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))

#LIBS = src/blas/blas.a


$(BIN): $(OBJS)  
	if [ ! -d $(BINDIR) ]; then \
		mkdir $(BINDIR); \
	fi 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

src/blas/blas.a: src/blas/*.c src/blas/*.h
	make -C src/blas OPTFLAGS='$(CFLAGS)' CC='$(CC)';

$(OBJDIR)/%.o: src/%.cpp
	if [ ! -d $(OBJDIR) ]; then \
		mkdir $(OBJDIR); \
	fi
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(BINDIR) $(OBJDIR) data/lrout.data data/bsout.data

