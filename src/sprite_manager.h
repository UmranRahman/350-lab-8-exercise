#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>

#include <cstddef>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        // if filepath is already in mTextures, return it.
        // otherwise construct the texture and return it.
        auto it = mTextures.find(filepath);
        if (it != mTextures.end()) {
            return it->second;// already loaded
        }
        auto result = mTextures.emplace(filepath, sf::Texture(filepath));
        return result.first->second;
    }

    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        // emplace_back with std::forward<Args>(args)...
        // return the new sprite's index
        mSprites.emplace_back(std::forward<Args>(args)...);
        return mSprites.size() - 1;
    }

    Sprite& getSprite(SpriteID id) {
        return mSprites[id];
    }

private:
    std::unordered_map<std::string, sf::Texture> mTextures;
    std::deque<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
