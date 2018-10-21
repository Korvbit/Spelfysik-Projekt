#ifndef BOW_H
#define BOW_H


#include <SFML\Graphics.hpp>

struct bowInfo {
	float weight;
	float drawWeight;
	float bowFactor;
	float efficiency;
};

class Bow
{
public:
	float getDraw();
	float getBowFactor();
	float getEfficiency();
	float getMass();
	float getKraftigBoge();
	sf::Vector2f getPos();
	sf::RectangleShape* getHB();

	void setDraw(float drawLength);
	void setRot(float rotation);
	void update(float v, sf::Vector2f dir);
	Bow(sf::Vector2f pos, sf::RectangleShape hitbox, bowInfo input);
	virtual ~Bow();

private:

	void setPos(sf::Vector2f pos);

	sf::RectangleShape hitbox;

	float kraftigBoge;
	float bowFactor;
	float efficiency;
	float mass;
	float drawWeight;

};

#endif