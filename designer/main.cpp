#include <string>
#include <iostream>

#include <SDL.h>
#include <stdio.h>


class Surface {
public:
	Surface() {}
	Surface(SDL_Surface* new_surface) {
		surface_ = new_surface;
	}
	~Surface() {
		SDL_FreeSurface(surface_);
		surface_ = nullptr;
	}

	void FillRect(const SDL_Rect* rect,
		const SDL_PixelFormat* format,
		uint8_t r, uint8_t g, uint8_t b) {
		SDL_FillRect(surface_, rect, SDL_MapRGB(format, r, g, b));
	}

	SDL_Surface* ptr() {
		return surface_;
	}

	const SDL_PixelFormat* Format() {
		return surface_->format;
	}

private:
	SDL_Surface* surface_{ nullptr };
};


class Window {
public:
	Window() {}
	~Window() {
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}

	void Create(
		const std::string& name,
		const int32_t& x, const int32_t& y,
		const int32_t& width, const int32_t& height,
		const uint32_t& flags) {
		window_ = SDL_CreateWindow(name.c_str(),
			x, y, width, height, flags);
	}

	bool IsNullptr() {
		return window_ == nullptr;
	}

	Surface GetSurface() {
		return { SDL_GetWindowSurface(window_) };
	}

	void UpdateSurface() {
		SDL_UpdateWindowSurface(window_);
	}

	SDL_Window* ptr() {
		return window_;
	}

private:
	SDL_Window* window_{ nullptr };
};


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	Window window;
	Surface screenSurface;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	else {
		window.Create("SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window.IsNullptr())
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		else {
			screenSurface = window.GetSurface();
			screenSurface.FillRect(nullptr, screenSurface.Format(), 225, 255, 128);
			window.UpdateSurface();

			SDL_Event e;
			bool quit = false;
			while (quit == false) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) quit = true;
				}
			}
		}
	}

	SDL_Quit();

	return 0;
}
