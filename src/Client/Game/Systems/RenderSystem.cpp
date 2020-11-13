#include <Client/Game/Systems/RenderSystem.hpp>

void RenderSystem::init()
{ }

void RenderSystem::update(float delta, std::shared_ptr<ECS::World>& world, Rtype::RenderTarget& target)
{
    std::shared_ptr<Rtype::IRenderState<Rtype::RenderState>> state = std::make_shared<Rtype::sfmlRenderState>();
    Rtype::ITransform<Rtype::Transform> *mat = new Rtype::sfmlTransform();

    for (auto entity : m_cEntities) {
        auto [ sprite, transform ] = getDependencies(entity, world);

        mat->getNativ() = sf::Transform::Identity;
        mat->translate(transform.get()->position);
        mat->scale(transform.get()->scale);
        mat->rotate(transform.get()->angle);
        state->setMatrix(mat->getNativ());

        target.expose().draw(sprite.get()->sprite->getNativ(), state->getNativ());
    }
}

RenderSystem::Dependencies RenderSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const sprite = world->getComponent<SpriteComponent>(entity);
    auto const transform = world->getComponent<Rtype::TransformComponent>(entity);

    return std::make_tuple(sprite, transform);
}