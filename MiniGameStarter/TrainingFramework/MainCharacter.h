#pragma once
#include "Sprite2D.h"
#include "Movable.h"
#include "Arrow.h"
#include "../../ObjectPool.h"
class Movable;
class Arrow;
enum class Direction {
	LEFT=0,
	RIGHT
};
class MainCharacter
	: public Sprite2D,Movable
{
public:

	MainCharacter() : Sprite2D(),m_shootInterval(1),m_shootTime(0),m_poolArrow() {}
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void	Update(GLfloat) override;
	void	Init() override;

	void	Move(GLfloat deltatime, Direction direction) ;
	void	Move(GLfloat deltatime);

	Arrow*  Shoot();
	void	ReturnResourceArrow(Arrow* arrow);
private:
	ObjectPool<Arrow>* m_poolArrow;
	float m_shootInterval;
	float m_shootTime;
};

