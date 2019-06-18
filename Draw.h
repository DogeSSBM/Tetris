#pragma once

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

void drawScore()
{
	TB_draw(scoreLabel);
	TB_draw(scoreNum);
}

void drawAll(uint pieceX, uint pieceY, piece p, piece n)
{
	drawWalls();
	drawBoard();
	drawPiece(pieceX + 1, pieceY, p);
	drawNext(n);
	drawScore();
	draw();
}
