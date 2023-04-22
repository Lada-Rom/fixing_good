#ifndef FG_SURFACE_HPP
#define FG_SURFACE_HPP

#include <SDL.h>

class Surface {
public:
	Surface();
	Surface(SDL_Surface* new_surface);
	~Surface();

	void FillRect(
		const SDL_Rect* rect,
		const SDL_PixelFormat* format,
		uint8_t r,
		uint8_t g,
		uint8_t b);

	SDL_Surface* ptr();

	const SDL_PixelFormat* Format();

private:
	SDL_Surface* surface_{ nullptr };
};

#endif // !FG_SURFACE_HPP
