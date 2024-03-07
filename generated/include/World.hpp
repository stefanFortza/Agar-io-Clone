#include "Node.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class World : public Node
{
public:
    World(sf::Vector2u l_windSize) : m_appleShape(50.f)
    {
        // Set children
        m_children.push_back(&m_player);

        m_appleShape.setFillColor(sf::Color::Red);
    };

    ~World(){};

private:
    Player m_player;
    sf::Vector2u m_windowSize;
    sf::Vector2i m_item;
    int m_blockSize;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_bounds[4];

    void onUpdate(sf::RenderWindow &window)
    {
        m_appleShape.move(sf::Vector2f(1.f, 1.f));
    }

    void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const
    {
        // target.draw(m_appleShape, transform);
        // target.draw(m_appleShape, transform);
    }
};