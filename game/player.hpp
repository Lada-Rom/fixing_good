#ifndef FG_PLAYER_HPP
#define FG_PLAYER_HPP

#include <vector>

#include "framework_ish/specifictypes.h"

namespace uu = user_utils;

class Player {
public:
  enum Running { RIGHT, LEFT, UP, DOWN };

  Player() = default;
  Player(
    const uu::real64& x,
    const uu::real64& y)
    : x(x), y(y) {}

  void SetRunningRight();
  void SetRunningLeft();
  void SetRunningUp();
  void SetRunningDown();

  bool IsRunningRight();
  bool IsRunningLeft();
  bool IsRunningUp();
  bool IsRunningDown();

  void StopRunningRight();
  void StopRunningLeft();
  void StopRunningUp();
  void StopRunningDown();

  void MoveRight(
    const uu::uint32& frame_delta,
    const uu::real32& max_width);

  void MoveLeft(
    const uu::uint32& frame_delta,
    const uu::real32& max_width);

  void MoveUp(
    const uu::uint32& frame_delta,
    const uu::real32& max_height);

  void MoveDown(
    const uu::uint32& frame_delta,
    const uu::real32& max_height);

  uu::real32 x{};
  uu::real32 y{};

private:
  std::vector<bool> m_direction{ false, false, false, false };
  uu::real32 m_velocity{ 0.2 };
};

#endif  // !FG_PLAYER_HPP
