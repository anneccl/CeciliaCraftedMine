#ifndef ENGINE_H
#define ENGINE_H

#include "define.h"
#include "vector3.h"

#include <string>
#include <vector>

class Engine
{
public:
    enum MOUSE_BUTTON
    {
        MOUSE_BUTTON_NONE = 0x00,
        MOUSE_BUTTON_LEFT = 0x01,
        MOUSE_BUTTON_MIDDLE = 0x02,
        MOUSE_BUTTON_RIGHT = 0x04,
        MOUSE_BUTTON_WHEEL_UP = 0x08,
        MOUSE_BUTTON_WHEEL_DOWN = 0x10
    };
    Engine();
    virtual ~Engine();

    virtual void Init() = 0;
    virtual void DeInit() = 0;
    virtual void LoadResource() = 0;
    virtual void UnloadResource() = 0;
    virtual rl::Camera3D Update(float elapsedTime) = 0;
    virtual void Render3D(float elapsedTime) = 0;
    virtual void Render2D(float elapsedTime) = 0;
    virtual void MouseMoveEvent(int x, int y) = 0;

    bool Start(const std::string &title, int width, int height, bool fullscreen);
    bool Stop();

    int Width() const;
    int Height() const;

    void SetMaxFps(int maxFps);

    void SetFullscreen(bool fullscreen);
    bool IsFullscreen() const;

    bool IsWireframe() const;

protected:
    void LockCursor();
    void UnlockCursor();

    void ShowCursor();
    void HideCursor();

    void TakeScreenshot(const std::string &filename) const;

    // http://geomalgorithms.com/a05-_intersect-1.html
    int Intersect3DSegmentPlane(Vector3f segmentStart, Vector3f segmentEnd, Vector3f planePoint, Vector3f planeNormal, Vector3f *I);
    bool IsBetween(float value, float min, float max);
    bool AABBSegmentIntersect(Vector3f boxCenter, Vector3f boxSize, Vector3f segmentStart, Vector3f segmentEnd, Vector3f &hitPos, Vector3f &hitNormal);

private:
    void InitWindow(const std::string &title, int width, int height, bool fullScreen);
    void DoGameLoop();

private:
    bool m_wireframe = false;
    rl::Vector2 m_lastMousePos = {-1, 0};

    rl::RenderTexture2D m_target[2];
    std::vector<rl::Shader> m_postProcessingShaders;
};

#endif /* ENGINE_H */
