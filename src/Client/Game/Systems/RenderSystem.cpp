#include <Client/Game/Systems/RenderSystem.hpp>

void RenderSystem::init()
{ }

void RenderSystem::update(float delta, std::shared_ptr<ECS::World>& world, RType::RenderTarget& target)
{
    std::shared_ptr<RType::IRenderState<RType::RenderState>> state = std::make_shared<RType::sfmlRenderState>();
    RType::ITransform<RType::Transform> *mat = new RType::sfmlTransform();

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
    auto const transform = world->getComponent<RType::TransformComponent>(entity);

    return std::make_tuple(sprite, transform);
}