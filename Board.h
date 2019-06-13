#pragma once

bool board[10][20] = {0};

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

bool lineFull(uint y)
{
	for(uint x = 0; x < 10; x++){
		if(!board[x][y])
			return false;
	}
	return true;
}

void copyAbove(uint y)
{
	if(y == 0){
		for(uint x = 0; x < 10; x++){
			board[x][0] = false;
		}
	}
	else{
		for(uint x = 0; x < 10; x++){
			board[x][y] = board[x][y-1];
		}
	}
}

void removeLine(uint starty)
{
	for(int y = starty; y >= 0; y--){
		copyAbove(y);
	}
}

bool checkLines()
{
	for(uint y = 0; y < 20; y++){
		if(lineFull(19-y)){
			printf("line %u full, removing\n", 19-y);
			removeLine(19-y);
			return true;
		}
	}
	return false;
}
