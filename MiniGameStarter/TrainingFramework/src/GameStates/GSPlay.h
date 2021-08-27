#pragma once
#include "GameStateBase.h"
#include "../../MainCharacter.h"
#include "../../ObjectPool.h"
#include "../../HandFan.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;

class GSPlay :
	public GameStateBase
{
public:
	static int score;

	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_timer;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<MainCharacter> m_mainCharacter;
	ObjectPool<Target>* m_poolTarget;
	std::list<Target*> m_listTarget;
	std::list<Target*> m_listRemoveTarget;
	std::list<Arrow*> m_listArrow;
	std::list<Arrow*> m_listRemoveArrow;
	float m_time;
};

