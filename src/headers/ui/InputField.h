//
// Created by stefantacu on 10.04.2024.
//

#ifndef INPUTFIELD_H
#define INPUTFIELD_H
#include <SFML/Graphics.hpp>
#include "Label.h"

class InputField : public SceneNode {
    std::string inputText;
    sf::RectangleShape outline;
    sf::Text text;
    bool isSelected;

public:
    InputField();

    void setSelected(bool selected) {
        isSelected = selected;
    }

    std::string getText();

private:
    void handleEventCurrent(const sf::Event &event) override;

    void updateCurrent(const sf::Time &delta) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //INPUTFIELD_H
