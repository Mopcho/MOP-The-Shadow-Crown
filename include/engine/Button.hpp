#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <functional>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "raylib.h"

class Button
{
public:
    Rectangle m_bounds;
    std::string m_text;
    Font m_font;
    float m_fontSize = 10.0f;
    float m_spacing = 1.0f;
    float m_rotation = 0.0f;
    bool m_disabled = false;

    Button(const Rectangle bounds, std::string text, const Font & font, float fontSize, float letterSpacing, float rotation):
        m_bounds(bounds),
        m_text(std::move(text)),
        m_font(font),
        m_fontSize(fontSize),
        m_spacing(letterSpacing),
        m_rotation(rotation)
    {
    }

    Button(const Rectangle bounds, std::string text, const Font & font):
        m_bounds(bounds),
        m_text(std::move(text)),
        m_font(font)
    {
    }

    void OnClick(const std::function<void()>& cb)
    {
        m_onPressedEvents.emplace_back(cb);
    }

    void Process()
    {
        if (!m_disabled && CheckCollisionPointRec(GetMousePosition(), m_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto const & cb : m_onPressedEvents)
            {
                cb();
            }
        }
    }

    void Draw() const
    {
        DrawRectangleRec(m_bounds, DARKGREEN);

        Vector2 textSize = MeasureTextEx(m_font,m_text.c_str(), m_fontSize, m_spacing);
        float xPos = (m_bounds.x + (m_bounds.width / 2)) - textSize.x / 2;
        float yPos = (m_bounds.y + (m_bounds.height / 2)) - textSize.y / 2;

        DrawTextPro(m_font, m_text.c_str(), Vector2(xPos, yPos), Vector2(0, 0), m_rotation, m_fontSize, m_spacing, WHITE);
    }

private:
    std::vector<std::function<void()>> m_onPressedEvents {};
};

#endif //BUTTON_HPP
