#include "window.hpp"

Window::Window() {}

Window::~Window() {
	SDL_DestroyWindow(window_);
	window_ = nullptr;
}

void Window::Create(
	const std::string& name,
	const int32_t& x,
	const int32_t& y,
	const int32_t& width,
	const int32_t& height,
	const uint32_t& flags) {
	window_ = SDL_CreateWindow(name.c_str(),
		x, y, width, height, flags);
}

bool Window::IsNullptr() {
	return window_ == nullptr;
}

Surface Window::GetSurface() {
	return { SDL_GetWindowSurface(window_) };
}

void Window::UpdateSurface() {
	SDL_UpdateWindowSurface(window_);
}

SDL_Window* Window::ptr() {
	return window_;
}
