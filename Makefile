OBJS= main.cpp Background.cpp Boss.cpp Character.cpp\
			Complete.cpp Function.cpp Game.cpp Home.cpp\
			main.cpp Object.cpp Settings.cpp Tutorial.cpp\
			Widgets.cpp
CC=g++
LIBFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer  -lSDL2_image -lSDL2_ttf 
INCLUDESDL2 = -IC:/Library/SDL2/include 
INCLUDEMIXER = -IC:/Library/SDL2_Mixer/include
INCLUDEIMG=-IC:/Library/SDL2_IMG/include
INCLUDETTF = -IC:/Library/SDL2_TTF/include
OBJSBUILD = RunWithGhost.exe

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDESDL2) $(INCLUDEMIXER) $(INCLUDEIMG)  $(INCLUDETTF) \
	-w $(LIBFLAGS) -o $(OBJSBUILD)