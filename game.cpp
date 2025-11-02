#include "game.h"
#include <cmath>

Game::Game() : m_player(Vector3f(0, 0, 0), 0, -90.f)
{
}

Game::~Game()
{
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
    Mesh::VertexData *vd = new Mesh::VertexData[6]; // 6 vertex (1 quad, 2 triangles)

    int count = 0;
    const float size = 25.f;
    const float nbRep = 50.f;

    // Plancher
    // 4-------------3
    // | \           |
    // |   \         |
    // |     \       |
    // |       \     |
    // |         \   |
    // |           \ |
    // 1-------------2
    vd[count++] = Mesh::VertexData(-size, -2.f, size, 0, 1, 0, 1, 1, 1, 0, 0);         // 1
    vd[count++] = Mesh::VertexData(size, -2.f, size, 0, 1, 0, 1, 1, 1, nbRep, 0);      // 2
    vd[count++] = Mesh::VertexData(-size, -2.f, -size, 0, 1, 0, 1, 1, 1, 0, nbRep);    // 4
    vd[count++] = Mesh::VertexData(size, -2.f, size, 0, 1, 0, 1, 1, 1, nbRep, 0);      // 2
    vd[count++] = Mesh::VertexData(size, -2.f, -size, 0, 1, 0, 1, 1, 1, nbRep, nbRep); // 3
    vd[count++] = Mesh::VertexData(-size, -2.f, -size, 0, 1, 0, 1, 1, 1, 0, nbRep);    // 4

    m_meshFloor.SetMeshData(vd, count);
    delete[] vd;

    m_textureBlue.Load("checkerblue.png");
    m_textureFloral.Load("texturefloral.png");
    m_textureDirt1.Load("texturedirt1.png");
    m_shader.Load("shader.vs", "shader.fs");

    rl::Vector3 lightPos = {0, CHUNK_SIZE_Y, 0};
    lights[0] = CreateLight(LIGHT_POINT, lightPos, rl::Vector3Zero(), rl::WHITE, m_shader);

    
    // 4-------------3
    // | \           |
    // |   \         |
    // |     \       |
    // |       \     |
    // |         \   |
    // |           \ |
    // 1-------------2

    CubeMaker(vd,.5f,m_meshCube);
    CubeMaker(vd, .1f, m_meshsmallCube1);
}

void Game::UnloadResource()
{
}

