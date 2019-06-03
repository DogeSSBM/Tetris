#include "Includes.h"

bool board[10][20] = {0};

// sets an x and y block within a 4x4 piece with 0,0 being the top left and 3,3 bottom right
bool getBlock(const uint x, const uint y, const piece p)
{
	uint16_t bit = (0b1 << 15) >> (x+(4*y));
	return p & bit;
}

// gets an x and y block within a 4x4 piece with 0,0 being the top left and 3,3 bottom right
void setBlock(const uint x, const uint y, piece *p, const bool isFilled)
{
	uint16_t bit = (0b1 << 15) >> (x+(4*y));
	if(isFilled)
		*p |= bit;
	else
		*p &= ~bit;
}

// fun code golf version of printPiece()
void printPiece2(const piece p)
{
	for(uint16_t i = 0; i < 16; i++){
		printf("%c%c",p & (0x8000u>>i) ? 'X' : '-', (i+1)%4 ? ' ' : '\n');
	}
}

// prints out a 4x4 ascii representation of a piece
void printPiece(const piece p)
{
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			putc(getBlock(x,y,p)?'X':'-',stdout);
		}
		putc('\n',stdout);
	}
	putc('\n',stdout);
}

// sets xbound to the leftmost filled block in p and ybound to the topmost filled block in p
void getMinBounds(uint *const xbound, uint *const ybound, const piece p)
{
	for(uint x = 0; x < 4; x++){
		for(uint y = 0; y < 4; y++){
			if(getBlock(x, y, p)){
				*xbound = x;
				goto escape;
			}
		}
	}
	escape:
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x, y, p)){
				*ybound = y;
				return;
			}
		}
	}
}

// sets xbound to the rightmost filled block in p and ybound to the bottommost filled block in p
void getMaxBounds(uint *const xbound, uint *const ybound, const piece p)
{
	for(uint x = 0; x < 4; x++){
		for(uint y = 0; y < 4; y++){
			if(getBlock(3-x, y, p)){
				*xbound = 3-x;
				goto escape;
			}
		}
	}
	escape:
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			if(getBlock(x, 3-y, p)){
				*ybound = 3-y;
				return;
			}
		}
	}
}

// returns piece moved as far up and left as possible
piece minAdjust(const piece p)
{
	uint xbound = 0;
	uint ybound = 0;
	getMinBounds(&xbound, &ybound, p);
	if(xbound == 0 && ybound == 0)
		return p;
	piece p2 = {0};
	for(uint y = 0; y+ybound < 4; y++){
		for(uint x = 0; x+xbound < 4; x++){
			setBlock(x, y, &p2, getBlock(x+xbound, y+ybound, p));
		}
	}
	return p2;
}

// returns piece moved as far down and right as possible
piece maxAdjust(const piece p)
{
	uint xbound = 0;
	uint ybound = 0;
	getMaxBounds(&xbound, &ybound, p);
	if(xbound == 3 && ybound == 3)
		return p;
	piece p2 = {0};
	for(uint y = 0; y+ybound < 4; y++){
		for(uint x = 0; x+xbound < 4; x++){
			setBlock(x+xbound, y+ybound, &p2, getBlock(x, y, p));
		}
	}
	return p2;
}

// rotates piece 90deg clockwise
piece rotateR(const piece p)
{
	piece p2 = {0};
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			setBlock(3-y,x,&p2,getBlock(x,y,p));
		}
	}
	//return p2;
	return minAdjust(p2);
}

// rotates piece 90deg counter-clockwise
piece rotateL(const piece p)
{
	piece p2 = {0};
	for(uint y = 0; y < 4; y++){
		for(uint x = 0; x < 4; x++){
			setBlock(y,3-x,&p2,getBlock(x,y,p));
		}
	}
	//return p2;
	return minAdjust(p2);
}

// checks if piece is within board bounds and for collision with any blocks on board
// piece must be minAdjust
bool fits(uint x, uint y, const piece p)
{
	uint xbound = 0, ybound = 0;
	getMaxBounds(&xbound, &ybound, p);
	if(x+xbound >= 10 || y+ybound >= 20)
		return false;
	for(uint xrel = 0; xrel <= xbound; xrel++){
		for(uint yrel = 0; yrel <= ybound; yrel++){
			if(getBlock(xrel, yrel, p) && board[x+xrel][y+yrel])
				return false;
		}
	}
	return true;
}

void printBoard()
{
	for(uint y = 0; y < 20; y++){
		for(uint x = 0; x < 10; x++){
			putc(board[x][y]?'X':'-', stdout);
		}
		putc('\n', stdout);
	}
	putc('\n', stdout);
}

void placePiece(uint xpos, uint ypos, piece p)
{
	uint xmax = 0, ymax = 0;
	getMaxBounds(&xmax, &ymax, p);
	for(uint x = 0; x <= xmax; x++){
		for(uint y = 0; y <= ymax; y++){
			if(getBlock(x,y,p))
				board[xpos+x][ypos+y] = true;
		}
	}
}

void removePiece(uint xpos, uint ypos, piece p)
{
	uint xmax = 0, ymax = 0;
	getMaxBounds(&xmax, &ymax, p);
	for(uint x = 0; x <= xmax; x++){
		for(uint y = 0; y <= ymax; y++){
			if(getBlock(x,y,p))
				board[xpos+x][ypos+y] = false;
		}
	}
}

bool fall(uint x, uint y, piece p)
{

}

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
	const piece pieces[] = {PIECE0, PIECE1, PIECE2, PIECE3, PIECE4, PIECE5, PIECE6};

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
			if(fits(x,y-1,p)){
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
			if(fits(x-1,y,p)){
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
