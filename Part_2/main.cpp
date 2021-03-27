#include <iostream>
#include <fstream>

#include "Entity.h"
#include "Profiler.h"

void runTest(int numEntities)
{
	Profiler &p = Profiler::getInstance();
	p.reset();

	Entity *entities = new Entity[numEntities];

	for (int frameCount = 0; frameCount < 1024; frameCount++)
	{
		gravityUpdate(0.013f, entities, numEntities);

		p.nextFrame();
	}

	delete[] entities;

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
