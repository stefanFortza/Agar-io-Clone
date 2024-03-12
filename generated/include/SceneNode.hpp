#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <X11/X.h>

#include "GameContext.hpp"

// the abstract base class
class SceneNode : public sf::Transformable, public sf::Drawable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    explicit SceneNode(GameContext &context);

    ~SceneNode() override;


    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode &node);

    sf::Transform getWorldTransform() const;

    sf::Vector2f getWorldPosition() const;


    // ... functions to transform the node

    void update(sf::Time delta);

    // ... functions to manage the node's children

private:
    virtual void updateCurrent(sf::Time delta) = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    // sf::Transform m_transform;
    std::vector<Ptr> m_children;

protected:
    GameContext &m_context;
    SceneNode *m_parent;
};

#endif
