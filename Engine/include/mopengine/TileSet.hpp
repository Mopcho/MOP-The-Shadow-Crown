#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <unordered_map>

#include "Constants.hpp"
#include "raylib.h"

class TileMapImpl;
class SceneTilesImpl;

class MOPENGINE_API TileMap
{
public:
    int m_blockSize;
    std::string m_filePath;
    Texture2D m_texture;

    TileMap(int blockSize, const char* filePath);
    [[nodiscard]] Rectangle GetTileRectangleByIndex(int index) const;

private:
    std::unordered_map<int, Rectangle> m_cache {};
};

class MOPENGINE_API SceneTiles
{
public:
    SceneTiles(const int * mapGrid, size_t mapGridSize, float mapWidth, float mapHeight, TileMap * tilemap);
    [[nodiscard]] Rectangle GetMapCellRectangleByIndex(int index) const;
    void Draw() const;

private:
    std::vector<int> m_mapGrid{};
    float m_mapWidth = 0;
    float m_mapHeight = 0;
    TileMap* m_tileMap;
    std::unordered_map<int, Rectangle> m_cache{};
};

#endif //TILESET_HPP
