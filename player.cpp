#include "player.h"
#include <cmath>

// https://learnopengl.com/Getting-started/Camera
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

Player::Player(const Vector3f &position, float rotX, float rotY) : m_position(position), m_rotX(rotX), m_rotY(rotY)
{
    UpdateCameraVectors();
}

void Player::TurnLeftRight(float value)
{
    m_rotY += value;

    UpdateCameraVectors();
}

void Player::TurnTopBottom(float value)
{
    m_rotX -= value;

    if (m_rotX < -89.f)
        m_rotX = -89.f;

    if (m_rotX > 89.f)
        m_rotX = 89.f;

    UpdateCameraVectors();
}

Vector3f Player::SimulateMove(bool front, bool back, bool left, bool right, bool run, bool fly, float elapsedTime)
{
    Vector3f delta(0, 0, 0);

    float velocity = 4.f * elapsedTime;

    if (fly)
        velocity *= 4;

    if (run)
        velocity *= 2;

    // float y = delta.y;

    Vector3f noFlyFront = m_front;
    if (!fly)
    {
        noFlyFront.y = 0;
        noFlyFront.Normalize();
    }

    if (front)
        delta += noFlyFront * velocity;
    if (back)
        delta -= noFlyFront * velocity;
    if (left)
        delta -= m_right * velocity;
    if (right)
        delta += m_right * velocity;

    // delta.y = y;

    return delta;
}

const Vector3f &Player::GetPosition() const
{
    return m_position;
}

void Player::SetPosition(const Vector3f &position)
{
    m_position = position;
}

const Vector3f &Player::Position() const
{
    return m_position;
}

const Vector3f &Player::GetEyeVector() const
{
    return m_front;
}

const rl::Camera3D &Player::GetCamera()
{

    m_camera = rl::Camera3D{};
    rl::Vector3 position = {m_position.x, m_position.y, m_position.z};
    m_camera.position = position;

    Vector3f target = m_position + m_front;
    rl::Vector3 rlTarget = {target.x, target.y, target.z};
    m_camera.target = rlTarget;

    rl::Vector3 rlUp = {m_up.x, m_up.y, m_up.z};
    m_camera.up = rlUp;
    m_camera.fovy = 75.0f;
    m_camera.projection = rl::CAMERA_PERSPECTIVE;

    return m_camera;
}

void Player::SetViewAngle(const float rotX, const float rotY)
{
    m_rotX = rotX;
    m_rotY = rotY;

    UpdateCameraVectors();
}

void Player::UpdateCameraVectors()
{
    float yrotrad = (m_rotY / 180 * 3.141592654f);
    float xrotrad = (m_rotX / 180 * 3.141592654f);

    m_front.x = cos(yrotrad) * cos(xrotrad);
    m_front.y = sin(xrotrad);
    m_front.z = sin(yrotrad) * cos(xrotrad);
    // m_front.y = 0; // TODO disable fly mode
    m_front.Normalize();

    // also re-calculate the Right and Up vector
    m_right = m_front.Cross(Vector3f(0, 1.f, 0));
    m_right.Normalize(); // glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

    m_up = m_right.Cross(m_front);
    m_up.Normalize(); // glm::normalize(glm::cross(Right, Front));
}

// Démarre un saut si le joueur n'est pas déjà en train de sauter.
void Player::Jump()
{
    if(!m_isJumping){
        m_verticalSpeed = 5.0f; 
        m_isJumping = true;
    }
}
 // Vérifie si le joueur est au sol.
bool Player::IsOnGround() const
{
    return m_position.y <=m_groundHeight +0.01f;
}
// Met à jour la position verticale du joueur en fonction de la gravité et du temps écoulé.
void Player::UpdateJump(float elapsedTime)
{
     if (m_isJumping) {
        m_verticalSpeed -= 9.8f * elapsedTime; 
        m_position.y += m_verticalSpeed * elapsedTime;


        if (m_position.y < m_groundHeight) {
            m_position.y = m_groundHeight;
            m_verticalSpeed = 0.0f;
            m_isJumping = false;
        }
    }
}