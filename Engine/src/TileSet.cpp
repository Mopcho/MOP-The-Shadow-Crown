#include "mopengine/TileSet.hpp"

#include <string>
#include <unordered_map>
#include <vector>

TileMap::TileMap(int blockSize, const char* filePath):
    m_blockSize(blockSize),
    m_filePath(filePath),
    m_texture(LoadTexture(filePath))
{
}

[[nodiscard]] Rectangle TileMap::GetTileRectangleByIndex(int index) const
{
    if (m_cache.contains(index))
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


SceneTiles::SceneTiles(const int* mapGrid, size_t mapGridSize, float mapWidth, float mapHeight, TileMap* tilemap) :
    m_mapGrid(mapGrid, mapGrid + mapGridSize),
    m_mapWidth(mapWidth),
    m_mapHeight(mapHeight),
    m_tileMap(tilemap)
{
}

[[nodiscard]] Rectangle SceneTiles::GetMapCellRectangleByIndex(int index) const
{
    if (m_cache.contains(index))
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

void SceneTiles::Draw() const
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
        }
        else
        {
            color = Color(255, 255, 255, 255);
            mapGridValue--;
        }

        Rectangle rect = m_tileMap->GetTileRectangleByIndex(mapGridValue);
        DrawTexturePro(m_tileMap->m_texture, rect, dest, origin, 0.0f, color);
    }
}
