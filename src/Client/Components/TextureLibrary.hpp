#include <unordered_map>
#include <memory>
#include "../typeEncapsulation.hpp"

typedef uint32_t TextureID;

struct TextureLibraryComponent {
    std::unordered_map<TextureID, std::shared_ptr<Rtype::Texture>> TextureMap;
    std::unordered_map<std::string, TextureID> TextureNameMap;
    size_t NextTextureID = 1;

    TextureLibraryComponent() = default;

    TextureID load_texture(std::string const& name, std::string const& path)
    {
        TextureID save = NextTextureID;
        std::shared_ptr<Rtype::Texture> tex =
            new std::make_shared<Rtype::Texture>();

        if (!tex->loadFromFile(path))
            return 0;
        TextureNameMap.insert({name, NextTextureID});
        TextureMap.insert({NextTextureID++, std::move(tex)});
        return save;
    }

    void load_default_texture(std::string const& name, std::string const& path)
    {
        TextureID save = 0;
        std::shared_ptr<Rtype::Texture> tex =
            new std::make_shared<Rtype::Texture>();

        if (!tex->loadFromFile(path))
            return 0;
        TextureNameMap.insert({name, save});
        TextureMap.insert({save, std::move(tex)});
        return save;
    }

    void load_default_texture(std::string const& name)
    {
        Rtype::Image img;
        TextureID save = 0;
        std::shared_ptr<Rtype::Texture> tex =
            new std::make_shared<Rtype::Texture>();

        img.create(256, 256, Rtype::color::White);
        if (!tex->loadFromImage(img))
            return UINT32_MAX;
        TextureNameMap.insert({name, save});
        TextureMap.insert({save, std::move(tex)});
        return save;
    }
};

struct TextureComponent {
    TextureID id;
};