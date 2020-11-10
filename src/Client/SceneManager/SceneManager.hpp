#pragma once

#include <unordered_map>
#include <memory>
#include <Client/RenderTarget/RenderTarget.hpp>

namespace Rtype
{

    class IScene {
    public:
        virtual ~IScene() {}

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        virtual void onActivate() {}
        virtual void onDeactivate() {}

        virtual void update(float delta, RenderTarget& terminal_target) {}
        virtual void lateUpdate(float delta, RenderTarget& terminal_target) {}
    };

    class SceneManager {
    public:
        SceneManager();

        void update(float delta, RenderTarget& terminal_target);
        void lateUpdate(float delta, RenderTarget& terminal_target);

        unsigned int add(std::shared_ptr<IScene> scene);
        void switch_to(unsigned int id);
        void remove(unsigned int id);

    private:
        std::unordered_map<unsigned int, std::shared_ptr<IScene>> m_cScenes;
        std::shared_ptr<IScene> m_pCurrentScene;
        unsigned int m_nInsertedSceneID;
    };

} // namespace Rtype
