#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>

#include "GameObject.hpp"

class Scene
{
public:
    std::vector<GameObject *> m_gameObjects;

    Scene()
    {
    }

    void AddObject(GameObject * gameObject)
    {
        m_gameObjects.emplace_back(gameObject);
    }

    void DrawObjects()
    {
        for (auto & gameObject : m_gameObjects)
        {
            gameObject->Draw();
        }
    }
};

#endif //SCENE_HPP
