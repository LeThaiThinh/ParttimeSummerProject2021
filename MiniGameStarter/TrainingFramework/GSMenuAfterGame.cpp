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
	auto texture = ResourceManagers::GetInstance()->GetTexture("AfterGameBackGround.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Exit.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth *7/12, (float)Globals::screenHeight * 2 / 3);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GSPlay::score = 0;
		GSPlay::scoreOpponent = 0;
		GSPlay::sound->Stop();
		if(GSMenu::backgroundMusic)
			GSMenu::sound->PlayLoopSound();
		});
	m_listButton.push_back(button);
	// playagain button
	texture = ResourceManagers::GetInstance()->GetTexture("PlayAgain.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth * 5 / 12, (float)Globals::screenHeight * 2 / 3);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		GSPlay::score = 0;
		GSPlay::scoreOpponent = 0;
		});
	m_listButton.push_back(button);
	// Score Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> text;
	text = std::make_shared< Text>(shader, font,GSPlay::score>GSPlay::scoreOpponent?"You win!": GSPlay::score < GSPlay::scoreOpponent?"You lose!":"Draw", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 3 , (float)Globals::screenHeight * 1 / 3));
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
	m_textGameName.back()->SetText(GSPlay::score > GSPlay::scoreOpponent ? "You win!" : GSPlay::score < GSPlay::scoreOpponent ? "You lose!" : "Draw");

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
