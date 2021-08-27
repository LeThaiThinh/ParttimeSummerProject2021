#include "GSMenuInGame.h"

GSMenuInGame::GSMenuInGame() :GameStateBase(StateType::STATE_MENUINGAME),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(std::list<std::shared_ptr<Text>>{})
{
}

GSMenuInGame::~GSMenuInGame()
{
}

void GSMenuInGame::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENUAFTERGAME);
		});
	m_listButton.push_back(button);
	// resume button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 150, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	// playagain button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 250, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// Credit Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> text;
	text = std::make_shared< Text>(shader, font, "Credit", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 3 + 50, Globals::screenHeight * 1 / 6));
	m_textGameName.push_back(text);

}

void GSMenuInGame::Exit()
{
}

void GSMenuInGame::Pause()
{
}

void GSMenuInGame::Resume()
{
}

void GSMenuInGame::HandleEvents()
{
}

void GSMenuInGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenuInGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenuInGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenuInGame::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenuInGame::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_textGameName)
	{
		it->Draw();
	}
}
