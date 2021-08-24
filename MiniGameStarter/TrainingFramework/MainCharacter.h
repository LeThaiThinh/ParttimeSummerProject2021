#pragma once
#include "Sprite2D.h"
class MainCharacter
	: public Sprite2D
{
public:
	enum Direction {
		LEFT,
		RIGHT
	};
	MainCharacter() : Sprite2D(), m_time(0.0f), m_velocity(50.0f) {}
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void	Update(GLfloat) override;
	void	Init() override;

	void	SetVelocity(float);
	float	GetVelocity();
	void	Move(GLfloat, GLfloat, Direction);
	void	Move(GLfloat deltatime, Direction direction);
private:
	float m_velocity;
	float m_time;

};

