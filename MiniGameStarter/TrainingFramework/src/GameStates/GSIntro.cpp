#include "GSIntro.h"
#include "GSPlay.h"
#include "GSMenu.h"

std::shared_ptr<Sound> GSMenu::sound = ResourceManagers::GetInstance()->GetSound("BackgroundMusic.wav");
std::shared_ptr<Sound> GSPlay::sound = ResourceManagers::GetInstance()->GetSound("BackgroundMusicPlay.wav");
bool GSMenu::backgroundMusic = true;
bool GSMenu::vfxMusic = true;
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetSize(Globals::screenWidth / 2, Globals::screenHeight / 2);

	ResourceManagers::GetInstance()->AddShader("AnimationShader");
	ResourceManagers::GetInstance()->AddTexture("explosion.tga");
	ResourceManagers::GetInstance()->AddTexture("bg_main_menu.tga");
	ResourceManagers::GetInstance()->AddTexture("AfterGameBackGround.tga");
	ResourceManagers::GetInstance()->AddTexture("On.tga");
	ResourceManagers::GetInstance()->AddTexture("Exit.tga");
	ResourceManagers::GetInstance()->AddTexture("Off.tga");
	ResourceManagers::GetInstance()->AddTexture("Arrow.tga");
	ResourceManagers::GetInstance()->AddTexture("MainCharacter.tga");
	ResourceManagers::GetInstance()->AddTexture("Opponent.tga");
	ResourceManagers::GetInstance()->AddTexture("TargetHandFan.tga");
	ResourceManagers::GetInstance()->AddTexture("Arrow.tga");
	ResourceManagers::GetInstance()->AddTexture("TargetCircle.tga");
	ResourceManagers::GetInstance()->AddTexture("Bomb.tga");
	ResourceManagers::GetInstance()->AddTexture("Bomb2.tga");
	ResourceManagers::GetInstance()->AddTexture("PlayBackground.tga");
	ResourceManagers::GetInstance()->AddTexture("Pause.tga");
	ResourceManagers::GetInstance()->AddTexture("PlayAgain.tga");
	ResourceManagers::GetInstance()->AddTexture("btn_prev.tga");

}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 3)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
