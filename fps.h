#include <time.h>
#include <iostream>

class Fps
{
double frames;
time_t startTime;
time_t endTime;

public:
void reset();
void update();
};
