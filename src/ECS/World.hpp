#pragma once

#include <memory>
#include <typeindex>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "SingletonComponentCollection.hpp"

namespace ECS
{

class World
{
    public:
        void initialize()
        {
            m_ComponentManager = std::make_shared<ComponentManager>();
            m_EntityManager = std::make_shared<EntityManager>();
            m_SystemManager = std::make_shared<SystemManager>();
        }

        Entity createEntity() { return m_EntityManager->createEntity(); }

        void destroyEntity(Entity entity)
        {
            m_EntityManager->destroyEntity(entity);

            m_ComponentManager->notifyEntityDestroy(entity);

            m_SystemManager->notifyEntityDestroyed(entity);
        }

        template<typename T>
        void registerComponent()
        {
            m_ComponentManager->registerComponent<T>();
        }

        template<typename... Components>
        void addComponents(Entity entity, Components... args)
        {
            addComponentsHelper(entity, args...);
        }

        template<typename T>
        void addComponent(Entity entity, T component)
        {
            m_ComponentManager->addComponent<T>(entity, component);

            auto signature = m_EntityManager->getSignature(entity);
            signature.set(m_ComponentManager->getComponentType<T>(), true);
            m_EntityManager->setSignature(entity, signature);

            m_SystemManager->notifyEntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void removeComponent(Entity entity)
        {
            m_ComponentManager->removeComponent<T>(entity);

            auto signature = m_EntityManager->getSignature(entity);
            signature.set(m_ComponentManager->getComponentType<T>(), false);
            m_EntityManager->setSignature(entity, signature);

            m_SystemManager->notifyEntitySignatureChanged(entity, signature);
        }

        template<typename T>
        ComponentHandle<T> getComponent(Entity entity)
        {
            return m_ComponentManager->getComponent<T>(entity);
        }

        template<typename T>
        ComponentType getComponentType()
        {
            return m_ComponentManager->getComponentType<T>();
        }

        ComponentType getComponentType(std::size_t id)
        {
            return m_ComponentManager->getComponentType(id);
        }

        template<typename T, typename... Ignored>
        std::shared_ptr<T> registerSystem()
        {
            std::vector<std::type_index> tmp_vec = {};
            tmp_vec.insert(tmp_vec.end(), {typeid(Ignored)...});
            std::vector<std::size_t> ignored_types_hashes = {};
            for (auto index : tmp_vec)
                ignored_types_hashes.push_back(index.hash_code());
            std::vector<ComponentType> ignore_component_type = {};
            for (auto type_hash : ignored_types_hashes)
                ignore_component_type.push_back(m_ComponentManager->getComponentType(type_hash));
            return m_SystemManager->registerSystem<T>(ignore_component_type);
        }

        template<typename T>
        void setSystemSignature(Signature signature)
        {
            m_SystemManager->setSignature<T>(signature);
        }

        template<typename T, typename... Types>
        void setSystemSignature()
        {
            ECS::Signature signature;

            std::vector<std::type_index> tmp_vec = {};
            tmp_vec.insert(tmp_vec.end(), {typeid(Types)...});
            std::vector<std::size_t> types_hashes = {};
            for (auto index : tmp_vec)
                types_hashes.push_back(index.hash_code());
            for (auto type_hash : types_hashes)
                signature.set(getComponentType(type_hash), true);
            m_SystemManager->setSignature<T>(signature);
        }

    private:
        std::shared_ptr<ComponentManager> m_ComponentManager;
        std::shared_ptr<EntityManager> m_EntityManager;
        std::shared_ptr<SystemManager> m_SystemManager;

        template<typename T>
        void addComponentsHelper(Entity entity, T current)
        {
            addComponent<T>(entity, current);
        }

        template<typename T, typename... Rest>
        void addComponentsHelper(Entity entity, T current, Rest... args)
        {
            addComponent<T>(entity, current);
            addComponentsHelper(entity, args...);
        }
};


} // namespace ECS
