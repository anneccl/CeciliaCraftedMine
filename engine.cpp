#include "engine.h"
#include "define.h"

// TODO
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
    rl::CloseWindow();
}

bool Engine::Start(const std::string &title, int width, int height, bool fullscreen)
{
    InitWindow(title, width, height, fullscreen);

    m_target[0] = rl::LoadRenderTexture(Width(), Height());
    m_target[1] = rl::LoadRenderTexture(Width(), Height());

    Init();
    LoadResource();

    rl::SetTargetFPS(60);

    // Main game loop
    while(!rl::WindowShouldClose())
    {
        DoGameLoop();
    }

    UnloadResource();

    rl::UnloadRenderTexture(m_target[0]);
    rl::UnloadRenderTexture(m_target[1]);
    DeInit();

    return true;
}

bool Engine::Stop()
{
    rl::CloseWindow();
    return true;
}

int Engine::Width() const
{
    return rl::GetScreenWidth();
}

int Engine::Height() const
{
    return rl::GetScreenHeight();
}

void Engine::SetMaxFps(int maxFps)
{
    rl::SetTargetFPS(maxFps);
}

void Engine::SetFullscreen(bool fullscreen)
{
    bool current = rl::IsWindowFullscreen();

    if(current == fullscreen)
        return;

    rl::ToggleFullscreen();

    DeInit();
    Init();
}

bool Engine::IsFullscreen() const
{
    return rl::IsWindowFullscreen();
}

bool Engine::IsWireframe() const
{
    return m_wireframe;
}

void Engine::LockCursor()
{
    rl::DisableCursor();
}

void Engine::UnlockCursor()
{
    rl::EnableCursor();
}

void Engine::ShowCursor()
{
    rl::ShowCursor();
}

void Engine::HideCursor()
{
    rl::HideCursor();
}

void Engine::TakeScreenshot(const std::string &filename) const
{
    rl::TakeScreenshot(filename.c_str());
}

// http://geomalgorithms.com/a05-_intersect-1.html
int Engine::Intersect3DSegmentPlane(Vector3f segmentStart, Vector3f segmentEnd, Vector3f planePoint, Vector3f planeNormal, Vector3f *I) // I = intersection point
{
    Vector3f u = segmentEnd - segmentStart;
    Vector3f w = segmentStart - planePoint;

    float D = planeNormal.Dot(u);
    float N = -planeNormal.Dot(w);

    if(fabs(D) < 0.00000001)
    {              // segment is parallel to plane
        if(N == 0) // segment lies in plane
            return 2;
        else
            return 0; // no intersection
    }
    // they are not parallel
    // compute intersect param
    float sI = N / D;
    if(sI < 0 || sI > 1)
        return 0; // no intersection

    *I = segmentStart + u * sI; // compute segment intersect point
    return 1;
}

bool Engine::IsBetween(float value, float min, float max)
{
    float epsilon = 0;
    return (value >= min - epsilon && value <= max + epsilon);
}

bool Engine::AABBSegmentIntersect(Vector3f boxCenter, Vector3f boxSize, Vector3f segmentStart, Vector3f segmentEnd, Vector3f &hitPos, Vector3f &hitNormal)
{
    const Vector3f &c = boxCenter;
    float bsx2 = boxSize.x / 2.f;
    float bsy2 = boxSize.y / 2.f;
    float bsz2 = boxSize.z / 2.f;

    Vector3f line = segmentEnd - segmentStart;
    Vector3f result;

    static const Vector3f normals[] = {
        Vector3f(1, 0, 0),
        Vector3f(-1, 0, 0),
        Vector3f(0, 1, 0),
        Vector3f(0, -1, 0),
        Vector3f(0, 0, 1),
        Vector3f(0, 0, -1)};

    for(int i = 0; i < 6; ++i)
    {
        const Vector3f &normal = normals[i];

        if(line.Dot(normal) < 0 && Intersect3DSegmentPlane(segmentStart, segmentEnd, boxCenter + Vector3f(bsx2 * normal.x, bsy2 * normal.y, bsz2 * normal.z), normal, &result) == 1)
        {
            // std::cout << result << " - " << c << std::endl;
            if(IsBetween(result.x, c.x - bsx2, c.x + bsx2) && IsBetween(result.y, c.y - bsy2, c.y + bsy2) && IsBetween(result.z, c.z - bsz2, c.z + bsz2))
            {
                // std::cout << "FOUND: " << result << std::endl;
                hitPos = result;
                hitNormal = normal;
                // m_currentBlock = result;
                return true;
            }
        }
    }

    return false;
}

void Engine::InitWindow(const std::string &title, int width, int height, bool fullScreen)
{
    rl::SetConfigFlags(rl::FLAG_MSAA_4X_HINT);
    rl::SetConfigFlags(rl::FLAG_WINDOW_RESIZABLE);

    rl::InitWindow(width, height, title.c_str());

    if(fullScreen)
        rl::ToggleFullscreen();

    rl::rlDisableWireMode();

    // rl::SetTraceLogLevel(rl::LOG_WARNING);
    rl::SetTraceLogLevel(rl::LOG_ERROR);
}

void Engine::DoGameLoop()
{
    float elapsedTime = rl::GetFrameTime();

    if(rl::IsKeyPressed(rl::KEY_Y))
    {
        m_wireframe = !m_wireframe;
    }

    if(IsKeyPressed(rl::KEY_F10))
    {
        SetFullscreen(!IsFullscreen());
    }

    rl::Vector2 mousePos = rl::GetMousePosition();
    if(mousePos.x != m_lastMousePos.x || mousePos.y != m_lastMousePos.y)
    {
        // if(m_lastMousePos.x != -1)
        MouseMoveEvent(mousePos.x, mousePos.y);

        m_lastMousePos = mousePos;
    }

    rl::Camera3D camera = Update(elapsedTime);

    rl::BeginTextureMode(m_target[0]);
    {
        // rl::ClearBackground(rl::DARKGRAY);
        rl::ClearBackground(rl::BLACK);

        rl::BeginMode3D(camera);
        {
            if(m_wireframe)
                rl::rlEnableWireMode();

            Render3D(elapsedTime);

            if(m_wireframe)
                rl::rlDisableWireMode();
        }
        rl::EndMode3D();
    }
    rl::EndTextureMode();

    rl::BeginDrawing();
    {
        rl::ClearBackground(rl::RAYWHITE);

        int curTarget = 0;
        rl::DrawTextureRec(m_target[curTarget].texture, (rl::Rectangle){0, 0, (float)m_target[curTarget].texture.width, (float)-m_target[curTarget].texture.height}, (rl::Vector2){0, 0}, rl::WHITE);
        Render2D(elapsedTime);
    }
    rl::EndDrawing();
}
