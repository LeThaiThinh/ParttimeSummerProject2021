#pragma once
#include "Sprite2D.h"
class MainCharacter
	: public Sprite2D
{
protected:

public:
	MainCharacter() : Sprite2D() {}
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~MainCharacter();

	void	Update(GLfloat deltatime) override;
	void	Init() override;
	void	HandleKeyEvent(int key,bool bbIsPresseded);

	void	SetVelocity(Vector3);
	Vector3	GetVelocity();
	void	Move(GLfloat deltatime, GLfloat duration);
private:
	Vector3 m_velocity;
	float m_time;

};

