#include "surface.hpp"

Surface::Surface(SDL_Surface* new_surface) {
  surface_ = new_surface;
}

Surface::~Surface() {
  if (!IsNullptr())
    SDL_FreeSurface(surface_);
  surface_ = nullptr;
}

bool Surface::IsNullptr() {
  return !surface_;
}

void Surface::FillRect(
  const SDL_Rect* rect,
  const SDL_PixelFormat* format,
  uint8_t r,
  uint8_t g,
  uint8_t b) {
  SDL_FillRect(surface_, rect, SDL_MapRGB(format, r, g, b));
}

SDL_Surface* Surface::ptr() {
  return surface_;
}

const SDL_PixelFormat* Surface::Format() {
  return surface_->format;
}
