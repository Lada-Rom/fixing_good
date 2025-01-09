#ifndef MAGIC_SETTINGS_HPP
#define MAGIC_SETTINGS_HPP

struct AppSettings {
    std::string window_name{ "Magic I(v)an" };
    size_t window_width{ 800 };
    size_t window_height{ 600 };

    real32 target_fps{ 30.f };
};

#endif  // !MAGIC_SETTINGS_HPP
