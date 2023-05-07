#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <string_view>
#include <map>
#include <SDL.h>
#ifdef _WIN32
    #include <SDL_main.h>
#endif
#include <SDL2pp/SDL2pp.hh>
#include "framework_ish/specifictypes.h"

namespace uu = user_utils;

namespace { // anonymous

extern std::map<std::string_view, SDL_Texture*> m_texture_map;

} // anonymous

namespace TextureManager {

bool Load(const std::string_view& file_name, const std::string_view& id,
          SDL_Renderer *pRenderer);

void Draw(const std::string_view& id, uu::sint32 x, uu::sint32 y,
          uu::sint32 width, uu::sint32 height,
          SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

void DrawFrame(const std::string_view& id, uu::sint32 x, uu::sint32 y,
               uu::sint32 width, uu::sint32 height,
               uu::sint32 currentRow, uu::sint32 currentFrame,
               SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

void ClearFromTextureMap(const std::string_view& id);

} // TextureManager

#endif // !__TEXTURE_MANAGER__
