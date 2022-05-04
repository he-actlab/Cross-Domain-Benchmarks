CC := gcc
INC := -I./include
MATRIX_DIR = ./include/meschach_lib
CCFLAGS := -g -O3 -Wall -fopenmp -I$(MATRIX_DIR) $(INC)

OBJDIR := obj
BINDIR := bin
LIBDIR := -L./lib

LDFLAGS := $(LIBDIR) -lm -lpthread -lavilib lib/meschach.a
BIN := $(BINDIR)/leukocyte

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))

override OUTPUT = -DOUTPUT

all: $(BIN) 

$(BIN): $(OBJS) 
	if [ ! -d $(BINDIR) ]; then \
		mkdir $(BINDIR); \
	fi 
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: src/%.c 
	if [ ! -d $(OBJDIR) ]; then \
		mkdir $(OBJDIR); \
	fi
	$(CC) $(OUTPUT) $(CCFLAGS) -c $^ -o $@

$(MATRIX_DIR)/meschach.a:
	cd $(MATRIX_DIR); ./configure --with-all; make all; make clean

clean:
	rm -rf $(BINDIR) $(OBJDIR) 
