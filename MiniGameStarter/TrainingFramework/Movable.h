#pragma once
#include <CMath.h>
class Movable
{
protected:
	float	m_speed;
	Vector2	m_direction;
public:
	Movable():m_speed(0),m_direction(Vector2(0,0)){}
	void	SetSpeed(float speed) { m_speed = speed; }
	float	GetSpeed() { return m_speed; }
	void	SetDirection(Vector2 direction) { m_direction = direction; }
	Vector2	GetDirection() { return m_direction; }
	virtual void Move(GLfloat deltatime) = 0;
};

