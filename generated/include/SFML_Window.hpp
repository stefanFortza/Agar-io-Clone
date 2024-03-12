#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

class SFML_Window {
private:
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone{};
    bool m_isFullscreen{};

public:
    SFML_Window();

    SFML_Window(const std::string &l_title, const sf::Vector2u &l_size);

    ~SFML_Window();

    void BeginDraw();

    void EndDraw();

    void Update();

    bool IsDone() const;

    bool IsFullscreen() const;

    sf::Vector2u GetWindowSize() const;

    sf::RenderWindow &GetRenderWindow();

    void ToggleFullscreen();

    void SetView(const sf::View &view);

    void Draw(const sf::Drawable &l_drawable, const sf::RenderStates &states);

private:
    void Setup(const std::string &l_title, const sf::Vector2u &l_size);

    void Destroy();

    void Create();
};

#endif // WINDOW_HPP
