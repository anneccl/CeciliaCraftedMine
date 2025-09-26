#ifndef PLAYER_H
#define PLAYER_H

#include "define.h"
#include "vector3.h"
class Player
{
public:
    Player(const Vector3f &position, float rotX = 0, float rotY = 0);
    void TurnLeftRight(float value);
    void TurnTopBottom(float value);
    Vector3f SimulateMove(bool front, bool back, bool left, bool right, bool run, bool fly, float elapsedTime);

    const Vector3f &GetPosition() const;
    void SetPosition(const Vector3f &position);

    const Vector3f &Position() const;
    const Vector3f &GetEyeVector() const;

    const rl::Camera3D &GetCamera();

    void SetViewAngle(const float rotX, const float rotY);

private:
    void UpdateCameraVectors();

private:
    Vector3f m_position, m_front, m_up, m_right;
    float m_rotX, m_rotY;

    rl::Camera3D m_camera;
};

#endif /* PLAYER_H */
