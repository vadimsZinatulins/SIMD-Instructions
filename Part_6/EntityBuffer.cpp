#include "EntityBuffer.h"

#include <random>


EntityBuffer::EntityBuffer(int numEntities)
{
	// Create an array of all x positions
	m_xs = new float[numEntities];
	// Create an array of all y positions
	m_ys = new float[numEntities];
	// Create an array of all healths
	m_healths = new float[numEntities];

	// Previously these were static variables but this time since
	// this constructor is only called once and all entities are generated 
	// here, there is no need to make these static anymore
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

	for (int i = 0; i < numEntities; i++)
	{
		// Generate random position for entity at index 'i'
		m_xs[i] = dist(e2);
		m_ys[i] = dist(e2);

		// Starting health is 100 for entity at index 'i'
		m_healths[i] = 100;

	}
}

EntityBuffer::~EntityBuffer()
{
	// Don't forget to free the memory
	delete[] m_xs;
	delete[] m_ys;
	delete[] m_healths;
}
