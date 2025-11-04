#include "game.h"
#include <cmath>

Game::Game() : m_player(Vector3f(VIEW_DISTANCE, 6.7f, VIEW_DISTANCE), 0, -90.f),
m_chunkTest(true), 
m_chunks((2*VIEW_DISTANCE + CHUNK_SIZE_X)/CHUNK_SIZE_X, (2*VIEW_DISTANCE + CHUNK_SIZE_Z)/CHUNK_SIZE_Z)
{
    m_chunks.Reset(nullptr);
}

Game::~Game()
{
    for (int cz = 0; cz < m_chunks.GetY(); ++cz) {
        for (int cx = 0; cx < m_chunks.GetX(); ++cx) {
            Chunk *c = m_chunks.Get(cx,cz);
            delete c;
            m_chunks.Set(cx, cz, nullptr);
        }
    }
}

void Game::Init()
{
    LockCursor();
}

void Game::DeInit()
{
}

void Game::LoadResource()
{

    for (int cz = 0; cz < m_chunks.GetY(); ++cz) 
    {
        for (int cx = 0; cx < m_chunks.GetX(); ++cx) 
         m_chunks.Set(cx, cz, new Chunk(false));
    }

    m_textureBlue.Load("checkerblue.png");
    m_textureFloral.Load("texturefloral.png");
    m_textureDirt1.Load("texturedirt1.png");
    m_shader.Load("shader.vs", "shader.fs");

    rl::Vector3 lightPos = {0, CHUNK_SIZE_Y, 0};
    lights[0] = CreateLight(LIGHT_POINT, lightPos, rl::Vector3Zero(), rl::WHITE, m_shader);

}

void Game::UnloadResource()
{
}

rl::Camera3D Game::Update(float elapsedTime)
{
    // Votre code de logique de jeu qui doit être exécuté à chaque frame ici...

    m_chunkTest.Update();

    for (int cz = 0; cz < m_chunks.GetY(); ++cz) {
        for (int cx = 0; cx < m_chunks.GetX(); ++cx) {
            
            Chunk* c = m_chunks.Get(cx, cz);
            if (!c) continue;
            c->Update();
        }
    }
   

    Vector3f pos = m_player.GetPosition();

    Vector3f delta = m_player.SimulateMove(
        rl::IsKeyDown(rl::KEY_W),
        rl::IsKeyDown(rl::KEY_S),
        rl::IsKeyDown(rl::KEY_A),
        rl::IsKeyDown(rl::KEY_D),
        rl::IsKeyDown(rl::KEY_LEFT_SHIFT),
        m_fly,
        elapsedTime
    );
    m_player.SetPosition(pos+delta);
     if (rl::IsKeyDown(rl::KEY_SPACE) && m_player.IsOnGround())
    {
        m_player.Jump();
    }
    m_player.UpdateJump(elapsedTime);
    UpdateLightValues(m_shader, lights[0]);

    const rl::Camera3D &camera = m_player.GetCamera();
    float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
    m_shader.SetValue(rl::SHADER_LOC_VECTOR_VIEW, cameraPos, rl::SHADER_UNIFORM_VEC3);
    return camera;
}

void Game::Render3D(float elapsedTime)
{
    static float gameTime = 0;
    gameTime += elapsedTime;

    Transformation t;
    t.ApplyTranslation(0, 10.f, 0);
    m_chunkTest.Render(m_textureFloral, m_shader,t);


    for (int cz = 0; cz < m_chunks.GetY(); ++cz) {
        for (int cx = 0; cx < m_chunks.GetX(); ++cx) {
            
           Chunk* c = m_chunks.Get(cx, cz);
            if (!c) continue;

            Transformation t;
            t.ApplyTranslation( cx * CHUNK_SIZE_X, 0.0f, cz * CHUNK_SIZE_Z);
            c->Render(m_textureDirt1, m_shader, t);
        }
    }
    
}

void Game::Render2D(float elapsedTime)
{
    rl::DrawFPS(20, 20);
}

void Game::KeyPressEvent(unsigned char key)
{
}

void Game::KeyReleaseEvent(unsigned char key)
{
}

void Game::MouseMoveEvent(int x, int y)
{
    if (m_firstmouse)
    {
        m_LastmouseX =x;
        m_LastmouseY =y;
        m_firstmouse = false;
    }

    int xoffset = m_LastmouseX - x;
    int yoffset = y - m_LastmouseY;

    m_LastmouseX =x;
    m_LastmouseY =y;

    float sensitivity = .1f;
    float xoffsetf = xoffset * sensitivity;
    float yoffsetf = yoffset * sensitivity;

    m_player.TurnLeftRight(xoffsetf);
    m_player.TurnTopBottom(yoffsetf);

}

void Game::MousePressEvent(const MOUSE_BUTTON &button, int x, int y)
{
}

void Game::MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y)
{
}