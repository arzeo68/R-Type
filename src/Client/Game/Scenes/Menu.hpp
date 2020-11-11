#pragma once

#include <Client/RenderTarget/RenderTarget.hpp>
#include <Client/SceneManager/SceneManager.hpp>

class MenuScene : public Rtype::AScene {
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void onCreate() override;
    void onDestroy() override;

    void onActivate()  override;
    void onDeactivate() override;

    void update(float delta, Rtype::RenderTarget& target) override;
    void lateUpdate(float delta, Rtype::RenderTarget& target) override;

private:
};