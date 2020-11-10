#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

struct TextureLibrarySingletonComponent {
    TextureLibrarySingletonComponent() = default;

    uint32_t request_texture_id(std::string const& path)
    {
        auto ite = pathMap.find(path);
        if (ite != pathMap.end()) {
            return ite->second;
        }
        return 0;
    }

    std::shared_ptr<sf::Texture> request_texture(std::string const& path)
    {
        auto ite = pathMap.find(path);
        if (ite != pathMap.end()) {
            std::cout << "Found texture " << path << " id : " << ite->second << "\n";
            return textureMap.find((*ite).second)->second;
        }
        std::cout << "Failed to find texture " << path << " falling back to " << pathMap.at("Fallback") << "\n";
        return textureMap.at(0);
    }

    sf::Texture& request_texture(uint32_t id)
    {
        auto ite = textureMap.find(id);
        if (ite != textureMap.end()) {
            return ite->second;
        }
        return textureMap.at(0);
    }

    void add_texture(std::string const& path)
    {
        sf::Texture tmp;

        if (tmp.loadFromFile(path)) {
            textureMap.insert({next_texture_id, std::move(tmp)});
            pathMap.insert({path, next_texture_id});
            next_texture_id += 1;
        }
    }

    void add_default_fallback_texture()
    {
        sf::Image i;
        i.create(256, 256, sf::Color::Red);

        sf::Texture t;
        t.loadFromImage(i);
        textureMap.insert({0, std::move(t)});
        pathMap.insert({"Fallback", 0});
    }

    std::unordered_map<uint32_t, std::shared_ptr<sf::Texture>> textureMap;
    std::unordered_map<std::string, uint32_t> pathMap;
    uint32_t next_texture_id = 1;
};

struct TextureReferenceComponent {
    TextureReferenceComponent() = default;

    TextureReferenceComponent(TextureLibrarySingletonComponent texlib, std::string const& path)
    {
        id = texlib.request_texture_id(path);
    }

    uint32_t id;
};