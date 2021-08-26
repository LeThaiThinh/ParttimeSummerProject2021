#pragma once
#include "Sprite2D.h"
#include "Movable.h"
#include "MainCharacter.h"
#include "../GameManager/ResourceManagers.h"
#include "SelfDestructable.h"

class MainCharacter;
class Arrow :
    public Sprite2D, Movable,SelfDestructable
{

public:

	Arrow() : Sprite2D(), m_mainCharacter(){}
	Arrow(Vector3 position);
	Arrow(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, MainCharacter* mainCharacter);
	Arrow(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color, MainCharacter* mainCharacter);
	Arrow(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, MainCharacter* mainCharacter);
	~Arrow();

	void	Update(GLfloat) override;
	void	Init() override;
	void	Reset();

	bool	IsExist() override;
	void	Move(GLfloat deltatime) override;
private:
	MainCharacter* m_mainCharacter;
};

