#pragma once

#include <Client/RenderTarget/RenderTarget.hpp>
#include <Client/SceneManager/SceneManager.hpp>

/**
 * implementation of AScene
 */
class MenuScene : public RType::AScene {
public:
    /**
     * Constructor
     */
    MenuScene() = default;
    /**
     * destructor
     */
    ~MenuScene() = default;
    /**
     * this function will be call when the scene is created
     */
    void onCreate() override;
    /**
 * this function will be call when the scene is destroyed
 */
    void onDestroy() override;
    /**
 * this function will be call when the scene is turn on
 */
    void onActivate()  override;
    /**
 * this function will be call when the scene is turn off
 */
    void onDeactivate() override;
    /**
 * this function will be call at each frame on this scene
 */
    void update(float delta, RType::RenderTarget& target) override;
    /**
* this function will be call at the end of each frame on this scene
*/
    void lateUpdate(float delta, RType::RenderTarget& target) override;

private:
};