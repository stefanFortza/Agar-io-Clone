#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "World.hpp"
#include "Player.hpp"

class Game
{
public:
    Game() : m_window("Chapter 2", sf::Vector2u(800, 600)), m_world(sf::Vector2u(800, 600)){};
    ~Game() {}

    void HandleInput() {}

    void Update()
    {
        m_window.Update(); // Update window events.
        m_world.Update(*m_window.GetRenderWindow());
    }

    void Render()
    {
        m_window.BeginDraw(); // Clear.

        // Draw root node
        // TODO add root node state machine

        m_world.Draw(*m_window.GetRenderWindow(), sf::Transform::Identity);

        m_window.EndDraw(); // Display.
    }

    SFML_Window *GetWindow()
    {
        return &m_window;
    }

    sf::Time GetElapsed() { return m_elapsed; }
    void RestartClock() { m_elapsed = m_clock.restart(); }

private:
    SFML_Window m_window;
    // add UI
    World m_world;
    sf::Clock m_clock;
    sf::Time m_elapsed;
};

#endif // GAME_HPP
