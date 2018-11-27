CC =g++
LIBS = `pkg-config --cflags --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`
LIBS_WIN = -I/d/msys/mingw64/include -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro
FLAGS = -lpthread -Wall -g -lm
BIN = out
BIN_WIN = out.exe
SOURCE = main.cpp Menu.cpp Game.cpp Projectile.cpp Word.cpp Words.cpp GameObject.cpp Projectiles.cpp 

all:
	$(CC) $(SOURCE) $(FLAGS) $(LIBS) -o $(BIN)
