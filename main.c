#define SCALE 32
#define GAP 2
#include "Includes.h"

void loose()
{
	printf("Next piece doesnt fit, you loose!\n");
	while(1){
		events();
		delay(5);
	}
}

int main(int argc, char const *argv[])
{
	static event e = NOTHING;
	gfx_init(SCALE*(12+6), SCALE*21);
	initScore();
	const uint xorig = 3, yorig = 0;
	uint x = xorig, y = yorig;
	piece p = pieces[rand()%NUMPIECES];
	piece n = pieces[rand()%NUMPIECES];
	uint linesCleared = 0;
	static uint level = 0;
	static uint levelLinesCleared = 0;
	static ull levelTime = 1000ull;
    clear();
	drawAll(x,y,p,n);
	resetTime();
	while(1){
		if(elapsedTime() >= levelTime)
			e = MOVE_D;
		else
			e = events();
		switch (e){
		case MOVE_U:
			printf("Move U\n");
			if(y>0 && fits(x,y-1,p)){
				y--;
			}
			break;
		case MOVE_L:
			printf("Move L\n");
			if(x>0 && fits(x-1,y,p)){
				x--;
			}
			break;
		case MOVE_R:
			printf("Move R\n");
			if(fits(x+1,y,p)){
				x++;
			}
			break;
		case ROTATE_L:
			printf("Rotate L\n");
			if(fits(x,y,rotateL(p))){
				p = rotateL(p);
			}
			break;
		case ROTATE_R:
			printf("Rotate R\n");
			if(fits(x,y,rotateR(p))){
				p = rotateR(p);
			}
			break;
		case MOVE_D:
			printf("Move D\n");
			resetTime();
			if(fits(x,y+1,p)){
				y++;
				break;
			}
		case PLACE:
			printf("Place\n");
			placePiece(x,y,p);
			x = xorig, y = yorig;
			p = n;
			n = pieces[rand()%NUMPIECES];
			linesCleared = 0;
			while(checkLines()){
				linesCleared++;
			}
			if(linesCleared > 0){
				printf("%u lines cleared\n", linesCleared);
				rawScore += linesCleared;
				intToStr(rawScore, scoreText);
				TB_setText(scoreNum, scoreText);
				levelLinesCleared += linesCleared;
			}
			if(!fits(x,y,p)){
				loose();
			}
			break;
		case NOTHING:
			break;
		default:
			printf("Unknown event\n");
			break;
		}
		if(levelLinesCleared >= 5){
			level++;
			printf("5+ lines cleared, advancing to level %u\n", level);
			levelTime = levelTime > 100? levelTime - 100 : 50;
			printf("level time %llu\n", levelTime);
			levelLinesCleared = 0;
		}
		drawAll(x,y,p,n);
	}
	return 0;
}
