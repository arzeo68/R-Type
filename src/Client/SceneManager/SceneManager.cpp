#include <algorithm>
#include <Client/SceneManager/SceneManager.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/NetworkUpdate.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/Components/Rotation.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/UniqueID.hpp>

namespace RType
{

SceneManager::SceneManager()
    : m_cScenes(0), m_pCurrentScene(nullptr), m_nInsertedSceneID(0)
{ }

void SceneManager::update(float delta, RenderTarget& terminal_target)
{
    if (m_pCurrentScene)
        m_pCurrentScene->update(delta, terminal_target);
}

void SceneManager::lateUpdate(float delta, RenderTarget& terminal_target)
{
    if (m_pCurrentScene)
        m_pCurrentScene->lateUpdate(delta, terminal_target);
}

unsigned int SceneManager::add(std::shared_ptr<AScene> scene)
{
    scene->getSubject().registerObserver(Switch_to, std::bind(&SceneManager::catch_switch, this, std::placeholders::_1, std::placeholders::_2));
    auto inserted = m_cScenes.insert(std::make_pair(m_nInsertedSceneID, scene));

    inserted.first->second->onCreate();

    if (m_pCurrentScene == nullptr) {
        m_pCurrentScene = inserted.first->second;
        inserted.first->second->onActivate();
    }

    return m_nInsertedSceneID++;
}

void SceneManager::remove(unsigned int id)
{
    auto it = m_cScenes.find(id);
    if (it != m_cScenes.end()) {
        if (m_pCurrentScene == it->second) {
            m_pCurrentScene = nullptr;
        }
        it->second->onDestroy();
        m_cScenes.erase(it);
    }
}

void SceneManager::switch_to(unsigned int id)
{
    auto it = m_cScenes.find(id);
    if (it != m_cScenes.end()) {
        if (m_pCurrentScene)
            m_pCurrentScene->onDeactivate();
        m_pCurrentScene = it->second;
        m_pCurrentScene->onActivate();
    }
}

void SceneManager::catch_switch(EventSceneSwitchType, std::shared_ptr<Observer::IEvent> data)
{
    std::shared_ptr<EventSceneSwitch> nScene = std::dynamic_pointer_cast<EventSceneSwitch>(data);

    switch_to(nScene->sceneID);
}

void AScene::catch_network_event(RType::packageType type, std::shared_ptr<Observer::IEvent> data)
{
    std::shared_ptr<NetworkEvent> event = std::dynamic_pointer_cast<NetworkEvent>(data);
    auto input = m_World->getSingletonComponent<RType::NetworkUpdateSingletonComponent>();
    if (event->data.type == 0) {
        RType::iRect rect = {event->data.rect[0], event->data.rect[1], event->data.rect[2], event->data.rect[3]};
        ECS::Entity e = m_World->createEntity();
        auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();
        m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent, RType::UniqueID>(
            e,
            SpriteComponent(texlib.get()->get_texture("SpriteSheet"), &rect),
            RType::TransformComponent({event->data.x, event->data.y}, 0, {3, 3}),
            RType::MovementComponent({0, 0}, 0, std::bind(base_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
            RType::UniqueID(event->data.id)
        );
    } else if (event->data.type == 1) {
        input.get()->packets.push_back(std::move(event->data));
    } else if (event->data.type == 2) {
        input.get()->destructionIDs.push_back(event->data.id);
    }
}

} // namespace RType
