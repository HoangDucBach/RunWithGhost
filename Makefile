OBJS = Background.cpp Boss.cpp Complete.cpp Character.cpp Function.cpp Game.cpp Home.cpp main.cpp Object.cpp Settings.cpp Tutorial.cpp Widgets.cpp
CC = g++
INCLUDE_PATHS = -IC:/Include
LIBRARY_PATHS = -LC:/Library
COMPILER_FLAGS = -w 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ_NAME = RunWithGhost.exe

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)