#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <ostream>
#include <SFML/Graphics.hpp>

#include "game_states/GameStateManager.h"


// the abstract base class
class SceneNode : public sf::Transformable, public sf::Drawable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    explicit SceneNode(GameStateManager *manager,
                       sf::RenderWindow *window, const std::string &name = "Node");

    ~SceneNode() override;

    void handleEvent(const sf::Event &event);

    sf::Transform getWorldTransform() const;

    sf::Vector2f getWorldPosition() const;

    // ... functions to transform the node

    void update(const sf::Time &delta);

    // ... functions to manage the node's children

    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode &node);

    friend std::ostream &operator<<(std::ostream &os, const SceneNode &obj) {
        return os << " Name: " << obj.m_name;
    }

private:
    virtual void handleEventCurrent(const sf::Event &event) = 0;

    virtual void updateCurrent(const sf::Time &delta) = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    std::vector<Ptr> m_children;

protected:
    GameStateManager *m_game_state_manager;
    sf::RenderWindow *m_window;
    SceneNode *m_parent;
    std::string m_name;
};

#endif
