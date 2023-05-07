#include "texture_manager.h"
#include "SDL_image.h"

namespace { // anonymous

std::map<std::string_view, SDL_Texture*> m_texture_map;

} // anonymous

namespace TextureManager {

bool Load(const std::string_view& fileName, const std::string_view& id,
          SDL_Renderer* pRenderer) {
    SDL_Texture* pTexture = IMG_LoadTexture(pRenderer, fileName.data());
    if(pTexture != 0) {
        m_texture_map[id] = pTexture;
        return true;
    }
    return false;
}

void Draw(const std::string_view& id, uu::sint32 x, uu::sint32 y,
          uu::sint32 width, uu::sint32 height,
          SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect { 0, 0, width, height };
    SDL_Rect dstRect { x, y, width, height };
    uu::real64 angle(0);

    SDL_RenderCopyEx(pRenderer, m_texture_map[id], &srcRect, &dstRect, angle,
                     NULL, flip); // NULL - rotation around (w/2, h/2)
}

void DrawFrame(const std::string_view &id, uu::sint32 x, uu::sint32 y,
               uu::sint32 width, uu::sint32 height,
               uu::sint32 currentRow, uu::sint32 currentFrame,
               SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect { width * currentFrame, height * (currentRow - 1),
                       width, height };
    SDL_Rect dstRect { x, y, width, height };
    uu::real64 angle(0);
    SDL_RenderCopyEx(pRenderer, m_texture_map[id], &srcRect, &dstRect, angle,
                     NULL, flip); // NULL - rotation around (w/2, h/2)
}

void ClearFromTextureMap(const std::string_view& id) {
    m_texture_map.erase(id);
}


}


int main(int argc, char** args) {
    return 0;
}
