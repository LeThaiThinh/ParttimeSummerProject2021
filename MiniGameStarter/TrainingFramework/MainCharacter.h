#pragma once
#include "Sprite2D.h"
#include "Movable.h"
#include "Arrow.h"
#include "../../ObjectPool.h"
#include <AL/ClassSound.h>
#include <GameStates/GSMenu.h>
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

	MainCharacter() : Sprite2D(),m_shootInterval(1),m_shootTime(0),m_poolArrow(),m_arrived(true) {}
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void	Update(GLfloat) override;
	void	Init() override;

	void	Move(GLfloat deltatime, Direction direction) ;
	void	Move(GLfloat deltatime);
	bool	MoveTo(GLfloat deltatime,Vector3 position);

	Arrow*  Shoot();
	Arrow*	MoveRandomAndShoot(float deltaTime);
	void	ReturnResourceArrow(Arrow* arrow);
	static	ClassSound* sound;
private:
	ObjectPool<Arrow>* m_poolArrow;
	float m_shootInterval;
	float m_shootTime;
	bool m_arrived;
	Vector3 m_toArrive;
};

