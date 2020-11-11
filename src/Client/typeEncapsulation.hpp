//
// Created by arzeo on 10/28/2020.
//

#ifndef BABEL_TYPEENCAPSULATION_HPP
#define BABEL_TYPEENCAPSULATION_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Rtype {
    typedef sf::Vector2i vec2i;
    typedef sf::Vector2f vec2f;
    typedef sf::Vector3f vec3f;
    typedef sf::IntRect iRect;
    typedef sf::FloatRect fRect;
    typedef sf::Color color;
    typedef sf::Keyboard::Key keys;

    typedef sf::Texture Texture;
    typedef sf::Image Image;
    typedef sf::Sprite Sprite;

    template< typename T>
    class ITexture {
        public:
        virtual ~ITexture() = default;
        virtual bool loadFromFile(std::string filepath) = 0;
        virtual T &getNativ() = 0;
    };

    class sfmlTexture: public ITexture<Texture> {
        public:
        sfmlTexture() {

        }
        bool loadFromFile(std::string filepath) override
        {
            _tex.loadFromFile(filepath);
        }
        Texture &getNativ() override
        {
            return _tex;
        }
        private:
        Texture _tex;
    };

    template< typename T>
    class IImage {
        public:
        virtual ~IImage() = default;
        virtual T &getNativ() = 0;
    };

    class sfmlImage: public IImage<Image> {
        public:
        sfmlImage(unsigned width, unsigned int height, color col)
        {
            _image.create(width, height, col);
        };
        Image &getNativ() override
        {
            return _image;
        }
        private:
        Image _image;
    };

    template< typename T>
    class ISprite {
        public:
        virtual ~ISprite() = default;
        virtual T &getNativ() = 0;
    };

    class sfmlSprite: public ISprite<Sprite> {
        public:
        sfmlSprite()
        {
        };
        Sprite &getNativ() override
        {
            return _image;
        }
        private:
        Sprite _image;
    };
}  // namespace Rtype

#endif  // BABEL_TYPEENCAPSULATION_HPP
