#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "../HandFan.h"

GSPlay::GSPlay() :GameStateBase(StateType::STATE_INTRO), m_time(0.0f),m_poolTarget(__nullptr)
{
}


GSPlay::~GSPlay()
{
}

int GameStateBase::keyPress = 0;
ObjectPool<Target>* ObjectPool<Target>::instance = 0;

void GSPlay::Init()
{
	srand(time(0));
	//
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("PlayBackground.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth - 50, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	// main character
	texture = ResourceManagers::GetInstance()->GetTexture("MainCharacter.tga");
	m_mainCharacter = std::make_shared<MainCharacter>(model, shader, texture);
	// pool tartget
	m_poolTarget = ObjectPool<Target>::getInstance();
	m_poolArrow = ObjectPool<Arrow>::getInstance();
	// timer
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_timer = std::make_shared< Text>(shader, font, "Time:"+std::to_string((int)m_time), TextColor::RED, 1.0f);
	m_timer->Set2DPosition(Vector2(5, 25));
	

}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}
void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == true) {
		switch (key)
		{
		case 'A':
			keyPress |= KEY_MOVE_LEFT;
			break;
		case 'D':
			keyPress |= KEY_MOVE_RIGHT;
			break;
		case VK_SPACE:
			keyPress |= KEY_SPACE;
			break;
		default:
			break;
		}
	}
	else {
		switch (key) {
		case 'A':
			keyPress ^= KEY_MOVE_LEFT;
			break;
		case 'D':
			keyPress ^= KEY_MOVE_RIGHT;
			break;
		case VK_SPACE:
			keyPress ^= KEY_SPACE;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	m_time += deltaTime;
	//manage main character
	m_mainCharacter->Update(deltaTime);
	if (keyPress & KEY_MOVE_LEFT) {
		m_mainCharacter->Move(deltaTime, Direction::LEFT);
	}
	if (keyPress & KEY_MOVE_RIGHT) {
		m_mainCharacter->Move(deltaTime, Direction::RIGHT);
	}
	if (keyPress & KEY_SPACE ) {
		Arrow* arrow = m_mainCharacter->Shoot();
		if (arrow != nullptr) {
			m_listArrow.push_back(arrow);
			std::cout << m_listArrow.size() << "-";

		}
	}
	//manage list button
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	// manage list target : create,update,remove
	if ((int)(m_time *2) > (int)((m_time - deltaTime)*2)) {
		Target* target = m_poolTarget->getResource();
		m_listTarget.push_back(target);
	}
	for (auto it : m_listTarget)
	{
		it->Update(deltaTime);
		for (auto arrow : m_listArrow) {
			if (it->IsCollided(arrow)) {
				m_listRemoveTarget.push_back(it);
				m_poolTarget->returnResource(it);
			}
		}
		if (!it->IsExist()) {
			m_listRemoveTarget.push_back(it);
			m_poolTarget->returnResource(it);
		}
	}
	for (auto it : m_listRemoveTarget)
	{
		m_listTarget.remove(it);
	} 
	m_listRemoveTarget.clear();
	//manage list arrow
	for (auto it : m_listArrow)
	{
		it->Update(deltaTime);
		if (!it->IsExist()) {
			m_listRemoveArrow.push_back(it);
			m_poolArrow->returnResource(it);
		}
	}
	for (auto it : m_listRemoveArrow)
	{
		m_listArrow.remove(it);
	}
	m_listRemoveArrow.clear();
	//timer
	m_timer->SetText("Time:" + std::to_string((int)m_time));
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_timer->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listTarget)
	{
		it->Draw();
	}
	for (auto it : m_listArrow)
	{
		it->Draw();
	}
	m_mainCharacter->Draw();
}