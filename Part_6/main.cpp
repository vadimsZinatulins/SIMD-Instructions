#include <iostream>

#include "EntityBuffer.h"
#include "Explosion.h"
#include "Profiler.h"

void runTest(int numEntities)
{
	Profiler &p = Profiler::getInstance();
	p.reset();

	EntityBuffer entityBuffer(numEntities);
	Explosion explosion;

	for (int frameCount = 0; frameCount < 1024; frameCount++)
	{
		explosionUpdate(&explosion, &entityBuffer, numEntities);

		p.nextFrame();
	}

	std::cout << numEntities << "\t" << p.getSessionAverage() / 1000 << "\n";
}

int main(int argc, char *argv[])
{
	for (int i = 0; i < 8; i++)
	{
		runTest(1024 * (1 << i));
	}

	return 0;
}
