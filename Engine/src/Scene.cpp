#include "mopengine/Scene.hpp"

Scene::Scene() = default;

void Scene::AddObject(GameObject* gameObject)
{
    m_gameObjects.emplace_back(gameObject);
}

void Scene::DrawObjects() const
{
    for (auto& gameObject : m_gameObjects)
    {
        gameObject->Draw();
    }
}

void Scene::ProcessObjects() const
{
    for (auto& gameObject : m_gameObjects)
    {
        gameObject->Process();
    }
}
