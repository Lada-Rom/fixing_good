#include "player.hpp"

void Player::SetRunningRight() {
  m_direction[RIGHT] = true;
}

void Player::SetRunningLeft() {
  m_direction[LEFT] = true;
}

void Player::SetRunningUp() {
  m_direction[UP] = true;
}

void Player::SetRunningDown() {
  m_direction[DOWN] = true;
}

bool Player::IsRunningRight() {
  return m_direction[RIGHT];
}

bool Player::IsRunningLeft() {
  return m_direction[LEFT];
}

bool Player::IsRunningUp() {
  return m_direction[UP];
}

bool Player::IsRunningDown() {
  return m_direction[DOWN];
}

void Player::StopRunningRight() {
  m_direction[RIGHT] = false;
}

void Player::StopRunningLeft() {
  m_direction[LEFT] = false;
}

void Player::StopRunningUp() {
  m_direction[UP] = false;
}

void Player::StopRunningDown() {
  m_direction[DOWN] = false;
}

void Player::MoveRight(
  const uu::uint32& frame_delta,
  const uu::real32& max_width) {
  x += frame_delta * m_velocity;
  if (x > max_width)
    x = -50;
}

void Player::MoveLeft(
  const uu::uint32& frame_delta,
  const uu::real32& max_width) {
  x -= frame_delta * m_velocity;
  if (x < -50)
    x = max_width;
}

void Player::MoveUp(
  const uu::uint32& frame_delta,
  const uu::real32& max_height) {
  y -= frame_delta * m_velocity;
  if (y < -50)
    y = max_height;
}

void Player::MoveDown(
  const uu::uint32& frame_delta,
  const uu::real32& max_height) {
  y += frame_delta * m_velocity;
  if (y > max_height)
    y = -50;
}
