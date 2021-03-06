#include "GSOption.h"


GSOption::GSOption() :GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(std::list<std::shared_ptr<Text>>{})
{
}

GSOption::~GSOption()
{
}

void GSOption::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth - 50, 50.f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	
	//VFX music button
	texture = ResourceManagers::GetInstance()->GetTexture("On.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth *2/3-50, (float)Globals::screenHeight * 2 / 6);
	button->SetSize(150, 50);
	button->SetName("VFXMusic");
	button->SetOnClick([]() {
		GSMenu::vfxMusic = !GSMenu::vfxMusic;
		});
	m_listButton.push_back(button);

	//background music button
	texture = ResourceManagers::GetInstance()->GetTexture("On.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth *2/3-50, (float)Globals::screenHeight * 3 / 6);
	button->SetSize(150, 50);
	button->SetName("BackgroundMusic");
	button->SetOnClick([]() {
		GSMenu::backgroundMusic = !GSMenu::backgroundMusic;
		if (GSMenu::backgroundMusic)
			GSMenu::sound->PlayLoopSound();
		else
			GSMenu::sound->Stop();
		});
	m_listButton.push_back(button);

	// Credit Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> text;
	text = std::make_shared< Text>(shader, font, "Setting", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 3 + 50, (float)Globals::screenHeight * 1 / 6));
	m_textGameName.push_back(text);

	text = std::make_shared< Text>(shader, font, "VFX Music       ", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 4, (float)Globals::screenHeight * 2 / 6));
	m_textGameName.push_back(text);
	
	text = std::make_shared< Text>(shader, font, "Background Music", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 4, (float)Globals::screenHeight * 3 / 6));
	m_textGameName.push_back(text);

}

void GSOption::Exit()
{
}

void GSOption::Pause()
{
}

void GSOption::Resume()
{
}

void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		if (it->GetName() == "BackgroundMusic") {
			if (GSMenu::backgroundMusic) {
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("On.tga"));
			}else it->SetTexture(ResourceManagers::GetInstance()->GetTexture("Off.tga"));
		}
		else if (it->GetName() == "VFXMusic") {
			if (GSMenu::vfxMusic) {
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("On.tga"));
			}
			else it->SetTexture(ResourceManagers::GetInstance()->GetTexture("Off.tga"));
		}
		it->Update(deltaTime);
	}
}

void GSOption::Draw()
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
