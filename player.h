#ifndef PLAYER_H
#define PLAYER_H

#include "define.h"
#include "vector3.h"
#include <cmath>
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

    // Méthode pour le saut.
    void Jump();
    bool IsOnGround() const;
    void UpdateJump(float elapsedTime);

private:
    void UpdateCameraVectors();

private:
    Vector3f m_position, m_front, m_up, m_right;
    float m_rotX, m_rotY;

    rl::Camera3D m_camera;

    bool m_isJumping = false;
    float m_verticalSpeed = 0.0f;
    float m_groundHeight = 0.0f;
};

#endif /* PLAYER_H */
