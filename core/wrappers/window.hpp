#ifndef FG_WINDOW_HPP
#define FG_WINDOW_HPP

#include <string>

#include <SDL.h>

#include "surface.hpp"

class Window {
public:
	Window();
	~Window();

	void Create(
		const std::string& name,
		const int32_t& x,
		const int32_t& y,
		const int32_t& width,
		const int32_t& height,
		const uint32_t& flags);

	bool IsNullptr();

	Surface GetSurface();

	void UpdateSurface();

	SDL_Window* ptr();

private:
	SDL_Window* window_{ nullptr };
};

#endif // !FG_WINDOW_HPP
