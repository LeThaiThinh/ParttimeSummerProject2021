#include "Explosion.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"
#include "Application.h"
std::shared_ptr<Sound> Explosion::sound = ResourceManagers::GetInstance()->GetSound("Bomb.wav");
Explosion::Explosion()
	:AnimationSprite() , m_isYou(true)
{
}

Explosion::Explosion(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, float frameTime, float x, float y, bool isYou)
	: AnimationSprite(model, shader, texture,numFrame,frameTime,x,y), SelfDestructable(), m_isYou(isYou)
{
	Set2DPosition(x, y);
	Init();
}
Explosion::Explosion( float x, float y, bool isYou)
	: AnimationSprite(16, 0.033,4, x, y), SelfDestructable(),m_isYou(isYou)
{
	if(GSMenu::vfxMusic)sound->PlaySound();
	Set2DPosition(x, y);
	Init();
}
Explosion::~Explosion()
{
}

void Explosion::Init()
{
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("Bomb2.tga"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
	SetSize(200,200);
	m_timeExist = 0.5f;
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}
void Explosion::Update(GLfloat deltatime)
{
	m_time += deltatime;
	m_currentFrameTime += deltatime;
	if (m_currentFrameTime >= m_frameTime) {
		m_currentFrame++;
		m_currentColumn = (m_currentFrame % m_numFramesInLine);
		m_currentLine = (m_currentFrame / m_numFramesInLine);
		if (m_currentFrame >= m_numFrames) {
			m_currentFrame = 0;
		}		m_currentFrameTime -= m_frameTime;
	}
}
bool Explosion::IsExist()
{
	return m_time < m_timeExist;;
}
bool Explosion::IsYou()
{
	return Explosion::m_isYou;
}
