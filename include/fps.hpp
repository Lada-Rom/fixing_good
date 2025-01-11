#ifndef MAGIC_FPS_HPP
#define MAGIC_FPS_HPP

#include <iostream>
#include <sstream>

#include "common/types.hpp"
#include "settings.hpp"
#include "timer.hpp"


// TODO:
// Maybe we need a Fixed time steps
class FPSControl {
public:
    FPSControl() = delete;
    FPSControl(AppSettings& app_settings) : settings(app_settings) {}
    ~FPSControl() = default;

    void StartGeneralTimer();
    void StartFrameTimer();
    real32 GetFrameTime() const;

    void CalcAvgFPS();
    void BoundFPS();

private:
    AppSettings settings{};

    Timer fps_count_timer{};
    Timer fps_bound_timer{};

    size_t frames_count{};
    real32 frame_time{};
    real32 avg_fps{};

    std::stringstream fps_info;
};

#endif  // !MAGIC_FPS_HPP
