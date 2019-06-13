#pragma once

TextBox *scoreLabel;

TextBox *scoreNum;

void initScore()
{
	scoreLabel = TB_create(SCALE*12+SCALE/4, SCALE*8+SCALE/4, "Score");
	scoreNum = TB_create(SCALE*12+SCALE/4, SCALE*10+SCALE/4, "12345");
}

void drawScore()
{
	TB_draw(scoreLabel);
	TB_draw(scoreNum);
}
