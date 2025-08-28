#ifndef TILESET_HPP
#define TILESET_HPP
#include <string>

#include "raylib.h"

class TileMap
{
public:
    int m_blockSize;
    std::string m_filePath;
    Texture2D m_texture;

    TileMap(int blockSize, const std::string & filePath):
        m_blockSize(blockSize),
        m_filePath(filePath),
        m_texture(LoadTexture(filePath.c_str()))
    {
    }

    Rectangle GetTileRectangleByIndex(int index) const
    {
        if (m_cache.find(index) != m_cache.end())
        {
            return m_cache.at(index);
        }

        int blocksPerRow = m_texture.width / m_blockSize;
        int row = (index / blocksPerRow) + 1;
        int column = index % blocksPerRow;
        int x = column * m_blockSize;
        int y = (row * m_blockSize) - m_blockSize;

        return Rectangle(x, y, m_blockSize, m_blockSize);
    }

private:
    std::unordered_map<int, Rectangle> m_cache {};
};

class SceneTiles
{
public:
    SceneTiles(const std::vector<int> & mapGrid, float mapWidth, float mapHeight, TileMap * tilemap) :
        m_mapGrid(mapGrid),
        m_mapWidth(mapWidth),
        m_mapHeight(mapHeight),
        m_tileMap(tilemap)
    {
    }

    Rectangle GetMapCellRectangleByIndex(int index)
    {
        if (m_cache.find(index) != m_cache.end())
        {
            return m_cache.at(index);
        }

        float mapGridCellSize = (m_mapWidth + m_mapHeight) / m_mapGrid.size();
        int blocksPerRow = m_mapWidth / mapGridCellSize;
        int row = (index / blocksPerRow) + 1;
        int column = index % blocksPerRow;
        float x = column * mapGridCellSize;
        float y = (row * mapGridCellSize) - mapGridCellSize;
        return Rectangle(x, y, mapGridCellSize, mapGridCellSize);
    }

    void Draw()
    {
        for (int i = 0; i < m_mapGrid.size(); i++)
        {
            Rectangle dest = GetMapCellRectangleByIndex(i);
            Vector2 origin(0, 0);
            Color color;
            int mapGridValue = m_mapGrid[i];

            if (m_mapGrid[i] == 0) // For 0 make the tile transparent
            {
                color = Color(255, 0, 0, 0);
            }  else
            {
                color = Color( 255, 255, 255, 255 );
                mapGridValue--;
            }

            Rectangle rect = m_tileMap->GetTileRectangleByIndex(mapGridValue);
            DrawTexturePro(m_tileMap->m_texture, rect, dest, origin, 0.0f , color);
        }
    }

private:
    std::vector<int> m_mapGrid {};
    float m_mapWidth = 0;
    float m_mapHeight = 0;
    TileMap * m_tileMap;
    std::unordered_map<int, Rectangle> m_cache {};
};

#endif //TILESET_HPP
