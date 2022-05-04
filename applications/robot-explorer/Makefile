CC			:= g++
LD			:= g++
CFLAGS		:= -Wall -std=c++11 -Wconversion -O3 -fPIC -fopenmp -DCV_OMP -ftree-vectorize -msse2 -march=native 
INCLUDE 	:= -I./include

OBJDIR := obj
BINDIR := bin
LIBDIR := -L./lib

LDFLAGS     := $(LIBDIR) -lcontrol -llapack -llapacke -lgfortran -lblas -lkernels
BIN := $(BINDIR)/robot-explorer

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))


.PHONY: all clean
	
all: DIR $(BIN)

DIR:
	@echo ${CPP_FILES}
	@echo ${OBJ_FILES}
	if [ ! -d "./bin" ];then 	\
		mkdir bin;				\
	fi
	if [ ! -d "./obj" ];then 	\
		mkdir obj;				\
	fi

$(BIN): $(OBJ_FILES)
	$(LD) $^ -o $@ $(CFLAGS)  $(LIBS) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf *.o
	@rm -rf *.d
	@rm -rf *.out
	@rm -rf bin
	@rm -rf obj
	rm -rf results.json
	rm -rf timing_results.txt
