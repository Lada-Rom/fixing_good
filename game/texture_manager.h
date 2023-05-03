#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <string_view>
#include <map>
#include "SDL.h"
#include "framework_ish/specifictypes.h"

#include <SDL2pp/SDL2pp.hh>

namespace uu = user_utils;
namespace pp = SDL2pp;

namespace { // anonymous

extern std::map<std::string_view, pp::Texture> m_texture_map;

} // anonymous

namespace TextureManager {

void Load(const std::string_view& file_name,
          const std::string_view& id,
          pp::Renderer& renderer);

void Draw(const std::string_view& id, uu::sint32 x, uu::sint32 y,
          uu::sint32 width, uu::sint32 height,
          pp::Renderer& renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

void DrawFrame(const std::string_view& id, uu::sint32 x, uu::sint32 y,
               uu::sint32 width, uu::sint32 height,
               uu::sint32 currentRow, uu::sint32 currentFrame,
               pp::Renderer& renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

void ClearFromTextureMap(const std::string_view& id);

} // TextureManager

#endif // !__TEXTURE_MANAGER__
