#include "Target.h"
#include "Application.h"

Target::Target()
	:Sprite2D(), SelfDestructable()
{

	Init();
}

Target::Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float timeExist, float timeDestruct)
	: Sprite2D(id, model, shader, texture), SelfDestructable(timeExist, timeDestruct)
{
	Init();
}

Target::Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(id, model, shader, texture) 
{
	Init();
}

Target::Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color)
	: Sprite2D(id, model, shader, color)
{
	Init();
}

Target::Target(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

Target::~Target()
{
}

void Target::Update(GLfloat deltaTime)
{
	m_time += deltaTime;
	Move(deltaTime);
}

void Target::Init()
{
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
	int random = rand() % 7;
	float y=0;
	float x=0;
	m_time = 0;
	y = (float)(rand() % Globals::screenHeight * 3/5  + Globals::screenHeight * 1 / 6);
	if (random <=3 ) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TargetHandFan.tga"));
		SetSpeed(50.0f);
		SetSize(50, 50);
		SetType(TargetType::HANDFAN);
		m_timeExist = 7.0f;
		if (rand() % 2 == 0) {
			x = (float)m_iWidth / 2;
			SetDirection(Vector2(1, 0));
		}
		else {
			x = (float)Globals::screenWidth / 2;
			SetDirection(Vector2(-1, 0));
		}
	}
	else if (random <= 5) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TargetCircle.tga"));
		SetSize(75, 100);
		SetSpeed(175.0f);
		SetType(TargetType::CIRCLE);
		m_timeExist = 10.0f;
		if (rand() % 2 == 0) {
			x = (float)- m_iWidth / 2;
			SetDirection(Vector2(1,0));
		}else{
			x= (float)Globals::screenWidth + m_iWidth/2;
			SetDirection(Vector2(-1, 0));
		}
	}
	else if (random == 6) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Bomb.tga"));
		SetSpeed(100.0f);
		SetSize(50, 75);
		SetType(TargetType::BOMB);
		m_timeExist = 15.0f;
		if (rand() % 2 == 0) {
			x = (float)-m_iWidth / 2;
			SetDirection(Vector2(1, 0));
		}
		else {
			x = (float)Globals::screenWidth + m_iWidth/2;
			SetDirection(Vector2(-1, 0));
		}
	}
	SetCamera(Application::GetInstance()->GetCamera());
	Set2DPosition(x, y);
}

void Target::Reset()
{
	Init();
}


bool Target::IsExist()
{
	return m_time < m_timeExist;;
}


void Target::Move(float deltaTime)
{
	Set2DPosition(m_position.x + deltaTime * m_speed * m_direction.x, m_position.y + deltaTime * m_speed * m_direction.y);
}

bool Target::IsCollided(Arrow* arrow)
{
	if ((m_position.x - m_iWidth /2 < arrow->GetPosition().x) && (arrow->GetPosition().x < m_position.x + m_iWidth / 2) && (m_position.y > arrow->GetPosition().y) &&(arrow->GetPosition().y > m_position.y-m_iHeight)) {
		return true;
	}
	else return false;
}
bool Target::IsCollided(Explosion* explosion)
{
	if ((m_position.x  < explosion->GetPosition().x + explosion->GetSize().x/2) && (explosion->GetPosition().x - explosion->GetSize().x/2 < m_position.x ) && (m_position.y > explosion->GetPosition().y - explosion->GetSize().y/2) && (explosion->GetPosition().y+explosion->GetSize().y/2 > m_position.y )) {
		return true;
	}
	else return false;
}
