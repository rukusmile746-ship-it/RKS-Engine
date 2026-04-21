#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct Entity
{
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
};

struct Scene
{
    std::vector<Entity> entities;
};



#endif
