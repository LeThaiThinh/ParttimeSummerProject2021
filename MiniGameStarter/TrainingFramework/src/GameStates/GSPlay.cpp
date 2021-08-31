#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "../HandFan.h"

GSPlay::GSPlay() :GameStateBase(StateType::STATE_PLAY),m_time(60.0f),m_poolTarget (ObjectPool<Target>::getInstance())
{
}

GSPlay::~GSPlay()
{
}

int GameStateBase::keyPress = 0;
ObjectPool<Target>* ObjectPool<Target>::instance = 0;
int GSPlay::score = 0;
int GSPlay::scoreOpponent = 0;
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

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("Pause.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth - 50, 50.0f);
	button->SetSize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENUINGAME);
		});
	m_listButton.push_back(button);
	// main character
	texture = ResourceManagers::GetInstance()->GetTexture("MainCharacter.tga");
	m_mainCharacter = std::make_shared<MainCharacter>(model, shader, texture);
	m_mainOpponent = std::make_shared<MainCharacter>(model, shader, texture);
	// timer
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_timer = std::make_shared< Text>(shader, font, "Time:"+std::to_string((int)m_time), TextColor::RED, 1.0f);
	m_timer->Set2DPosition(Vector2((float)Globals::screenWidth / 2 , 25.0f));
	// score
	m_score = std::make_shared< Text>(shader, font, "Your Score:" + std::to_string(GSPlay::score), TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2((float)Globals::screenWidth/2 - 300, 25.0f));
	m_scoreOpponent = std::make_shared< Text>(shader, font, "Opponent's score:" + std::to_string(GSPlay::scoreOpponent), TextColor::RED, 1.0f);
	m_scoreOpponent->Set2DPosition(Vector2((float)Globals::screenWidth / 2 + 150, 25.0f));
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
	m_time -= deltaTime;
	if (m_time <= 0)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENUAFTERGAME);
		m_time = 0;
	}
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
		}
	}
	m_mainOpponent->Update(deltaTime);
	Arrow* arrow = m_mainOpponent->MoveRandomAndShoot(deltaTime);
	if (arrow != nullptr) {
		m_listArrowOpponent.push_back(arrow);
	}
	//manage list button
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	// manage list target : create,update,remove
	if ((int)(m_time *3) > (int)((m_time - deltaTime)*3)) {
		Target* target = m_poolTarget->getResource();
		m_listTarget.push_back(target);
	}
	for (auto it : m_listTarget)
	{
		it->Update(deltaTime);
		//check your arrow collide target
		for (auto arrow : m_listArrow) {
			if (it->IsCollided(arrow)) {
				if (it->GetType() == TargetType::CIRCLE) {
					m_listRemoveArrow.push_back(arrow);
					GSPlay::score += 3;
				}
				else if (it->GetType() == TargetType::BOMB) {
					m_listRemoveArrow.push_back(arrow);
					Explosion* explosion =new Explosion(it->GetPosition().x, it->GetPosition().y,true);
					m_listExplosion.push_back(explosion);
					GSPlay::score += 2;
				}
				else {
					GSPlay::score++;
				}
				m_listRemoveTarget.push_back(it);
				m_poolTarget->returnResource(it);
			}
		}
		//check opponent's arrow collide target
		for (auto arrow : m_listArrowOpponent) {
			if (it->IsCollided(arrow)) {
				if (it->GetType() == TargetType::CIRCLE) {
					m_listRemoveArrow.push_back(arrow);
					GSPlay::scoreOpponent += 3;
				}
				else if (it->GetType() == TargetType::BOMB) {
					m_listRemoveArrow.push_back(arrow);
					Explosion* explosion = new Explosion(  it->GetPosition().x, it->GetPosition().y,false);
					m_listExplosion.push_back(explosion);
					GSPlay::scoreOpponent += 2;
				}
				else {
					GSPlay::scoreOpponent++;
				}
				m_listRemoveTarget.push_back(it);
				m_poolTarget->returnResource(it);
			}
		}
		//check explosion collide target
		for (auto explosion : m_listExplosion) {
			if (it->IsCollided(explosion)) {
				if (!explosion->IsYou()) {
					if (it->GetType() == TargetType::CIRCLE) {
						GSPlay::scoreOpponent += 3;
					}
					else if (it->GetType() == TargetType::BOMB) {
						Explosion* explosion = new Explosion( it->GetPosition().x, it->GetPosition().y, false);
						m_listExplosion.push_back(explosion);
						GSPlay::scoreOpponent += 2;
					}
					else {
						GSPlay::scoreOpponent++;
					}
				}
				else {
					if (it->GetType() == TargetType::CIRCLE) {
						GSPlay::score += 3;
					}
					else if (it->GetType() == TargetType::BOMB) {
						Explosion* explosion = new Explosion( it->GetPosition().x, it->GetPosition().y, true);
						m_listExplosion.push_back(explosion);
						GSPlay::score += 2;
					}
					else {
						GSPlay::score++;
					}
				}
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
	//manage explosion
	for (auto it : m_listExplosion)
	{
		it->Update(deltaTime);
		if (!it->IsExist()) {
			m_listRemoveExplosion.push_back(it);
		}
	}
	for (auto it : m_listRemoveExplosion)
	{
		m_listExplosion.remove(it);
	}
	m_listRemoveTarget.clear();
	//manage list arrow
	for (auto it : m_listArrow)
	{
		it->Update(deltaTime);
		if (!it->IsExist()) {
			m_listRemoveArrow.push_back(it);
			m_mainCharacter->ReturnResourceArrow(it);
		}
	}
	for (auto it : m_listArrowOpponent)
	{
		it->Update(deltaTime);
		if (!it->IsExist()) {
			m_listRemoveArrow.push_back(it);
			m_mainOpponent->ReturnResourceArrow(it);
		}
	}
	for (auto it : m_listRemoveArrow)
	{
		m_listArrow.remove(it);
		m_listArrowOpponent.remove(it);
	}
	m_listRemoveArrow.clear();
	//timer
	m_timer->SetText("Time:" + std::to_string((int)m_time));
	m_score->SetText("Your Score:" + std::to_string(score));
	m_scoreOpponent->SetText("Opponent's score:" + std::to_string(GSPlay::scoreOpponent));
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_timer->Draw();
	m_score->Draw();
	m_scoreOpponent->Draw();
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
	for (auto it : m_listArrowOpponent)
	{
		it->Draw();
	}
	for (auto it : m_listExplosion)
	{
		it->Draw();
	}	
	m_mainCharacter->Draw();
	m_mainOpponent->Draw();
}
