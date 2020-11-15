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
            std::string path("./");
            path.append(name);
            path.append("Factory");
#ifdef _WIN32
            path.append(".dll");
#else
            path.append(".so");
#endif
            for (auto& f : *_factories.get()) {
                std::string current_name = (*(f.get()))->getName();
                if (name == current_name) {
                    return false;
                }
            }
            _factories->emplace_back(std::make_shared<DynamicLoader<RType::IEntityFactory>>(path));
            return true;
        }

    private:
        std::string _path;
        std::shared_ptr<std::vector<std::shared_ptr<DynamicLoader<IEntityFactory>>>>& _factories;
    };
} // namespace RType
