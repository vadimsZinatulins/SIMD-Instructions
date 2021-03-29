#include "Explosion.h"
#include "Entity.h"
#include "Timer.h"

#include <random>
#include <nmmintrin.h>

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

	__m128 mmExplosionX = _mm_set_ps1(explosion->m_x);
	__m128 mmExplosionY = _mm_set_ps1(explosion->m_y);
	__m128 mmExplosionR1 = _mm_set_ps1(explosion->m_r1);
	__m128 mmExplosionR2 = _mm_set_ps1(explosion->m_r2);
	__m128 mmExplosionDmg = _mm_set_ps1(explosion->m_damage);
	__m128 mmOne = _mm_set_ps1(1.0);
	__m128 mmZero = _mm_setzero_ps();

	for (int i = 0; i < numEntities; i += 4)
	{
		// Calculate distantes from entities to explosion
		__m128 mmDxs = _mm_sub_ps(mmExplosionX, _mm_set_ps(entities[i + 0].m_x, entities[i + 1].m_x, entities[i + 2].m_x, entities[i + 3].m_x));
		__m128 mmDys = _mm_sub_ps(mmExplosionY, _mm_set_ps(entities[i + 0].m_y, entities[i + 1].m_y, entities[i + 2].m_y, entities[i + 3].m_y));
		__m128 mmDistances = _mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(mmDxs, mmDxs), _mm_mul_ps(mmDys, mmDys)));

		// Calculate damage factor
		__m128 dmgFactors = _mm_sub_ps(mmOne, _mm_div_ps(_mm_sub_ps(mmDistances, mmExplosionR1), _mm_sub_ps(mmExplosionR2, mmExplosionR1)));
		__m128 clampedFactor = _mm_min_ps(mmOne, _mm_max_ps(mmZero, dmgFactors));

		// Calculate new health for each entity
		__m128 mmHealths = _mm_sub_ps(_mm_set_ps(entities[i + 0].m_health, entities[i + 1].m_health, entities[i + 2].m_health, entities[i + 3].m_health), _mm_mul_ps(mmExplosionDmg, clampedFactor));

		// Apply new healths
		float *healths = (float *)&mmHealths;
		entities[i + 0].m_health = healths[3];
		entities[i + 1].m_health = healths[2];
		entities[i + 2].m_health = healths[1];
		entities[i + 3].m_health = healths[0];
	}
}
