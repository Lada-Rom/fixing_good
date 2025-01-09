#ifndef MAGIC_FPS_HPP
#define MAGIC_FPS_HPP

#include <iostream>
#include <sstream>

#include "common/types.hpp"
#include "settings.hpp"
#include "timer.hpp"


class FPSControl {
public:
    FPSControl() = delete;
    FPSControl(AppSettings& app_settings) : settings(app_settings) {}
    ~FPSControl() = default;

    void StartGeneralTimer() {
        fps_count_timer.start();
    }

    void StartFrameTimer() {
        fps_bound_timer.stop();
        fps_bound_timer.reset();
        fps_bound_timer.start();
    }

    real32 GetFrameTime() {
        return frame_time;
    }

    void CalcAvgFPS() {
        ++frames_count;
        real32 general_time = fps_count_timer.getElapsedTime() * 1e-9f;
        avg_fps = frames_count / general_time;

        fps_info.str(std::string());
        fps_info << "FRAMES " << frames_count << " TIME " << general_time << " AVG " << avg_fps << std::endl;
        SDL_Log(fps_info.str().c_str());
    }

    void BoundFPS() {
        //SDL_Delay(1000);
        frame_time = fps_bound_timer.getElapsedTime() * 1e-9f;
        real32 target_frame_time = 1.f / settings.target_fps;

        fps_info.str(std::string());
        fps_info << "TIME " << frame_time << " TICK " << target_frame_time << std::endl;
        SDL_Log(fps_info.str().c_str());

        if (frame_time < target_frame_time) {
            SDL_Delay((target_frame_time - frame_time) * 1e3f);
            frame_time += (target_frame_time - frame_time);
        }
    }

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
