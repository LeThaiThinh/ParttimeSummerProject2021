#include "Arrow.h"
#include "Application.h"

Arrow::Arrow(Vector3 position)
{
	Set2DPosition(Vector2(position.x,position.y));
	Init();
}

Arrow::Arrow(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, MainCharacter* mainCharacter)
	: Sprite2D(id, model, shader, texture), m_mainCharacter(mainCharacter)
{
	Init();
}

Arrow::Arrow(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color, MainCharacter* mainCharacter)
	: Sprite2D(id, model, shader, color),  m_mainCharacter(mainCharacter)
{
	Init();
}

Arrow::Arrow(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, MainCharacter* mainCharacter)
	: Sprite2D( model, shader, texture), m_mainCharacter(mainCharacter)
{
	Init();
}

Arrow::~Arrow()
{
}

void Arrow::Update(GLfloat deltaTime)
{
	m_time += deltaTime;
	Move(deltaTime);
}

void Arrow::Init()
{
	m_time = 0;
	m_timeExist = 4;
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("Arrow.tga"));
	SetSpeed(800.0f);
	SetDirection(Vector2(0,-1));
	SetSize(35, 100);
	SetCamera(Application::GetInstance()->GetCamera());

}

void Arrow::Reset()
{
	Init();
}

bool Arrow::IsExist()
{
	return m_time < m_timeExist;;
}

void Arrow::Move(GLfloat deltaTime)
{
	Set2DPosition(m_position.x + deltaTime * m_speed * m_direction.x, m_position.y + deltaTime * m_speed * m_direction.y);
}


