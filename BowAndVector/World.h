#pragma once

#include <string>


struct Object
{
	float pos;
	std::string type;
	//<!--- hitbox --->
};

class World
{
public:
	World();
	virtual ~World(); \

	bool collisionCheck(int objIndex_1, int objIndex_2);

private:
	struct Object objectList[256]; //<!--- Dynamisk- eller Statisk allokering? --->
	int targetIndex;
};

