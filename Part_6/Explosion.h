#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

class EntityBuffer;

class Explosion
{
public:
	Explosion();
	~Explosion();

private:
	// This is here so that this function can access private attributes of this class
	friend void explosionUpdate(Explosion *explosion, EntityBuffer *entities, int numEntities);

	// Explosion's position
	float m_x;
	float m_y;

	// Explosion's radiuses
	float m_r1;
	float m_r2;

	// Explosion's damage
	float m_damage;;
};

void explosionUpdate(Explosion *explosion, EntityBuffer *entities, int numEntities);

#endif // !__EXPLOSION_H__
