#pragma once
#include "AnimationSprite.h"
#include "SelfDestructable.h"
#include "ResourceManagers.h"
#include <AL/Sound.h>
#include <GameStates/GSMenu.h>

class Explosion :
    public AnimationSprite, SelfDestructable
{
public:
    Explosion();
    Explosion(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, float frameTime, float x, float y, bool isYou);
    Explosion(float x,float y,bool isYou);
    ~Explosion();
    void Init();
    void Update(GLfloat);
    bool IsExist();
    bool IsYou();
    static std::shared_ptr<Sound> sound ;
private:
    bool m_isYou;
};

