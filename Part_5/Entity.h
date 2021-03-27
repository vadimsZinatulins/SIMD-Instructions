#ifndef __ENTITY_H__
#define __ENTITY_H__

class Explosion;

class Entity
{
public:
	Entity();
	~Entity();

private:
	// This is here so that this function can access private attributes of this class
	friend void explosionUpdate(Explosion *explosion, Entity *entities, int numEntities);

	// Entity's position
	float m_x;
	float m_y;

	// Entity's health
	float m_health;
};

#endif // !__ENTITY_H__
