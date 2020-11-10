#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

typedef uint32_t TextureID;

struct TextureLibraryComponent {
    std::unordered_map<TextureID, sf::Texture> TextureMap;
};

struct TextureComponent {
    TextureID id;
};