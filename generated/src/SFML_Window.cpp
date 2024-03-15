//
// Created by stefantacu on 07.03.2024.
//

#include <SFML/Graphics.hpp>
#include <SFML_Window.hpp>

// SFML_Window::SFML_Window() { this->setup("Window", sf::Vector2u(1280, 720)); }
//
// SFML_Window::SFML_Window(const std::string &l_title, const sf::Vector2u &l_size): m_game(game) {
//     this->setup(l_title, l_size);
// }
//
// SFML_Window::~SFML_Window() { destroy(); }
//
// void SFML_Window::beginDraw() {
//     m_window.clear(sf::Color::White);
// }; // Clear the window.
//
// void SFML_Window::endDraw() { this->m_window.display(); } // Display the changes.
//
// void SFML_Window::update() {
//     sf::Event event{};
//     while (m_window.pollEvent(event)) {
//         m_game->handleEvent(event);
//
//         if (event.type == sf::Event::Closed) {
//             this->m_isDone = true;
//         } else if (event.type == sf::Event::KeyPressed &&
//                    event.key.code == sf::Keyboard::F5) {
//             toggleFullscreen();
//         }
//     }
// }
//
// bool SFML_Window::isDone() const {
//     return this->m_isDone;
// }
//
// bool SFML_Window::isFullscreen() const { return this->m_isFullscreen; }
//
// sf::Vector2u SFML_Window::getWindowSize() const { return this->m_windowSize; }
//
// sf::RenderWindow &SFML_Window::getRenderWindow() { return this->m_window; }
//
//
// void SFML_Window::toggleFullscreen() {
//     this->m_isFullscreen = !m_isFullscreen;
//     destroy();
//     create();
// }
//
// void SFML_Window::setView(const sf::View &view) {
//     m_window.setView(view);
// }
//
// void SFML_Window::draw(const sf::Drawable &l_drawable, const sf::RenderStates &states) {
//     this->m_window.draw(l_drawable, states);
// }
//
// void SFML_Window::setup(const std::string &l_title, const sf::Vector2u &l_size) {
//     this->m_windowTitle = l_title;
//     this->m_windowSize = l_size;
//     this->m_isFullscreen = false;
//     this->m_isDone = false;
//     this->create();
// };
//
// void SFML_Window::destroy() {
//     this->m_window.close();
// }
//
// void SFML_Window::create() {
//     const auto style = (m_isFullscreen
//                             ? sf::Style::Fullscreen
//                             : sf::Style::Default);
//     this->m_window.create({m_windowSize.x, m_windowSize.y, 32},
//                           m_windowTitle, style);
//     this->m_window.setFramerateLimit(60);
// }
//
