BIN_PATH=./bin/
CXXFLAGS=-std=c++11 -g -lSDL -lSDL_image
#CXXFLAGS=-I./src/game/ -I./src/gameplay/ -I./src/graphics/ -I./src/scene/ \
#		 -I./src/surface -I./src/physics/ -I./src/input/ -I./src/entity/ \
#		 -I./src/misc/
VPATH=./src/game:./src/gameplay:./src/surface:./src/input:\
	  ./src/entity:./src/graphics:./src/physics:./src/scene

objs= entity.o game.o camera.o graphics.o sprite.o command.o input.o\
		physics.o scene.o background.o physicalspace.o surface.o gameplay.o

all: $(objs) main.o
	g++ -o ./bin/naivegame main.o  $(objs) $(CXXFLAGS) 

main.o: ./src/main.cpp
	g++ -c $(CXXFLAGS) -o main.o ./src/main.cpp
