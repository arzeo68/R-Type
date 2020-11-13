/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef RTYPE_TAGSYSTEM_HPP
#define RTYPE_TAGSYSTEM_HPP

#include <SFML/Graphics.hpp>
#include "Common/ECS/System.hpp"
#include "Common/ECS/World.hpp"
#include "Common/Components/Tag.hpp"

class TagSystem : public ECS::System {
    public:
    void init();

    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<const ECS::ComponentHandle<TagComponent>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};


#endif //RTYPE_TAGSYSTEM_HPP
