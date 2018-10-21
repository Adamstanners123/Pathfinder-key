#pragma once
#include "Sprites.h"
class StaticSprite :
	public Sprites
{
public:
	StaticSprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~StaticSprite();

	void update(float dt);
};

