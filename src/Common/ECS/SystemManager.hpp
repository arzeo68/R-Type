#pragma once

#include <memory>
#include <unordered_map>
#include "System.hpp"
#include "Types.h"

namespace ECS
{

class SystemManager
{
    public:

        template<typename T>
        std::shared_ptr<T> registerSystem(std::vector<ComponentType>& ignored_component_types)
        {
            std::size_t id = typeid(T).hash_code();

            if (m_cSystems.find(id) != m_cSystems.end())
                return nullptr;
            auto system = std::make_shared<T>();
            system->m_cIgnoredComponents = std::move(ignored_component_types);
            m_cSystems.insert({id, system});
            return system;
        }

        template<typename T>
        void setSignature(Signature signature)
        {
            std::size_t id = typeid(T).hash_code();

            if (m_cSystems.find(id) == m_cSystems.end())
                return;
            m_cSignatures.insert({id, signature});
        }

        void notifyEntityDestroyed(Entity entity)
        {
            for (auto const& pair : m_cSystems) {
                auto const& system = pair.second;

                system->m_cEntities.erase(entity);
            }
        }

        template<typename T>
        void subscribe(Entity entity, Signature entitySignature)
        {
            std::size_t id = typeid(T).hash_code();

            if (m_cSystems.find(id) == m_cSystems.end())
                return;
            Signature sys_signature = *m_cSignatures.find(id);
            if ((entitySignature & sys_signature) == sys_signature) {
                m_cSystems[id]->m_cEntities.insert(entity);
            }
        }

        void notifyEntitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for (auto const& pair : m_cSystems) {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& signature = m_cSignatures[type];

                if ((entitySignature & signature) == signature && checkForIgnoredComponents(entitySignature, system->m_cIgnoredComponents))
                    system->m_cEntities.insert(entity);
                else
                    system->m_cEntities.erase(entity);
            }
        }

        template<typename T>
        std::shared_ptr<System> getSystem()
        {
            std::size_t id = typeid(T).hash_code();
            auto ite = m_cSystems.find(id);

            if (ite == m_cSystems.end())
                return nullptr;
            return ite->second;
        }
    private:
        std::unordered_map<std::size_t, Signature> m_cSignatures { };
        std::unordered_map<std::size_t, std::shared_ptr<System>> m_cSystems { };

        bool checkForIgnoredComponents(Signature entitySignature, std::vector<ComponentType> const& ignoredComponents)
        {
            if (ignoredComponents.empty())
                return true;
            for (auto const& type : ignoredComponents) {
                if (entitySignature.test(type))
                    return false;
            }
            return true;
        }
};

} // namespace ECS
