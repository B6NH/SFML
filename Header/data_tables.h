#ifndef DATA_TABLES__H__
#define DATA_TABLES__H__

#include "resource_identifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>
#include <functional>


class Aircraft;


// Direction is movement angle and distance
struct Direction{
	Direction(float angle, float distance) :
    angle(angle), distance(distance){
      //
	}

	float angle;
	float distance;
};

struct AircraftData{
	int hitpoints;
	float speed;
	Textures::ID texture;
	sf::Time fireInterval;
	// Vector of directions describes movement pattern
	std::vector<Direction> directions;
};

struct ProjectileData{
	int damage;
	float speed;
	Textures::ID texture;
};

struct PickupData{
	std::function<void(Aircraft&)> action;
	Textures::ID texture;
};


std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();

#endif
