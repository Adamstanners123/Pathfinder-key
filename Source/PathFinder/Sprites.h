#pragma once
#include "SFML\Graphics.hpp" 

class Sprites : public sf::RectangleShape
{
public:
	Sprites(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprites();

	virtual void update(float dt) = 0;

	sf::Vector2f getVelocity();
	sf::Vector2f getHalfSize() { return getSize() / 2.0f; }
	
	

protected:  sf::Vector2f velocity;
			sf::FloatRect AABB;
			bool alive, canPickup, canDamage;
};

