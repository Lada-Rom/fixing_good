#include "window.hpp"

Window::~Window() {
  if (!IsNullptr())
    SDL_DestroyWindow(window_);
  window_ = nullptr;
}

Window::Window(
  const std::string& name,
  const int32_t& x,
  const int32_t& y,
  const int32_t& width,
  const int32_t& height,
  const uint32_t& flags) {
  window_ = SDL_CreateWindow(name.c_str(),
    x, y, width, height, flags);
  if (IsNullptr())
    throw std::runtime_error("Failed to create window!");
}

bool Window::IsNullptr() {
  return !window_;
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
