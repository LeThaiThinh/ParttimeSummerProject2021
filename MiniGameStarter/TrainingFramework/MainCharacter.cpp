#include "MainCharacter.h"


MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(id,model,shader,texture), m_time(0.0f)
{
	Init();
}

MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color)
	: Sprite2D(id, model, shader, color), m_time(0.0f)
{
	Init();
}

MainCharacter::MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_time(0.0f)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}


void MainCharacter::Update(GLfloat deltatime)
{
	Move(deltatime, 3.0f);
}

void MainCharacter::Init()
{
	Set2DPosition(Vector2(Globals::screenWidth/2, Globals::screenHeight/2));
	SetSize(60, 80);
	SetVelocity(Vector3(50.0f, 0.0f, 0.0f));
}

void MainCharacter::HandleKeyEvent(int key, bool bbIsPresseded)
{
	if (key == KEY_BACK) {
		LOGI("shotting");
	}
}

void MainCharacter::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

Vector3 MainCharacter::GetVelocity()
{
	return m_velocity;
}

void MainCharacter::Move(GLfloat deltatime, GLfloat duration)
{
	if (m_time < duration) {
		m_time += deltatime;
		Set2DPosition(Vector2(m_position.x + m_velocity.x * deltatime, m_position.y + m_velocity.y * deltatime));
	}

}
