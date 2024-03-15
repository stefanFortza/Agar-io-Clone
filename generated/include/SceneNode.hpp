#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <SFML/Graphics.hpp>


// the abstract base class
class SceneNode : public sf::Transformable, public sf::Drawable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    explicit SceneNode();

    ~SceneNode() override;

    void handleEvent(const sf::Event &event);

    sf::Transform getWorldTransform() const;

    sf::Vector2f getWorldPosition() const;

    // ... functions to transform the node

    void update(const sf::Time &delta);

    // ... functions to manage the node's children

    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode &node);

private:
    virtual void handleEventCurrent(const sf::Event &event) = 0;

    virtual void updateCurrent(const sf::Time &delta) = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    std::vector<Ptr> m_children;

protected:
    SceneNode *m_parent;
};

#endif
