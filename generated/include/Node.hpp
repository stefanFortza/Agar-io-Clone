#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>

// the abstract base class
class Node
{
public:
    // ... functions to transform the node

    void Update(sf::RenderWindow &window)
    {
        onUpdate(window);

        for (std::size_t i = 0; i < m_children.size(); ++i)
            m_children[i]->Update(window);
    }

    // ... functions to manage the node's children

    void Draw(sf::RenderWindow &target, const sf::Transform &parentTransform) const
    {
        // combine the parent transform with the node's one
        sf::Transform combinedTransform = parentTransform * m_transform;

        // let the node draw itself
        onDraw(target, combinedTransform);

        // draw its children
        for (std::size_t i = 0; i < m_children.size(); ++i)
            m_children[i]->Draw(target, combinedTransform);
    }

private:
    virtual void onDraw(sf::RenderWindow &target, const sf::Transform &transform) const = 0;
    virtual void onUpdate(sf::RenderWindow &window) = 0;

protected:
    sf::Transform m_transform;
    std::vector<Node *> m_children;
};

#endif