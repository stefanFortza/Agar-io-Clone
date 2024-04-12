//
// Created by stefantacu on 21.03.2024.
//

#include "../../headers/ui/Label.h"

#include "../../headers/ui/AssetManager.h"

Label::Label(const sf::String &string, unsigned int characterSize) {
   setFont(AssetManager::roboto_font);
   setString(string);
   setCharacterSize(characterSize);
   setColor(sf::Color::Black);
}
