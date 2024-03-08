#include "./node.hpp"

class PlayerCamera : public Node
{
public:
    PlayerCamera()
    {
    }

    ~PlayerCamera()
    {
    }

private:
    sf::View m_view

        virtual void
        onUpdate(sf::Time delta, sf::RenderWindow &window)
    {
    }
    virtual void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const
    {
    }
};
