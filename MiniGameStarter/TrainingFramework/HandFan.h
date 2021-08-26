#pragma once
#include "Sprite2D.h"
#include "SelfDestructable.h"
#include "../GameManager/ResourceManagers.h"
#include "Movable.h"
#include "Arrow.h"

enum class TargetType {
	HANDFAN=0,
	CIRCLE,
	BOMB
};
class Target :
    public Sprite2D,SelfDestructable,Movable
{
public:
	Target();
	Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,float timeExist,float timeDestruct);
	Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Target(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	Target(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Target();

	void	Update(GLfloat deltaTime) override;
	void	Init() override;
	void	Reset();

	bool	IsExist() override;
	void	Move(float deltaTime) override;
	bool	IsCollided(Arrow* arrow);
private:
	TargetType type;
};

