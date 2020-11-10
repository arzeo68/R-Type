#pragma once

#include <queue>
#include <array>
#include "Types.h"

namespace ECS
{

class EntityManager {
    public:
        EntityManager()
            : m_nLivingEntityCount(0)
        {
            for (Entity ent = 1; ent < MAX_ENTITIES; ent += 1)
                m_cAvailableEntities.push(ent);
        }
        ~EntityManager() = default;

        // NO COPY
        EntityManager(EntityManager const&) = delete;
        EntityManager& operator=(EntityManager const&) = delete;

        Entity createEntity()
        {
            if (m_nLivingEntityCount >= MAX_ENTITIES)
                return InvalidEntity;
            Entity id = m_cAvailableEntities.front();
            m_cAvailableEntities.pop();
            m_nLivingEntityCount += 1;
            return id;
        }

        void destroyEntity(Entity entity)
        {
            if (entity >= MAX_ENTITIES)
                return;
            m_cSignatures[entity].reset();
            m_cAvailableEntities.push(entity);
            m_nLivingEntityCount -= 1;
        }

        void setSignature(Entity entity, Signature signature)
        {
            if (entity >= MAX_ENTITIES)
                return;
            m_cSignatures[entity] = signature;
        }

        Signature getSignature(Entity entity)
        {
            if (entity >= MAX_ENTITIES)
                return Signature();
            return m_cSignatures[entity];
        }


        static const Entity InvalidEntity = 0;
    private:
        std::queue<Entity> m_cAvailableEntities;
        std::size_t m_nLivingEntityCount;

        std::array<Signature, MAX_ENTITIES> m_cSignatures;
};

} // namespace ECS