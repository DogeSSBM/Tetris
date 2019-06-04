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
