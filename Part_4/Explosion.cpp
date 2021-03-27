#include "Explosion.h"
#include "Entity.h"
#include "Timer.h"

#include <random>

Explosion::Explosion()
{
	// Random number generator. Made this static so that this generator
	// doesn't get created and destroyed everytime an Explosion is created.
	static std::random_device rd;
	static std::mt19937 e2(rd());
	static std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

	// Generate random position
	m_x = dist(e2);
	m_y = dist(e2);

	m_r1 = 2.5f;	// Inner radius
	m_r2 = 6.0f;	// Outer  radius

	m_damage = 80.0f;
}

Explosion::~Explosion()
{
}

void explosionUpdate(Explosion *explosion, Entity *entities, int numEntities)
{
	Timer t;

	for (int i = 0; i < numEntities; i++)
	{
		// Calculate the distante from entity to explosion
		float dx = explosion->m_x - entities[i].m_x;
		float dy = explosion->m_y - entities[i].m_y;
		float distance = std::sqrt(dx * dx + dy * dy);

		// Calculate damage factor
		float dmgFactor = 1 - ((distance - explosion->m_r1) / (explosion->m_r2 - explosion->m_r1));
		float clampedFactor = std::min(1.0f, std::max(0.0f, dmgFactor));

		// Apply damage to entity
		entities[i].m_health -= explosion->m_damage * clampedFactor;
	}
}
