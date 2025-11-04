#ifndef GAME_H
#define GAME_H

#include "blockinfo.h"
#include "chunk.h"
#include "array2d.h"
#include "define.h"
#include "engine.h"
#include "mesh.h"
#include "player.h"
#include "rlights.h"
#include "shader.h"
#include "texture.h"

class Game : public Engine
{
public:
    Game();
    virtual ~Game();
    virtual void Init();
    virtual void DeInit();
    virtual void LoadResource();
    virtual void UnloadResource();
    virtual rl::Camera3D Update(float elapsedTime);
    virtual void Render3D(float elapsedTime);
    virtual void Render2D(float elapsedTime);
    virtual void KeyPressEvent(unsigned char key);
    virtual void KeyReleaseEvent(unsigned char key);
    virtual void MouseMoveEvent(int x, int y);
    virtual void MousePressEvent(const MOUSE_BUTTON &button, int x, int y);
    virtual void MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y);

private:
    //Mesh m_meshFloor;
    Chunk m_chunkTest;
    Array2d<Chunk*> m_chunks ;

    Texture m_textureBlue;
    Texture m_textureFloral;
    Texture m_textureDirt1;

    Shader m_shader;
    Light lights[MAX_LIGHTS] = {};

    Player m_player;
    bool m_fly = false;
    bool m_firstmouse = true;
    int m_LastmouseX, m_LastmouseY ;

};

#endif /* GAME_H */
