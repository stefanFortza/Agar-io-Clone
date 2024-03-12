//
// Created by stefantacu on 07.03.2024.
//
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include "SFML_Window.hpp"
#include "World.hpp"
#include "Player.hpp"

Game::Game() : m_context(&m_window), m_window("Chapter 2", sf::Vector2u(1280, 720)),
               m_world(m_context, m_window.GetRenderWindow()) {
};

Game::~Game() = default;

void Game::HandleInput() {
}

void Game::Update() {
    m_window.Update(); // Update window events.

    m_world.update(m_elapsed);
}

void Game::Render() {
    m_window.BeginDraw(); // Clear.

    // Draw root node
    // TODO add root node state machine

    m_window.SetView(m_world.getNodeView());
    m_window.Draw(m_world, m_states);
    m_window.SetView(m_window.GetRenderWindow().getDefaultView());

    // sf::CircleShape shape(100, 100);
    // shape.setFillColor(sf::Color::Black);
    // m_window.Draw(shape, m_states);

    m_window.EndDraw(); // Display.
}

SFML_Window *Game::GetWindow() {
    return &m_window;
}

sf::Time Game::GetElapsed() const { return m_elapsed; }

void Game::RestartClock() { m_elapsed = m_clock.restart(); }

