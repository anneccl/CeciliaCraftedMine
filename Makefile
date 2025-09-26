SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
BINFILE = ./main.exe
CC = g++

COMPILER_FLAGS = -I/usr/X11R6/include -I/usr/local/include -I/opt/homebrew/Cellar/raylib/5.0/include -finline-functions -std=c++17
LINKER_FLAGS = -lm -L/usr/X11R6/lib -L/usr/local/lib -L/opt/homebrew/Cellar/raylib/5.0/lib -lpthread -lraylib

# Release:
#CFLAGS = -O3 -fomit-frame-pointer -ffast-math -w $(COMPILER_FLAGS)
#LFLAGS = $(LINKER_FLAGS)

# Debug:
CFLAGS = -g -W -Wall $(COMPILER_FLAGS) -Wno-write-strings -Wno-unused-parameter -Wno-switch -Wno-reorder -Wno-missing-field-initializers -Wno-deprecated-copy -DDEBUGMODE -DDEBUG
LFLAGS = $(LINKER_FLAGS)

all : $(BINFILE)

$(BINFILE) : $(OBJS)
	@$(CC) $(OBJS) -o $(BINFILE) $(LFLAGS)

%.o : %.cpp
	@echo CC $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f Makefile.bak
	@rm -f $(OBJS)
	@rm -f $(BINFILE)
	@rm -rf ./out/

depend:
	@$(CC) -MM $(CFLAGS) $(SRCS) > Makefile.dep

info:
	@echo SRCS: $(SRCS)
	@echo OBJS: $(OBJS)
	@echo $(BINFILE)


include Makefile.dep