rl::Camera3D Game::Update(float elapsedTime)
{
    // Votre code de logique de jeu qui doit être exécuté à chaque frame ici...

    Vector3f pos = m_player.GetPosition();

    Vector3f delta = m_player.SimulateMove(
        rl::IsKeyDown(rl::KEY_W),
        rl::IsKeyDown(rl::KEY_S),
        rl::IsKeyDown(rl::KEY_A),
        rl::IsKeyDown(rl::KEY_D),
        false,
        m_fly,
        elapsedTime
    );
    m_player.SetPosition(pos+delta);

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

    m_meshFloor.Render(m_textureDirt1, m_shader);

    Transformation t;
    t.ApplyTranslation(0, 0, -3.f);
    Transformation t1;
    t1.ApplyTranslation(1.f,1.f,-3.f);
    // t.ApplyRotation(gameTime * 30.f, 1.f, 0.f, 0.f); // X
    // t.ApplyRotation(gameTime * 47.f, 0.f, 1.f, 0.f); // Y
    // t.ApplyRotation(gameTime * 61.f, 0.f, 0.f, 1.f); // Z

    // t.ApplyTranslation(sin(gameTime), 0,0);
    // t.ApplyRotation(gameTime* 50, 0,0,1);
    // static float facteur = 1.f;
    // if(facteur >0)
    //     facteur -= .1f *elapsedTime;
       
    //t.ApplyScale(facteur,facteur,facteur);


    m_meshCube.Render(m_textureFloral, m_shader, t);
    m_meshsmallCube1.Render(m_textureBlue,m_shader, t1);
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

void Game::CubeMaker(Mesh::VertexData *vd, float dimension, Mesh& cube)
{
    vd = new Mesh::VertexData[36];
    int count = 0;

    // Face avant du cube 
    vd[count++] = Mesh::VertexData(-dimension, -dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 0, 0); //1
    vd[count++] = Mesh::VertexData(dimension, -dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(-dimension, dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 0, 1.f); //4
    vd[count++] = Mesh::VertexData(dimension, -dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(dimension, dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f); //3
    vd[count++] = Mesh::VertexData(-dimension, dimension, dimension, 0, 0, 1.f, 1.f, 1.f, 1.f, 0, 1.f); //4

    // Face droite du cube 
    vd[count++] = Mesh::VertexData(dimension, -dimension, dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 0, 0); //1
    vd[count++] = Mesh::VertexData(dimension, -dimension, -dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(dimension, dimension, dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 0, 1.f); //4
    vd[count++] = Mesh::VertexData(dimension, -dimension, -dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(dimension, dimension, -dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 1.f); //3
    vd[count++] = Mesh::VertexData(dimension, dimension, dimension, 1.f, 0, 0, 1.f, 1.f, 1.f, 0, 1.f); //4

    // Face gauche du cube 
    vd[count++] = Mesh::VertexData(-dimension, -dimension, -dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 0, 0); //1
    vd[count++] = Mesh::VertexData(-dimension, -dimension, dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(-dimension, dimension, -dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 0, 1.f); //4
    vd[count++] = Mesh::VertexData(-dimension, -dimension, dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(-dimension, dimension, dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 1.f, 1.f); //3
    vd[count++] = Mesh::VertexData(-dimension, dimension, -dimension, -1.f, 0, 0, 1.f, 1.f, 1.f, 0, 1.f); //4

    // Face arriere du cube 
    vd[count++] = Mesh::VertexData(-dimension, -dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 0,   0); // 1
    vd[count++] = Mesh::VertexData(-dimension,  dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 0,   1.f); // 4
    vd[count++] = Mesh::VertexData( dimension, -dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 1.f, 0);   // 2
    vd[count++] = Mesh::VertexData( dimension, -dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 1.f, 0);   // 2
    vd[count++] = Mesh::VertexData(-dimension,  dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 0,   1.f); // 4
    vd[count++] = Mesh::VertexData( dimension,  dimension, -dimension, 0, 0, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f); // 3

    // Face dessus du cube 
    vd[count++] = Mesh::VertexData(-dimension, dimension, dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 0, 0); //1
    vd[count++] = Mesh::VertexData(dimension, dimension, dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(-dimension, dimension, -dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 0, 1.f); //4
    vd[count++] = Mesh::VertexData(dimension, dimension, dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 1.f, 0); //2
    vd[count++] = Mesh::VertexData(dimension, dimension, -dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 1.f, 1.f); //3
    vd[count++] = Mesh::VertexData(-dimension, dimension, -dimension, 0, 1.f, 0, 1.f, 1.f, 1.f, 0, 1.f); //4

    // Face dessous du cube 
    vd[count++] = Mesh::VertexData(-dimension, -dimension,  dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 0,   0);   // 1
    vd[count++] = Mesh::VertexData(-dimension, -dimension, -dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 0,   1.f); // 4
    vd[count++] = Mesh::VertexData( dimension, -dimension,  dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 1.f, 0);   // 2
    vd[count++] = Mesh::VertexData( dimension, -dimension,  dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 1.f, 0);   // 2
    vd[count++] = Mesh::VertexData(-dimension, -dimension, -dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 0,   1.f); // 4
    vd[count++] = Mesh::VertexData( dimension, -dimension, -dimension, 0, -1.f, 0, 1.f, 1.f, 1.f, 1.f, 1.f); // 3
    
    cube.SetMeshData(vd,count);
    delete vd;
}
