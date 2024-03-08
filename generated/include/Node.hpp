#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>

// the abstract base class
class Node {
public:
    virtual ~Node();

    // ... functions to transform the node

    void Update(sf::Time delta, sf::RenderWindow &window);

    // ... functions to manage the node's children

    void Draw(sf::RenderWindow &target, const sf::Transform &parentTransform) const;

private:
    virtual void onUpdate(sf::Time delta, sf::RenderWindow &window) = 0;

    virtual void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const = 0;

protected:
    sf::Transform m_transform;
    std::vector<Node *> m_children;
};

#endif
