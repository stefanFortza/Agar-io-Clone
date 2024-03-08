//
// Created by stefantacu on 07.03.2024.
//
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include "SFML_Window.hpp"
#include "World.hpp"
#include "Player.hpp"

Game::Game() : m_window("Chapter 2", sf::Vector2u(1280, 720)){};

Game::~Game() {}

void Game::HandleInput() {}

void Game::Update()
{
    m_window.Update(); // Update window events.
    m_world.Update(m_elapsed, m_window.GetRenderWindow());
}

void Game::Render()
{
    m_window.BeginDraw(); // Clear.

    // Draw root node
    // TODO add root node state machine

    m_world.Draw(m_window.GetRenderWindow(), sf::Transform::Identity);

    m_window.EndDraw(); // Display.
}

SFML_Window *Game::GetWindow()
{
    return &m_window;
}

sf::Time Game::GetElapsed() const { return m_elapsed; }

void Game::RestartClock() { m_elapsed = m_clock.restart(); }

