#pragma once

struct{
	uint xlen, ylen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	int fontSize;
	Color fontColor;
	Color defaultColor;
}gfx = {};

void delay(uint ms)
{
	SDL_Delay(ms);
}

void drawPixel(uint x, uint y)
{
	SDL_RenderDrawPoint(gfx.renderer, x, y);
}

void drawLine(uint x1, uint y1, uint x2, uint y2)
{
	SDL_RenderDrawLine(gfx.renderer, x1, y1, x2, y2);
}

void drawHLine(uint x, uint y, int len)
{
	SDL_RenderDrawLine(gfx.renderer, x, y, x+len, y);
}

void drawVLine(uint x, uint y, int len)
{
	SDL_RenderDrawLine(gfx.renderer, x, y, x, y+len);
}

void drawRect(uint x, uint y, uint xlen, uint ylen)
{
	Rect r = {x, y, xlen, ylen};
	SDL_RenderDrawRect(gfx.renderer, &r);
}

void fillRect(uint x, uint y, uint xlen, uint ylen)
{
	Rect r = {x, y, xlen, ylen};
	SDL_RenderFillRect(gfx.renderer, &r);
}

void fillBorder(uint x, uint y, uint xlen, uint ylen, int b)
{
	fillRect(x-b, y-b, xlen+2*b, b);
	fillRect(x-b, y+ylen, xlen+2*b, b);
	fillRect(x-b, y, b, ylen);
	fillRect(x+xlen, y, b, ylen);
}

void setColor(Color c)
{
	SDL_SetRenderDrawColor(gfx.renderer, c.r, c.g, c.b, c.a);
}

void setRGB(u8 r, u8 g, u8 b)
{
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, 255);
}

void setRGBA(u8 r, u8 g, u8 b, u8 a)
{
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, a);
}

void clear()
{
	setColor(BLACK);
	SDL_RenderClear(gfx.renderer);
	fillRect(0,0,gfx.xlen,gfx.ylen);
}

void draw()
{
	SDL_RenderPresent(gfx.renderer);
}

void drawText(uint x, uint y, const char *text)
{
	Rect r;
	r.x = x; r.y = y;
	SDL_Surface *surface = TTF_RenderText_Solid(gfx.font, text, gfx.fontColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(gfx.renderer, texture, NULL, &r);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

typedef struct{
	char* text;
	Rect r;
	int size;
	Color textColor;
	Color backColor;
}TextBox;

void setFontSize(int size)
{
	if(size != gfx.fontSize){
		if(gfx.font != NULL){
			TTF_CloseFont(gfx.font);
		}
		gfx.fontSize = size;
		gfx.font = TTF_OpenFont("./LiberationMono.ttf", gfx.fontSize);
	}
}

void TB_setText(TextBox *tb, const char *text)
{
	size_t size = sizeof(char)*strlen(text)+1;
	tb->text = malloc(size);
	memset(tb->text, '\0', size);
	memcpy(tb->text, text, size);
}

void TB_setTextSize(TextBox *tb, int size)
{
	tb->size = size;
}

TextBox* TB_create(uint x, uint y, const char* text)
{
	TextBox *tb = malloc(sizeof(TextBox));
	TB_setText(tb, text);
	tb->r.x = x;
	tb->r.y = y;
	tb->backColor = BLACK;
	tb->textColor = GREY;
	tb->size = 48;
	return tb;
}

void TB_destroy(TextBox *tb)
{
	if(tb){
		if(tb->text){
			free(tb->text);
		}
		free(tb);
	}
}

void TB_draw(TextBox *tb)
{
	setFontSize(tb->size);
	SDL_Surface *surface = TTF_RenderText_Solid(
		gfx.font, tb->text, tb->textColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(
		gfx.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &(tb->r.w), &(tb->r.h));
	setColor(tb->backColor);
	SDL_RenderFillRect(gfx.renderer, &(tb->r));
	SDL_RenderCopy(gfx.renderer, texture, NULL, &(tb->r));
	setColor(tb->textColor);
	// SDL_RenderDrawRect(gfx.renderer, &(tb->r));
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void gfx_quit()
{
	// Destroy renderer
	SDL_DestroyRenderer(gfx.renderer);
	// Destroy window
	SDL_DestroyWindow(gfx.window);
	// Quit SDL subsystems
	SDL_Quit();
}

void TB_quit()
{
	if(gfx.font != NULL){
		TTF_CloseFont(gfx.font);
	}
	TTF_Quit();
}

void gfx_init(uint winXlen, uint winYlen)
{
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL borked! Error: %s\n", SDL_GetError());
		exit(0);
	}
	else{
		//Create window
		SDL_CreateWindowAndRenderer(winXlen, winYlen, 0,
			&(gfx.window), &(gfx.renderer));
		printf("Adding gfx_quit to atexit()\n");
		atexit(gfx_quit);
		gfx.xlen = winXlen;
		gfx.ylen = winYlen;
		gfx.defaultColor = BLACK;
		if (TTF_Init()){
			printf("SDL_ttf borked! Error: %s\n", TTF_GetError());
			exit(0);

		}
		SDL_SetRenderDrawBlendMode(gfx.renderer, SDL_BLENDMODE_NONE);
		gfx.fontColor = WHITE;
		setFontSize(16);
		if(!gfx.font){
			printf("SDL_ttf borked font! Error: %s\n", TTF_GetError());
			exit(0);
		}
		printf("adding TB_quit to atexit()\n");
		atexit(TB_quit);
		clear();
		draw();
		clear();
		printf("Done!\n");
	}
}
