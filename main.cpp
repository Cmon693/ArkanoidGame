//czysty

#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_main.h>
#include "header.h"
using namespace std;

  int SCREEN_WIDTH = 640;
  int SCREEN_HEIGHT = 480;
  int dlPaletki = 140;
  int srPilki = 9;
  double speed = 0.15;

int lewyBok;
int prawyBok;
int gornyBok;
int dolnyBok;
  


  int CHAR_WIDTH = 8;
  int CHAR_HEIGHT = 8;
  int t1, t2;
  double delta, delta100, deltaP, worldTime;

  double odstep = 0;
  double xp = SCREEN_WIDTH/2 + odstep;
	double yp = SCREEN_HEIGHT - 40-srPilki;
	double xw = 1;
	double yw = -1;
	double win;
	int start = 0;
	int wynik = 0.0;
	int leci = 0;
	double polozenie;
	double pozZycia = 3.0;
	int kleista;
	double odlicznie = 20.0;
	int licz;
	int ok = 1;
	



// =======================================================================
int main(int argc, char **argv) 
{
	

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                     &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		std::cout << "SDL_CreateWindowAndRenderer error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Jakub Szymanski 155210");


	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                                           0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_Texture *scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                                        SDL_TEXTUREACCESS_STREAMING,
	                                        SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie kursora 
	SDL_ShowCursor(SDL_DISABLE);

	SDL_Surface *charset = SDL_LoadBMP("cs8x8.bmp");
	if(charset == NULL) {
		std::cout << "SDL_LoadBMP(cs8x8.bmp) error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	SDL_SetColorKey(charset, true, 0x000000);

	SDL_Surface *pilka = SDL_LoadBMP("pilka.bmp");
	if (pilka == NULL) {
		std::cout << "SDL_LoadBMP(pilka.bmp) error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);	

	int frames = 0;
	double fpsTimer = 0;
	double fps = 0;
	//int gameStartTime = SDL_GetTicks();
	worldTime = 0;
	double etiSpeed = 1;
	
	double distance = 0;
	double distance0 = 0;		
	
	wczytaj ();	

	//===============================================================
	t1 = SDL_GetTicks();
	bool quit = false;
	while (!quit) 
	{
		polozenie = SCREEN_WIDTH/2 - dlPaletki/2 + odstep;
		lewyBok = xp - srPilki;
		prawyBok = xp + srPilki;
		gornyBok = yp - srPilki;
		dolnyBok = yp + srPilki;		

		t2 = SDL_GetTicks();
		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		deltaP = (t2 - t1) * 0.9;
		delta100 = (t2 - t1) * speed;
		t1 = t2;
		worldTime += delta;

		if (licz == 1) 
		{
			odlicznie -= delta; 
			if (frandom == 1) dlPaletki = 260;
			if (frandom == 4) speed = 0.1;
		}
		if (odlicznie < 0) 
		{
			licz = 0;
			odlicznie = 20.0;
			dlPaletki = 140;
			speed = 0.15;
		}

		distance += etiSpeed * delta;

		SDL_FillRect(screen, NULL, black);

		// tekst informacyjny		
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, blue);
		char text[128];
		if (pozZycia == 0) 
		{
				sprintf(text, "KONIEC GRY! esc -> wyjscie   s -> nowa gra");
				DrawStringCentered(screen, screen->w / 2, 14, text, charset);
				start = 0;	
				speed = 0.15;
				xp = SCREEN_WIDTH/2 + odstep;
				yp = SCREEN_HEIGHT - 40-srPilki;
				wczytaj();
				leci = 0;
		}
		else if (ok == 0) 
		{
				sprintf(text, "ZWYCIESTWO! esc -> wyjscie   s -> nowa gra");
				DrawStringCentered(screen, screen->w / 2, 14, text, charset);
				start = 0;	
				speed = 0.15;
				xp = SCREEN_WIDTH/2 + odstep;
				yp = SCREEN_HEIGHT - 40-srPilki;
				wczytaj ();
				leci = 0;
		}
		else
		{
		sprintf(text, "Wynik: %d , Zycia: %.0lf, BONUS: %.1lf s", wynik, pozZycia, odlicznie);
		DrawStringCentered(screen, screen->w / 2, 14, text, charset);
		sprintf(text, "Esc - wyjscie, \032 - przesun w lewo, \033 - przesun w prawo");
		DrawStringCentered(screen, screen->w / 2, 30, text, charset);
		}		

		//PLANSZA
		DrawRectangle(screen, 10, 50, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 60, red, NULL);
		//PALETKA
		DrawRectangle(screen, polozenie, SCREEN_HEIGHT - 40, dlPaletki, 10, red, green);

		win = 1.0;
		rysujCegle (screen, 'A', blue, red);
		rysujCegle (screen, 'B', blue, green);
		rysujCegle (screen, 'C', green, blue);
		rysujCegle (screen, 'D', red, black); //niezniszczalna
		if (win == 1) 
		{
			start = 0;
			ok = 0;
		}
		
		//odbiecie od paletki
		if (dolnyBok > SCREEN_HEIGHT - 40 && xp > polozenie  && xp < polozenie + dlPaletki) 
		{
			if (kleista == 1) start = 0;
			yw=-(yw*yw);
		}

		//odbicie od scian
		if (prawyBok > SCREEN_WIDTH - 10) xw = -xw;
		if (lewyBok < 10) xw = -xw;
		if (gornyBok < 50) yw = -yw;
		//przegrana
		if (dolnyBok > SCREEN_HEIGHT - 10) 
		{			
			pozZycia--;
			odstep = 0;
			xp = SCREEN_WIDTH/2 + odstep;
			yp = SCREEN_HEIGHT - 40-srPilki;
			start = 0;
			speed = 0.15;
			yw = -(yw*yw);
		}

		if (start == 1)
		{
		xp += xw * delta100;
		yp += yw * delta100;		
		//przyspieszenie
		if (speed < 0.25) speed += 0.00005;
		}
		//PILKA
		DrawSurface(screen, pilka, xp, yp); 

		if (leci == 1) 
		{
				nagroda(screen, blue, blue);
		}

		fpsTimer += delta;
		if (fpsTimer > 0.5) 
		{
			fps = frames * 2 - 0.5;
			frames = 0;
			fpsTimer -= 0.5;
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				case 's':
					start = 1;
					kleista = 0;
					if (pozZycia == 0) {
						pozZycia = 3;
						wynik = 0;
					}
					if (ok == 0) 
					{
						ok = 1;
						wynik = 0;
						pozZycia = 3;
					}
					break;
				case SDLK_LEFT:
					if (polozenie > 10) odstep = odstep - 10;
					if (start == 0 && polozenie > 10) xp -= 10;
					//if (polozenie > 10) odstep = odstep - deltaP;
					//if (start == 0 && polozenie > 10) xp -= deltaP;
					break;
				case SDLK_RIGHT:
					if (polozenie < SCREEN_WIDTH - dlPaletki - 10) odstep = odstep + 10;
					if (start == 0 && polozenie < SCREEN_WIDTH - dlPaletki - 10) xp += 10;
					//if (polozenie < SCREEN_WIDTH - dlPaletki - 10) odstep = odstep + deltaP;
					//if (start == 0 && polozenie < SCREEN_WIDTH - dlPaletki - 10) xp += deltaP;
					break;
				}
				break;
			case SDL_KEYUP:
				etiSpeed = 1.0;
				break;
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		frames++;
	}

	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}