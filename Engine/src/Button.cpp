#include "mopengine/Button.hpp"

#include <string>
#include <utility>
#include <vector>

Button::Button(const Rectangle bounds, std::string text, const Font& font, float fontSize, float letterSpacing,
               float rotation):
    m_bounds(bounds),
    m_text(std::move(text)),
    m_font(font),
    m_fontSize(fontSize),
    m_spacing(letterSpacing),
    m_rotation(rotation)
{
}

Button::Button(const Rectangle bounds, std::string text, const Font& font):
    m_bounds(bounds),
    m_text(std::move(text)),
    m_font(font)
{
}

void Button::OnClick(const std::function<void()> & callback)
{
    m_onPressedEvents.emplace_back(callback);
}

void Button::Process() const
{
    if (!m_disabled && CheckCollisionPointRec(GetMousePosition(), m_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (auto const& cb : m_onPressedEvents)
        {
            cb();
        }
    }
}

void Button::Draw() const
{
    DrawRectangleRec(m_bounds, DARKGREEN);

    Vector2 textSize = MeasureTextEx(m_font, m_text.c_str(), m_fontSize, m_spacing);
    float xPos = (m_bounds.x + (m_bounds.width / 2)) - textSize.x / 2;
    float yPos = (m_bounds.y + (m_bounds.height / 2)) - textSize.y / 2;

    DrawTextPro(m_font, m_text.c_str(), Vector2(xPos, yPos), Vector2(0, 0), m_rotation, m_fontSize, m_spacing, WHITE);
}
