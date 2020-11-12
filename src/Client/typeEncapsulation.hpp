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
    typedef sf::Transform Transform;
    typedef sf::RenderStates RenderState;

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
            return _tex.loadFromFile(filepath);
        }

        Texture &getNativ() override
        {
            return _tex;
        }
        private:
        Texture _tex;
    };

    template< typename T>
    class ISprite {
        public:
        virtual ~ISprite() = default;
        virtual void setTexture(Rtype::Texture& tex) = 0;
        virtual void setTextureRect(Rtype::iRect& rect) = 0;
        virtual void setOrigin(Rtype::vec2f& vec) = 0;
        virtual void centerOrigin() = 0;
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

        void setTexture(Rtype::Texture& tex)
        {
            _image.setTexture(tex);
        }

        void setTextureRect(Rtype::iRect& rect)
        {
            _image.setTextureRect(rect);
        }

        void setOrigin(Rtype::vec2f& vec)
        {
            _image.setOrigin(vec);
        }

        void centerOrigin()
        {
            sf::IntRect bound = _image.getTextureRect();
            _image.setOrigin(bound.width / 2.f, bound.height / 2.f);
        }

        private:
        Sprite _image;
    };

    template< typename T>
    class ITransform {
        public:
        virtual ~ITransform() = default;
        virtual ITransform<T>& translate(vec2f) = 0;
        virtual ITransform<T>& scale(vec2f) = 0;
        virtual ITransform<T>& rotate(float) = 0;
        virtual T &getNativ() = 0;
    };

    class sfmlTransform: public ITransform<Transform> {
        public:
        sfmlTransform()
        {
        };

        Transform &getNativ() override
        {
            return _mat;
        }

        sfmlTransform& translate(vec2f trans) override
        {
            _mat.translate(trans);
            return *this;
        }

        sfmlTransform& scale(vec2f scale) override
        {
            _mat.scale(scale);
            return *this;
        }

        sfmlTransform& rotate(float angle) override
        {
            _mat.rotate(angle);
            return *this;
        }

        private:
        Transform _mat;
    };

    template< typename T>
    class IRenderState {
        public:
        virtual ~IRenderState() = default;
        virtual void setMatrix(Rtype::Transform mat) = 0;
        virtual T &getNativ() = 0;
    };

    class sfmlRenderState: public IRenderState<RenderState> {
        public:
        sfmlRenderState()
        {
        };

        RenderState &getNativ() override
        {
            return _state;
        }

        void setMatrix(Rtype::Transform mat)
        {
            _state.transform = mat;
        }

        private:
        RenderState _state;
    };
}  // namespace Rtype

#endif  // BABEL_TYPEENCAPSULATION_HPP
