#pragma once

#include "ComponentArray.hpp"

namespace ECS
{

class ComponentManager {
    public:

    template<typename T>
    void registerComponent()
    {
        std::size_t id = typeid(T).hash_code();

        if (m_cComponentTypes.find(id) != m_cComponentTypes.end())
            return;
        m_cComponentTypes.insert({id, m_nNextComponentType});
        m_cComponentArrays.insert({id, std::make_shared<ComponentArray<T>>()});

        m_nNextComponentType += 1;
    }

    template<typename T>
    ComponentType getComponentType()
    {
        std::size_t id = typeid(T).hash_code();

        if (m_cComponentTypes.find(id) == m_cComponentTypes.end())
            return 0;
        return m_cComponentTypes[id];
    }

    ComponentType getComponentType(std::size_t id)
    {
        return m_cComponentTypes[id];
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        auto array = getComponentArray<T>();

        if (array == nullptr)
            return;
        array->insert(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        auto array = getComponentArray<T>();

        if (array == nullptr)
            return;
        array->remove(entity);
    }

    template<typename T>
    ComponentHandle<T> getComponent(Entity entity)
    {
        auto array = getComponentArray<T>();

        if (array == nullptr)
            return ComponentHandle<T>();
        return array->get(entity);
    }

    void notifyEntityDestroy(Entity entity)
    {
        for (auto const& pair : m_cComponentArrays) {
            auto const& component = pair.second;

            component->notifyEntityDestroyed(entity);
        }
    }

    private:
        std::unordered_map<std::size_t, ComponentType> m_cComponentTypes { };

        std::unordered_map<std::size_t, std::shared_ptr<IComponentArray>> m_cComponentArrays { };

        ComponentType m_nNextComponentType { 1 };

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            std::size_t id = typeid(T).hash_code();

            if (m_cComponentTypes.find(id) == m_cComponentTypes.end())
                return nullptr;
            return std::static_pointer_cast<ComponentArray<T>>(m_cComponentArrays[id]);
        }
};

} // namespace ECS