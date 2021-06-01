#include "jfGL.h"
#include "Timing.h"

int main(int argc, char **argv)
{
	Timing timing;

	while (1)
	{
		char strBuffer[64];
		sprintf(strBuffer, "%f %f FPS", timing.dt(), timing.getFps());
		std::cout << strBuffer << std::endl;
		timing.Reset();
	}
	return 0;
}
