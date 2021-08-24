#include "MainCharacter.h"


MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(id,model,shader,texture), m_time(0.0f), m_velocity(50.0f)
{
	Init();
}

MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color)
	: Sprite2D(id, model, shader, color), m_time(0.0f), m_velocity(50.0f)
{
	Init();
}

MainCharacter::MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_time(0.0f), m_velocity(50.0f)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}


void MainCharacter::Update(GLfloat deltatime)
{
}

void MainCharacter::Init()
{
	Set2DPosition(Vector2(Globals::screenWidth/2, Globals::screenHeight-50));
	SetSize(60, 80);
}


void MainCharacter::SetVelocity(float velocity)
{
	m_velocity = velocity;
}

float MainCharacter::GetVelocity()
{
	return m_velocity;
}

void MainCharacter::Move(GLfloat deltatime, GLfloat duration, Direction direction)
{
	if (m_time < duration) {
		m_time += deltatime;
		if (direction == Direction::LEFT) {
			Set2DPosition(Vector2(m_position.x - m_velocity * deltatime, m_position.y));
		}else if (direction == Direction::RIGHT) {
			Set2DPosition(Vector2(m_position.x + m_velocity * deltatime, m_position.y));
		}
	}
}
void MainCharacter::Move(GLfloat deltatime, Direction direction)
{

	if (direction == Direction::LEFT) {
		Set2DPosition(Vector2(m_position.x - m_velocity * deltatime, m_position.y));
	}
	else if (direction == Direction::RIGHT) {
		Set2DPosition(Vector2(m_position.x + m_velocity * deltatime, m_position.y));
	}

}

