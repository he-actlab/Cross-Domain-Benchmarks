CC = gcc
INC := -I./include
DEBUG_FLAGS = -g -DDEBUG
CFLAGS = -Wall -Werror $(INC) -fPIC

OBJDIR := obj
BINDIR := bin
LIBDIR := lib

LDFLAGS := -L$(LIBDIR) -lm -lavutil -lavcodec 

#BIN := $(BINDIR)/security-camera
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))


$(LIBDIR)/libdecode.so: $(OBJS) 
	if [ ! -d $(LIBDIR) ]; then \
		mkdir $(LIBDIR); \
	fi 
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: src/%.c
	if [ ! -d $(OBJDIR) ]; then \
		mkdir $(OBJDIR); \
	fi
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(BINDIR) $(LIBDIR) $(OBJDIR)

