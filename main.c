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
