#define SCALE 32
#define GAP 2
#include "Includes.h"

void printOptions()
{
	printf("Options:\n");
	const static char* options[] = {
/*0 */	"options",
/*1 */	"next piece",
/*2 */	"prev piece",
/*3 */	"rotateR",
/*4 */	"rotateL",
/*5 */	"moveD",
/*6 */	"moveU",
/*7 */	"moveL",
/*8 */	"moveR",
/*9 */	"place"
	};
	for(uint i = 0; i < 10; i++){
		printf("%u: %s\n", i, options[i]);
	}
}

void drawBlock(uint x, uint y)
{
	fillRect(SCALE*x+GAP, SCALE*y+GAP, SCALE-GAP*2, SCALE-GAP*2);
}

void drawWalls()
{
	setColor(WHITE);
	for(uint i = 0; i < 21; i++){
		// board walls
		drawBlock(0, i);
		drawBlock(11, i);
		// rightmost wall
		drawBlock(17, i);
	}

	for(uint i = 0; i < 12+6; i++){
		// floor
		drawBlock(i, 20);
	}

	for(uint i = 12; i < 12+5; i++){
		// next piece box
		drawBlock(i, 0);
		drawBlock(i, 7);
		// score bottom
		drawBlock(i, 12);
	}
}

void drawPiece(uint xpos, uint ypos, piece p)
{
	setColor(GREY);
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,p))
				drawBlock(xpos+x, ypos+y);
		}
	}
}

void drawNext(piece n)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x,y,n))
				setColor(GREY);
			else
				setColor(BLACK);
			drawBlock(13+x, 2+y);
		}
	}
}

void drawBoard()
{
	for(uint y = 0; y < 20; y++){
		for(uint x = 0; x < 10; x++){
			if(board[x][y]){
				setColor(GREY);
				drawBlock(x+1, y);
			}
			else{
				setColor(BLACK);
				drawBlock(x+1, y);
			}
		}
	}
}

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
	static event e = MOVE_D;
	gfx_init(SCALE*(12+6), SCALE*21);
	initScore();
	drawWalls();
	drawScore();
	draw();
	const uint xorig = 3, yorig = 0;
	uint x = xorig, y = yorig;
	piece p = pieces[rand()%NUMPIECES];
	piece n = pieces[rand()%NUMPIECES];
	drawPiece(x+1,y,p);
	uint linesCleared = 0;
	static uint level = 0;
	static uint levelLinesCleared = 0;
	static ull levelTime = 1000ull;
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
		drawWalls();
		drawBoard();
		drawPiece(x+1, y, p);
		drawNext(n);
		drawScore();
		draw();
	}
	return 0;
}

/*
int main(int argc, char const *argv[])
{
	const uint xorig = 3, yorig = 0;
	uint x = xorig, y = yorig;
	uint index = 0;
	piece p = pieces[index];
	placePiece(x,y,p);
	printOptions();
	printBoard();
	while(1){
		switch (getInt()) {
		case 1:
			removePiece(x,y,p);
			index = (index+1)%7;
			p = pieces[index];
			placePiece(x,y,p);
			break;
		case 2:
			removePiece(x,y,p);
			index = index>0?index-1:6;
			p = pieces[index];
			placePiece(x,y,p);
			break;
		case 3:
			removePiece(x,y,p);
			if(fits(x,y,rotateR(p))){
				p = rotateR(p);
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid rotation, doing nothing\n");
			}
			break;
		case 4:
			removePiece(x,y,p);
			if(fits(x,y,rotateL(p))){
				p = rotateL(p);
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid rotation, doing nothing\n");
			}
			break;
		case 5:
			removePiece(x,y,p);
			if(fits(x,y+1,p)){
				y++;
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid movement, doing nothing\n");
			}
			break;
		case 6:
			removePiece(x,y,p);
			if(y>0 && fits(x,y-1,p)){
				y--;
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid movement, doing nothing\n");
			}
			break;
		case 7:
			removePiece(x,y,p);
			if(x>0 && fits(x-1,y,p)){
				x--;
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid movement, doing nothing\n");
			}
			break;
		case 8:
			removePiece(x,y,p);
			if(fits(x+1,y,p)){
				x++;
				placePiece(x,y,p);
			}
			else{
				placePiece(x,y,p);
				puts("Invalid movement, doing nothing\n");
			}
			break;
		case 9:
			placePiece(x,y,p);
			x = xorig, y = yorig;
			placePiece(x,y,p);
			break;
		case 0:
		case 10:
		default:
			printOptions();
			break;
		}
		printOptions();
		printBoard();
	}
	return 0;
}
*/
