#include <unordered_map>
#include <memory>
#include "../typeEncapsulation.hpp"

typedef uint32_t TextureID;

struct TextureLibraryComponent {
    std::unordered_map<TextureID, std::shared_ptr<Rtype::Texture>> TextureMap;
    std::unordered_map<std::string, TextureID> TextureNameMap;
    TextureID NextTextureID = 1;

    TextureLibraryComponent() = default;

    TextureID load_texture(std::string const& name, std::string const& path)
    {
        TextureID save = NextTextureID;
        std::shared_ptr<Rtype::Texture> tex = std::make_shared<Rtype::Texture>();

        if (!tex->loadFromFile(path))
            return 0;
        TextureNameMap.insert({name, NextTextureID});
        TextureMap.insert({NextTextureID++, std::move(tex)});
        return save;
    }

    void load_default_texture(std::string const& name, std::string const& path)
    {
        TextureID save = 0;
        std::shared_ptr<Rtype::Texture> tex = std::make_shared<Rtype::Texture>();

        if (!tex->loadFromFile(path))
            return;
        TextureNameMap.insert({name, save});
        TextureMap.insert({save, std::move(tex)});
        return;
    }

    void load_default_texture(std::string const& name)
    {
        Rtype::Image img;
        TextureID save = 0;
        std::shared_ptr<Rtype::Texture> tex = std::make_shared<Rtype::Texture>();

        img.create(256, 256, Rtype::color::White);
        if (!tex->loadFromImage(img))
            return;
        TextureNameMap.insert({name, save});
        TextureMap.insert({save, std::move(tex)});
        return;
    }

    TextureID get_texture_id(std::string const& name)
    {
        auto ite = TextureNameMap.find(name);
        if (ite != TextureNameMap.end()) {
            return ite->second;
        }
        return 0;
    }
};

struct TextureComponent {
    TextureID id;

    TextureComponent() : id(0) {}
    TextureComponent(TextureID id) : id(id) {}
};