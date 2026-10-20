#ifndef SPRITE_H
#define SPRITE_H

#include "basic_transform.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Sprite {  // could derive from sf::Drawable if you're willing to pay for a vptr, but not
                // necessary.
public:
    Sprite(const sf::Texture& texture) {
        mTexture = &texture;
        mMinPointTex = sf::Vector2f(0.f, 0.f);
        mMaxPointTex = sf::Vector2f(mTexture->getSize().x, mTexture->getSize().y);
        mOrigin = sf::Vector2f(0.f, 0.f);
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        mVertexArray.resize(6);
    }

    Sprite(const sf::Texture& texture, const sf::Vector2f& texMinPoint,
           const sf::Vector2f& texMaxPoint) {
        mMinPointTex = texMinPoint;
        mMaxPointTex = texMaxPoint;
        mTexture = &texture;
        mOrigin = sf::Vector2f(0.f, 0.f);
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        mVertexArray.resize(6);    
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        recomputeVertexArray();
        states.texture = mTexture;
        target.draw(mVertexArray, states);
    }

    sf::Vector2f& position() { return mTransform.translation; }
    const sf::Vector2f& position() const { return mTransform.translation; }
    sf::Vector2f& scale() { return mTransform.scale; }
    const sf::Vector2f& scale() const { return mTransform.scale; }
    sf::Vector2f& origin() { return mOrigin; }
    const sf::Vector2f& origin() const { return mOrigin; }

private:
    static constexpr std::array<sf::Vector2f, 6> DEFAULT_VERTICES = {sf::Vector2f(0, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 0),
                                                                     sf::Vector2f(1, 1), sf::Vector2f(1, 0), sf::Vector2f(0, 1)};  
    void recomputeVertexArray() const {
        if(mTexture == nullptr){
            return;
        }

        for(int i=0; i < 6; i++){
            sf::Vector2f d = DEFAULT_VERTICES[i];
            mVertexArray[i].texCoords.x = (mMinPointTex.x + d.x * (mMaxPointTex.x - mMinPointTex.x));
            mVertexArray[i].texCoords.y = (mMinPointTex.y + d.y * (mMaxPointTex.y - mMinPointTex.y));

            mVertexArray[i].position = mTransform.applyPoint(mVertexArray[i].texCoords - (mMinPointTex + mOrigin));
        }
        
    }

    const sf::Texture* mTexture;
    mutable sf::VertexArray mVertexArray;  // geometry, uv coords -- mutable means it can be changed
                                           //  even in const methods.
    sf::Vector2f mMinPointTex;             // AABB for subtexture min point along both x, y
    sf::Vector2f mMaxPointTex;             // AABB for subtexture max point along both x, y
    sf::Vector2f mOrigin;  // position in tex coords of the sprite origin, relative to minPoint
    BasicTransform mTransform;
};

#endif
