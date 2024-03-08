//
// Created by stefantacu on 07.03.2024.
//

#include <SFML/Graphics.hpp>
#include <Node.hpp>

Node::~Node() = default;

// ... functions to transform the node

void Node::Update(sf::Time delta, sf::RenderWindow &window) {
    onUpdate(delta, window);

    for (const auto &node: m_children)
        node->Update(delta, window);
}

// ... functions to manage the node's children

void Node::Draw(sf::RenderWindow &target, const sf::Transform &parentTransform) const {
    // combine the parent transform with the node's one
    // const sf::Transform combinedTransform = parentTransform * this->m_transform;
    const sf::Transform combinedTransform = parentTransform * this->m_transform;

    // let the node draw itself
    onDraw(target, combinedTransform);

    // draw its children
    for (auto node: this->m_children)
        node->Draw(target, combinedTransform);
}
