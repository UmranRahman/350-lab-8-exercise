#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // TODO: Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        /**
         * after g:  g.scale * x + g.translation
         * after f:  f.scale * (g.scale * x + g.translation) + f.translation
         * (f.scale * g.scale * x) + (f.scale * g.translation + f.translation)
         */
        sf::Vector2f cScale = f.scale * g.scale;
        sf::Vector2f cTranslation = (f.scale * g.translation) + f.translation;
        return BasicTransform(cScale, cTranslation);
    }

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        /**
         * using math notation
         * x = (y - f.scale)/f.translation
         */
        sf::Vector2f iScale = sf::Vector2f(1.0f, 1.0f)/ f.scale;
        sf::Vector2f iTranslation = -f.translation/f.scale;
        return BasicTransform(iScale, iTranslation);
    }

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif