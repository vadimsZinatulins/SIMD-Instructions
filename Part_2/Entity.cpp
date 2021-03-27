#include "Entity.h"
#include "Timer.h"

#include <random>
#include <nmmintrin.h>

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

	// Generate random velocity
	m_vx = dist(e2);
	m_vy = dist(e2);

	// Starting health is 100
	m_health = 100;
}

Entity::~Entity()
{
}

void Entity::udpate(float deltaTime)
{
	// { ... }
}

void gravityUpdate(float deltaTime, Entity *entities, int numEntities)
{
	for (int i = 0; i < numEntities; i += 4)
	{
		Timer t;

		__m128 mmDeltaGravity = _mm_set_ps1(-9.81f * deltaTime);

		__m128 mmX = _mm_set_ps(entities[i + 0].m_x, entities[i + 1].m_x, entities[i + 2].m_x, entities[i + 3].m_x);
		__m128 mmY = _mm_set_ps(entities[i + 0].m_y, entities[i + 1].m_y, entities[i + 2].m_y, entities[i + 3].m_y);
		__m128 mmVX = _mm_set_ps(entities[i + 0].m_vx, entities[i + 1].m_vx, entities[i + 2].m_vx, entities[i + 3].m_vx);
		__m128 mmVY = _mm_set_ps(entities[i + 0].m_vy, entities[i + 1].m_vy, entities[i + 2].m_vy, entities[i + 3].m_vy);

		mmVY = _mm_add_ps(mmVY, mmDeltaGravity);

		mmX = _mm_add_ps(mmX, mmVX);
		mmY = _mm_add_ps(mmY, mmVY);

		float *xs = (float *)&mmX;
		float *ys = (float *)&mmY;
		float *vys = (float *)&mmY;

		entities[i + 0].m_x = xs[3];
		entities[i + 0].m_y = ys[3];
		entities[i + 0].m_vy = vys[3];

		entities[i + 1].m_x = xs[2];
		entities[i + 1].m_y = ys[2];
		entities[i + 1].m_vy = vys[2];

		entities[i + 2].m_x = xs[1];
		entities[i + 2].m_y = ys[1];
		entities[i + 2].m_vy = vys[1];

		entities[i + 3].m_x = xs[0];
		entities[i + 3].m_y = ys[0];
		entities[i + 3].m_vy = vys[0];
	}
}
