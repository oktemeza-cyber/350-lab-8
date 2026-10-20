// maybe something here...
#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // methods...
    BasicTransform(sf::Vector2f scale = sf::Vector2f(1.f, 1.f), sf::Vector2f translation = sf::Vector2f(0, 0)): scale(scale), translation(translation){}

    sf::Vector2f applyPoint(const sf::Vector2f& p) const{
        sf::Vector2f newPoint(p.x * scale.x + translation.x, p.y * scale.y + translation.y);
        return newPoint;
        
    }

    sf::Vector2f applyVector(const sf::Vector2f& p) const{
        return sf::Vector2f(p.x * scale.x, p.y * scale.y);
    }

    bool operator==(const BasicTransform& other) const {
        return (scale == other.scale && translation == other.translation); 
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};
