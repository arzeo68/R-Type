#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <Server/EntityLib/IEntityFactory.hpp>
#include <Server/EntityLib/DynamicLoader.hpp>

namespace RType
{
    class ConfigFile {
    public:
        ConfigFile(std::string const& path, std::shared_ptr<std::vector<std::shared_ptr<DynamicLoader<IEntityFactory>>>>& factories)
            : _path(path), _factories(factories)
        {
            std::ifstream file(path);

            if (!file.is_open())
                return;

            std::string data;
            while (std::getline(file, data)) {
                std::cout << "Loading " << data << "\n";
                load(data);
                data.clear();
            }
            file.close();
        }

        ~ConfigFile() = default;

        bool load(std::string const& name)
        {
            std::string path("../../ressources/ennemies/");
            path.append(name);
            path.append("Factory");
#ifdef _WIN32
            path.append(".dll");
#else
            path.append(".so");
#endif
            if (_factories->empty()) {
                _factories->emplace_back(std::make_shared<DynamicLoader<RType::IEntityFactory>>(path));
            }
            /* for (auto& f : *_factories.get()) {
                std::cout << "NAME : " << (*(f.get()))->getName() << "\n";
                if (name == (*(f.get()))->getName()) {
                    std::string path("../../ressources/ennemies/");
                    path.append(name);
                    path.append("Factory");
#ifdef _WIN32
                    path.append(".dll");
#else
                    path.append(".so");
#endif
                    std::fstream f(path);
                    if (f.is_open()) {
                        _factories->emplace_back(path);
                        f.close();
                        return true;
                    }
                }
            } */
            return false;
        }

    private:
        std::string _path;
        std::shared_ptr<std::vector<std::shared_ptr<DynamicLoader<IEntityFactory>>>>& _factories;
    };
} // namespace RType
