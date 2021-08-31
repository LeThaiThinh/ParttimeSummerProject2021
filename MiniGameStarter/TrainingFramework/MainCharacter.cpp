#include "MainCharacter.h"


MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(id,model,shader,texture)
{
	Init();
}

MainCharacter::MainCharacter(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color)
	: Sprite2D(id, model, shader, color)
{
	Init();
}

MainCharacter::MainCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}


void MainCharacter::Update(GLfloat deltatime)
{
	m_shootTime += deltatime;
}

ObjectPool<Arrow>* ObjectPool<Arrow>::instance = 0;
void MainCharacter::Init()
{
	m_arrived = true;
	m_shootInterval = 0.4f;
	m_shootTime = 0.0f;
	m_poolArrow = ObjectPool<Arrow>::getInstance();
	Set2DPosition(Vector2((GLfloat)Globals::screenWidth/2, (GLfloat)Globals::screenHeight-50));
	SetSize(60, 80);
	SetSpeed(200.0f);
}

void MainCharacter::Move(GLfloat deltatime, Direction direction)
{
	if (direction == Direction::LEFT) {
		Set2DPosition(m_position.x - deltatime * m_speed, (GLfloat)m_position.y);
		if(m_position.x<0)Set2DPosition(0, (GLfloat)m_position.y);

	}
	else
	{
		Set2DPosition((GLfloat)(m_position.x + deltatime * m_speed), (GLfloat)m_position.y);
		if (m_position.x > Globals::screenWidth)Set2DPosition((GLfloat)Globals::screenWidth, (GLfloat)m_position.y);
	}
}

void MainCharacter::Move(GLfloat deltatime)
{
	Set2DPosition(m_position.x + deltatime * m_speed *m_direction.x, m_position.y+ deltatime * m_speed * m_direction.y);
}

bool MainCharacter::MoveTo(GLfloat deltatime, Vector3 position)
{
	Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
	return m_toArrive.operator-(m_position).Length() < 10.0f;
}

Arrow* MainCharacter::Shoot()
{
	if (m_shootTime >= m_shootInterval) {
		m_shootTime = 0;
		return m_poolArrow->getResource2(m_position);
	}
	return nullptr;
}

Arrow* MainCharacter::MoveRandomAndShoot(float deltaTime)
{
	if (m_arrived) {
		float x = float(rand() % Globals::screenWidth * 5 / 6 + Globals::screenWidth * 1 / 12);
		m_toArrive = Vector3(x,m_position.y,0);
		float distance = m_toArrive.operator-(m_position).Length();
		m_direction = Vector2((m_toArrive.x - m_position.x) / distance, (m_toArrive.y - m_position.y) / distance);
		m_arrived = false;
	}
	else {
		m_arrived = MoveTo(deltaTime, m_toArrive);
	}
	return Shoot();
}

void MainCharacter::ReturnResourceArrow(Arrow* arrow)
{
	m_poolArrow->returnResource(arrow);
}

