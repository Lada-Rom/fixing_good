#include "fps.hpp"

void FPSControl::StartGeneralTimer() {
    fps_count_timer.start();
}

void FPSControl::StartFrameTimer() {
    fps_bound_timer.stop();
    fps_bound_timer.reset();
    fps_bound_timer.start();
}

real32 FPSControl::GetFrameTime() const {
    return frame_time;
}

void FPSControl::CalcAvgFPS() {
    ++frames_count;
    real32 general_time = fps_count_timer.getElapsedTime() * 1e-9f;
    avg_fps = frames_count / general_time;

    fps_info.str(std::string());
    fps_info << "FRAMES " << frames_count << " TIME " << general_time << " AVG " << avg_fps << std::endl;
    SDL_Log(fps_info.str().c_str());
}

void FPSControl::BoundFPS() {
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
