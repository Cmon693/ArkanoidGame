#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_main.h>


void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawSurface(SDL_Surface *surface, SDL_Surface *sprite, int x, int y);
void DrawStringCentered(SDL_Surface *surface, int x_center, int y_center, const char *text, SDL_Surface *charset);
void DrawString(SDL_Surface *surface, int x, int y, const char *text, SDL_Surface *charset);
//===
void wczytaj ();
void rysujCegle (SDL_Surface *screen, char nazwa, Uint32 outlineColor, Uint32 fillColor);
void nagroda (SDL_Surface *screen, Uint32 outlineColor, Uint32 fillColor);
void dodatkowaRozgrywka();
void kleistaPaletka ();
void zmianaTempa ();
void dlugaPaletka ();


extern  int SCREEN_WIDTH ;
extern  int SCREEN_HEIGHT;
extern   int dlPaletki ;
extern double xp;
extern double yp;
extern double xw;
extern double yw;

extern   int CHAR_WIDTH;
extern   int CHAR_HEIGHT;

extern int t1, t2;
extern double delta, delta100, worldTime;

extern char tab [11][10];

extern int black;
extern int red ;
extern int green; 
extern int blue ;

extern double win;
extern int start;
extern char nazwa;
extern int wynik;
extern int random;
extern int frandom;
extern int currX;
extern int currY;
extern int dol;
extern int leci;
extern double polozenie;
extern double pozZycia;
extern int kleista;
extern int licz;
extern double odlicznie;

extern int lewyBok;
extern int prawyBok;
extern int gornyBok;
extern int dolnyBok;