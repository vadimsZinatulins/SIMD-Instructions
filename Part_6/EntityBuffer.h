#ifndef __ENTITY_BUFFER_H__
#define __ENTITY_BUFFER_H__

class Explosion;

class EntityBuffer
{
public:
	EntityBuffer(int numEntities);
	~EntityBuffer();

private:
	// This is here so that this function can access private attributes of this class
	friend void explosionUpdate(Explosion *explosion, EntityBuffer *entities, int numEntities);

	float *m_xs;
	float *m_ys;

	float *m_healths;
};

#endif // !__ENTITY_BUFFER_H__
