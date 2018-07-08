#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_main.h>
#include "header.h"
#include <cstdlib>
#include <ctime>

char tab [11][10];
char nazwa;
int random;
int frandom;
int x;
int y;
int dol = 0;
int currX;
int currY;


SDL_Surface *bonus;
SDL_Surface *dluga = SDL_LoadBMP("dlugaPaletka.bmp");
SDL_Surface *zycie = SDL_LoadBMP("dodatkowaRozgrywka.bmp");
SDL_Surface *klPal = SDL_LoadBMP("kleistaPaletka.bmp");
SDL_Surface *wolno = SDL_LoadBMP("zmianaTempa.bmp");


void nagroda (SDL_Surface *screen, Uint32 outlineColor, Uint32 fillColor)
{	
	dol ++;
	if (frandom == 1) bonus = dluga;
	if (frandom == 2) bonus = zycie;
	if (frandom == 3) bonus = klPal;
	if (frandom == 4) bonus = wolno;

	DrawSurface(screen, bonus, 11 + currX*62 + 30, 55 + currY*32 + dol); 

	if (55 + currY*32 + dol > SCREEN_HEIGHT - 40 &&
		11 + currX*62 > polozenie  && 11 + currX*62 < polozenie + dlPaletki) 
	{
		if (frandom == 1) dlugaPaletka ();
		if (frandom == 2) dodatkowaRozgrywka();
		if (frandom == 3) kleistaPaletka ();
		if (frandom == 4) zmianaTempa ();		
		leci = 0;
		dol = 0;
	}
	if (55 + currY*32 + dol > SCREEN_HEIGHT - 10) 
	{
		leci = 0;
		dol = 0;
	}
}

void dlugaPaletka ()
{
	licz = 1;
	odlicznie = 20.0;
	wynik += 100;
}

void zmianaTempa ()
{
	licz = 1;
	odlicznie = 20.0;
	wynik += 100;
}

void kleistaPaletka ()
{
	kleista = 1;
	wynik += 100;
}

void dodatkowaRozgrywka()
{
	pozZycia++;
	wynik += 100;
}

void wczytaj ()
{
	FILE *plik; 
	plik = fopen ("mapa.txt","r"); 

	for(int j = 0; j < 10; j++)
	{
		for(int i = 0; i < 11; i++)
		{
			tab[i][j] = fgetc(plik); 
		}
	}
	fclose(plik);	
}


void rysujCegle (SDL_Surface *screen, char nazwa, Uint32 outlineColor, Uint32 fillColor)
{
	int kontakt;
	int lCegla, pCegla, gCegla, dCegla; // krawedzie cegly
	for (y = 0; y < 10; y++) //kolumna
	{		
		for (x = 0; x < 10; x++) //wiersz
		{	
			lCegla = 11 + x*62; 
			pCegla = 11 + x*62 + 60;
			dCegla = 55 + y*32 + 30;
			gCegla = 55 + y*32;

			if (tab[x][y] == nazwa) 
			{			
				DrawRectangle(screen, 11 + x*62, 55 + y*32, 60, 30, outlineColor, fillColor);
				if (nazwa != 'D') win = 0.0;
				kontakt = 0;	
				//dany klocek
				if (gornyBok < 55 + y*32 + 30 && dolnyBok > 55 + y*32 &&
					prawyBok > 11 + x*62 && lewyBok < 11 + x*62 + 60) ///				
				{
					//gora
					if (yw == -1)
					{
						if (gornyBok <= dCegla && dolnyBok >= dCegla &&
							prawyBok >= lCegla && lewyBok <= pCegla) yw=-yw;
						else if (xw == 1)//-prawo
						{
							if (prawyBok >= lCegla && lewyBok <= lCegla &&
								gornyBok <= dCegla && dolnyBok >= gCegla) xw=-xw;	
						}
						else if (xw == -1)//-lewo
						{
							if (lewyBok <= pCegla && prawyBok >= pCegla &&
								gornyBok <= dCegla && dolnyBok >= gCegla) xw=-xw;
						}
					}					
					//dol
					else if ( yw == 1)
					{
						if (gornyBok <= gCegla && dolnyBok >= gCegla &&
							prawyBok >= lCegla && lewyBok <= pCegla) yw=-yw;
						if (xw == 1)//-prawo
						{
							if (prawyBok >= lCegla && lewyBok <= lCegla &&
								gornyBok <= dCegla && dolnyBok >= gCegla) xw=-xw;
						}
						else if (xw == -1)//lewo
						{
							if (lewyBok <= pCegla && prawyBok >= pCegla &&
								gornyBok <= dCegla && dolnyBok >= gCegla) xw=-xw;
						}
					}

					
						if (nazwa != 'D') 
						{
							tab[x][y] = '.';
							wynik += 25;
						}

						srand(time(NULL));
						random =( std::rand() % 3 ) + 1;
						if (random == 2 && nazwa != 'D') 
						{
							if (leci != 1)
							{
								srand(time(NULL));
								frandom =( std::rand() % 4 ) + 1;
								currX = x ;
								currY = y ;
								leci = 1;
							}
							else leci = 1;
						}					
				}
			}
		}
	}	
}



// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface *surface, int x, int y, const char *text, SDL_Surface *charset) 
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * CHAR_WIDTH;
		py = (c / 16) * CHAR_HEIGHT;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, surface, &d);
		x += 8;
		text++;
	}
}

void DrawStringCentered(SDL_Surface *surface, int x_center, int y_center, const char *text, SDL_Surface *charset) 
{
	DrawString(surface,
	           x_center - (strlen(text) * CHAR_WIDTH / 2),
	           y_center - (CHAR_HEIGHT / 2),
	           text, charset);
}

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *surface, SDL_Surface *sprite, int x, int y) 
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, surface, &dest);
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) 
{
	// Should we use SDL_LockSurface?
	Uint8 *pixel = (Uint8 *) surface->pixels
		+ y * surface->pitch
		+ x * surface->format->BytesPerPixel;
	*(Uint32 *) pixel = color;
}

// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1)
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) 
{
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) 
{
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (int i = y + 1; i < y + k - 1; i++) {
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	} 
}