#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"


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

    void beginDraw();

    void endDraw();

    void update();

    bool isDone() const;

    bool isFullscreen() const;

    sf::Vector2u getWindowSize() const;

    sf::RenderWindow &getRenderWindow();

    void toggleFullscreen();

    void setView(const sf::View &view);

    void draw(const sf::Drawable &l_drawable, const sf::RenderStates &states);

private:
    void setup(const std::string &l_title, const sf::Vector2u &l_size);

    void destroy();

    void create();
};

