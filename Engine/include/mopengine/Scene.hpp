#ifndef SCENE_HPP
#define SCENE_HPP
#include <string>
#include <vector>
#include "Constants.hpp"
#include "Drawable.hpp"

class SceneImpl;

class MOPENGINE_API Scene
{
public:
    std::vector<Drawable *> m_gameObjects;

    Scene();
    void AddObject(Drawable* drawableObj);
    void DrawObjects() const;
    void ProcessObjects() const;
};

#endif //SCENE_HPP