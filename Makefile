# Makefile pour le jeu de dames avec SDL

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL2 -lSDL2_ttf -lm
OBJECTS = main_sdl.o initialisation.o validation.o mouvement.o fin_partie.o interface_sdl.o
TARGET = jeu_de_dames_sdl

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

main_sdl.o: main_sdl.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c main_sdl.c

initialisation.o: initialisation.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c initialisation.c

validation.o: validation.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c validation.c

mouvement.o: mouvement.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c mouvement.c

fin_partie.o: fin_partie.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c fin_partie.c

interface_sdl.o: interface_sdl.c jeu_de_dames.h
	$(CC) $(CFLAGS) -c interface_sdl.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean