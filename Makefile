CC =g++
LIBS = `pkg-config --cflags --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`
LIBS_WIN = -I/d/msys/mingw64/include -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro
FLAGS = -lpthread -Wall -g -lm
BIN = bin/out
BIN_WIN = bin/out.exe
SOURCE = src/main.cpp src/Menu.cpp src/Game.cpp src/Projectile.cpp src/Word.cpp src/Words.cpp src/GameObject.cpp src/Projectiles.cpp src/Scores.cpp

all:
	$(CC) $(SOURCE) $(FLAGS) $(LIBS) -o $(BIN)
