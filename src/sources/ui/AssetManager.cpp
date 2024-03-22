//
// Created by stefantacu on 21.03.2024.
//

#include "../../headers/ui/AssetManager.h"


sf::Font AssetManager::roboto_font;

void AssetManager::initialize() {
    roboto_font.loadFromFile("assets/roboto/Roboto-Light.ttf");
}
