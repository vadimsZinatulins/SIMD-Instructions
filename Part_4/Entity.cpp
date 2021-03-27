#include "Entity.h"
#include "Timer.h"

#include <random>

Entity::Entity()
{
	// Random number generator. Made this static so that this generator
	// doesn't get created and destroyed everytime an entity is created. This would be 
	// bad specially when having huge array of entities
	static std::random_device rd;
	static std::mt19937 e2(rd());
	static std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

	// Generate random position
	m_x = dist(e2);
	m_y = dist(e2);

	// Starting health is 100
	m_health = 100;
}

Entity::~Entity()
{
}
