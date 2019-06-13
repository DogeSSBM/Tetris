#pragma once

TextBox *scoreLabel;
TextBox *scoreNum;
uint rawScore = 0;
char scoreText[] = "00000";

void setScore(uint s)
{
	intToStr(scoreText, s);
	TB_setText(scoreNum, scoreText);
}

void initScore()
{
	scoreLabel = TB_create(SCALE*12+SCALE/4, SCALE*8+SCALE/4, "Score");
	scoreNum = TB_create(SCALE*12+SCALE/4, SCALE*10+SCALE/4, "12345");
	setScore(12821);
}

void drawScore()
{
	TB_draw(scoreLabel);
	TB_draw(scoreNum);
}
