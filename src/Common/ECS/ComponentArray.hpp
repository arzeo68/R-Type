#pragma once

#include <iostream>
#include <array>
#include <unordered_map>
#include <memory>
#include "EntityManager.hpp"
#include "Types.h"

namespace ECS
{

template<typename T>
class ComponentHandle {
    public:
        ComponentHandle()
            : m_Handle(nullptr)
        { }
        ~ComponentHandle() { m_Handle = nullptr; }

        void set(T *ref) { m_Handle = ref; }

        T *get() { return m_Handle; }

        T *const get() const { return m_Handle; }

        operator bool() const { return m_Handle != nullptr; }
    private:
        T *m_Handle;
};

class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void notifyEntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
    public:
        void insert(Entity entity, T component)
        {
            if (entity == EntityManager::InvalidEntity || m_cEntityToIndexMap.find(entity) != m_cEntityToIndexMap.end())
                return;
            std::size_t newIndex = m_nComponentCount;
            m_cEntityToIndexMap[entity] = newIndex;
            m_cIndexToEntityMap[newIndex] = entity;
            m_cComponentArray[newIndex] = component;
            m_nComponentCount += 1;
        }

        void remove(Entity entity)
        {
            if (entity == EntityManager::InvalidEntity || m_cEntityToIndexMap.find(entity) == m_cEntityToIndexMap.end())
                return;
            std::size_t indexToRemovedEntity = m_cEntityToIndexMap[entity];
            std::size_t indexOfLastElement = m_nComponentCount - 1;

            m_cComponentArray[indexToRemovedEntity] = m_cComponentArray[indexOfLastElement];

            Entity entityOfLastElement = m_cIndexToEntityMap[indexOfLastElement];
            m_cEntityToIndexMap[entityOfLastElement] = indexToRemovedEntity;
            m_cIndexToEntityMap[indexToRemovedEntity] = entityOfLastElement;

            m_cEntityToIndexMap.erase(entity);
            m_cIndexToEntityMap.erase(indexOfLastElement);

            m_nComponentCount -= 1;
        }

        void notifyEntityDestroyed(Entity entity)
        {
            if (entity == EntityManager::InvalidEntity || m_cEntityToIndexMap.find(entity) == m_cEntityToIndexMap.end())
                return;
            remove(entity);
        }

        ComponentHandle<T> get(Entity entity)
        {
            ComponentHandle<T> n;

            if (entity == EntityManager::InvalidEntity || m_cEntityToIndexMap.find(entity) == m_cEntityToIndexMap.end())
                return n;
            n.set(&m_cComponentArray[m_cEntityToIndexMap[entity]]);
            return n;
        }

    private:
        std::array<T, MAX_ENTITIES> m_cComponentArray { };
        std::size_t m_nComponentCount { };

        std::unordered_map<Entity, size_t> m_cEntityToIndexMap { };
        std::unordered_map<size_t, Entity> m_cIndexToEntityMap { };
};

} // namespace ECS