#ifndef SCENE_HPP
#define SCENE_HPP
#include <functional>

class Scene
{
public:
    std::function<void()> m_sceneProcess;
    std::function<void()> m_sceneDraw;

    Scene(std::function<void()> sceneProcess, std::function<void()> sceneDraw):
        m_sceneProcess(std::move(sceneProcess)),
        m_sceneDraw(std::move(sceneDraw)) {}

    void Process()
    {
        m_sceneProcess();
    }

    void Draw()
    {
        m_sceneDraw();
    }
};

#endif //SCENE_HPP
