//
// Created by stefantacu on 07.03.2024.
//

#include <SFML/Graphics.hpp>
#include <SFML_Window.hpp>

SFML_Window::SFML_Window() { this->Setup("Window", sf::Vector2u(1280, 720)); }

SFML_Window::SFML_Window(const std::string &l_title, const sf::Vector2u &l_size) {
    this->Setup(l_title, l_size);
}

SFML_Window::~SFML_Window() { Destroy(); }

void SFML_Window::BeginDraw() {
    m_window.clear(sf::Color::White);
}; // Clear the window.

void SFML_Window::EndDraw() { this->m_window.display(); } // Display the changes.

void SFML_Window::Update() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->m_isDone = true;
        } else if (event.type == sf::Event::KeyPressed &&
                   event.key.code == sf::Keyboard::F5) {
            ToggleFullscreen();
        }
    }
}

bool SFML_Window::IsDone() const {
    return this->m_isDone;
}

bool SFML_Window::IsFullscreen() const { return this->m_isFullscreen; }

sf::Vector2u SFML_Window::GetWindowSize() const { return this->m_windowSize; }

sf::RenderWindow &SFML_Window::GetRenderWindow() { return this->m_window; }


void SFML_Window::ToggleFullscreen() {
    this->m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

void SFML_Window::SetView(const sf::View &view) {
    m_window.setView(view);
}

void SFML_Window::Draw(const sf::Drawable &l_drawable, const sf::RenderStates &states) {
    this->m_window.draw(l_drawable, states);
}

void SFML_Window::Setup(const std::string &l_title, const sf::Vector2u &l_size) {
    this->m_windowTitle = l_title;
    this->m_windowSize = l_size;
    this->m_isFullscreen = false;
    this->m_isDone = false;
    this->Create();
};

void SFML_Window::Destroy() {
    this->m_window.close();
}

void SFML_Window::Create() {
    const auto style = (m_isFullscreen
                            ? sf::Style::Fullscreen
                            : sf::Style::Default);
    this->m_window.create({m_windowSize.x, m_windowSize.y, 32},
                          m_windowTitle, style);
    this->m_window.setFramerateLimit(60);
}

