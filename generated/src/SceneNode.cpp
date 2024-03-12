//
// Created by stefantacu on 07.03.2024.
//

#include <cassert>
#include <SFML/Graphics.hpp>
#include <SceneNode.hpp>

#include "Game.hpp"

SceneNode::SceneNode(GameContext &context): m_context(context), m_parent(nullptr) {
}

SceneNode::~SceneNode() = default;

// ... functions to transform the node

void SceneNode::update(const sf::Time delta) {
    updateCurrent(delta);

    if (dynamic_cast<Entity *>(this)) {
        dynamic_cast<Entity *>(this)->updateCurrentPhysics(delta);
    }

    for (const auto &node: m_children)
        node->update(delta);
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // combine the parent transform with the node's one
    // const sf::Transform combinedTransform = parentTransform * this->m_transform;
    states.transform *= this->getTransform();

    // let the node draw itself
    drawCurrent(target, states);

    // draw its children
    for (const Ptr &node: this->m_children)
        node->draw(target, states);
    // target.draw(*node, states);
}


void SceneNode::attachChild(Ptr child) {
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {
    auto found = std::find_if(m_children.begin(), m_children.end(),
                              [&](Ptr &p) -> bool { return p.get() == &node; });
    assert(found != m_children.end());
    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode *node = this;
         node != nullptr; node = node->m_parent)
        transform = node->getTransform() * transform;
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}
