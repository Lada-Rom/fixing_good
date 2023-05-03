#include <utility>

#include "texture_manager.h"
#include "SDL_image.h"

namespace { // anonymous

std::map<std::string_view, pp::Texture> m_texture_map{};

} // anonymous

namespace TextureManager {

void Load(const std::string_view& fileName,
          const std::string_view& id,
          pp::Renderer& renderer) {
  pp::Texture pTexture(renderer, fileName.data());
  m_texture_map[id] = std::move(pTexture);
}

void Draw(const std::string_view& id, uu::sint32 x, uu::sint32 y,
          uu::sint32 width, uu::sint32 height,
          pp::Renderer& renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect { 0, 0, width, height };
    SDL_Rect dstRect { x, y, width, height };
    uu::real64 angle(0);

    renderer.Copy(m_texture_map[id], srcRect, dstRect, angle,
      pp::NullOpt, flip); // NullOpt - rotation around (w/2, h/2)
}

void DrawFrame(const std::string_view &id, uu::sint32 x, uu::sint32 y,
               uu::sint32 width, uu::sint32 height,
               uu::sint32 currentRow, uu::sint32 currentFrame,
               pp::Renderer& renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect { width * currentFrame, height * (currentRow - 1),
                       width, height };
    SDL_Rect dstRect { x, y, width, height };
    uu::real64 angle(0);
    renderer.Copy(m_texture_map[id], srcRect, dstRect, angle,
      pp::NullOpt, flip); // NullOpt - rotation around (w/2, h/2)
}

void ClearFromTextureMap(const std::string_view& id) {
    m_texture_map.erase(id);
}

}
