#ifndef NAGYHAZI_GRAFIKA_H
#define NAGYHAZI_GRAFIKA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "enum.h"
#include "lancolt_lista.h"

void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

void alaprajz(SDL_Renderer *renderer);

void kepbetoltes(SDL_Renderer *renderer, SDL_Texture **babukep, SDL_Texture **mentesgomb, SDL_Texture **visszagomb);

void gombrajz(SDL_Renderer *renderer, SDL_Texture *gomb, int x, int y);

void vbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y);

void sbabu_rajzol(SDL_Renderer *renderer, SDL_Texture *babukep, Babukkoddal melyik, int x, int y);

void menu(SDL_Renderer *renderer);

SDL_Point kattintas(SDL_Renderer *renderer, Lista *u);

SDL_Point menu_kattintas(SDL_Renderer *renderer);

int grafikailepes(SDL_Renderer *renderer, SDL_Texture *babukep, SDL_Texture *gomb, SDL_Texture *vissza, FILE *fajl, Babuk fuggvenytabla[8][8], bool *feher_kov, Lista **u);

void betoltott_kirajz(SDL_Renderer *renderer, Babuk ftabla[8][8], SDL_Texture *babukep, SDL_Texture *gomb, SDL_Texture *vissza);

void kiszinez(SDL_Renderer *renderer, SDL_Point katt, bool fekete);

#endif //NAGYHAZI_GRAFIKA_H
