#pragma once

clock_t ClockPerMs = CLOCKS_PER_SEC / 1000;

clock_t refTime;

void resetTime()
{
	refTime = clock();
}

ull elapsedTime()
{
	return (unsigned long long)((clock() - refTime)/ClockPerMs);
}
