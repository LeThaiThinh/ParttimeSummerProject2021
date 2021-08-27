#include "GSMenuAfterGame.h"

GSMenuAfterGame::GSMenuAfterGame() :GameStateBase(StateType::STATE_MENUAFTERGAME),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(std::list<std::shared_ptr<Text>>{})
{
}

GSMenuAfterGame::~GSMenuAfterGame()
{
}

void GSMenuAfterGame::Init()
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
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Score Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> text;
	text = std::make_shared< Text>(shader, font, "Score :"+GSPlay::score, Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 3 + 50, Globals::screenHeight * 1 / 6));
	m_textGameName.push_back(text);

}

void GSMenuAfterGame::Exit()
{
}

void GSMenuAfterGame::Pause()
{
}

void GSMenuAfterGame::Resume()
{
}

void GSMenuAfterGame::HandleEvents()
{
}

void GSMenuAfterGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenuAfterGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenuAfterGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenuAfterGame::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_textGameName.back()->SetText("Score:" + std::to_string(GSPlay::score));

}

void GSMenuAfterGame::Draw()
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
