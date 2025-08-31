#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>
#include <vector>

#include "Constants.hpp"
#include "raylib.h"

class MOPENGINE_API Button
{
public:
    Rectangle m_bounds;
    std::string m_text;
    Font m_font;
    float m_fontSize = 10.0f;
    float m_spacing = 1.0f;
    float m_rotation = 0.0f;
    bool m_disabled = false;

    Button(Rectangle bounds, std::string  text, const Font& font, float fontSize, float letterSpacing,
                  float rotation);
    Button(Rectangle bounds, std::string  text, const Font& font);
    void OnClick(const std::function<void()> & callback);
    void Process() const;
    void Draw() const;
private:
    std::vector<std::function<void()>> m_onPressedEvents{};
};

#endif //BUTTON_HPP
