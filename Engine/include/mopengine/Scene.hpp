#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include "Constants.hpp"
#include "GameObject.hpp"

class SceneImpl;

class MOPENGINE_API Scene
{
public:
    std::vector<GameObject *> m_gameObjects;

    Scene();
    void AddObject(GameObject * gameObject);
    void DrawObjects() const;
    void ProcessObjects() const;
};

#endif //SCENE_HPP
