#include <algorithm>
#include <Client/SceneManager/SceneManager.hpp>

namespace Rtype
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

    if (m_pCurrentScene = nullptr) {
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
    std::cout << "Trying to " << id << "\n";
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

} // namespace Rtype
