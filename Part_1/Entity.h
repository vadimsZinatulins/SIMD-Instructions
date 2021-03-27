#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
public:
	Entity();
	~Entity();

	// Gets called every frame to update Entity's internal state
	void udpate(float deltaTime);
private:
	// Entity's position
	float m_x;
	float m_y;

	// Entity's velocity
	float m_vx;
	float m_vy;

	// Entity's health
	float m_health;
};

#endif // !__ENTITY_H__
