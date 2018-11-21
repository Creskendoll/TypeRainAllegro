CC = g++
FLAGS = -lpthread -Wall -g `pkg-config --cflags --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5` -lm
BIN = out
SOURCE = main.cpp Menu.cpp Game.cpp Projectile.cpp Word.cpp Words.cpp GameObject.cpp Projectiles.cpp 

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)