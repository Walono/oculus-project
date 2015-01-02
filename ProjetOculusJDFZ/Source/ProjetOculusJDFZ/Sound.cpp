#include "ProjetOculusJDFZ.h"
#include "Sound.h"


Sound::Sound(std::string name, std::list<float> position,
	std::vector<float> viewDirection,
	std::vector<float> upDirection, int sourceId):
	name(name), position(position), viewDirection(viewDirection),
	upDirection(upDirection), sourceId(sourceId) {}

Sound::Sound(const Sound& other) :
	name(other.name), position(other.position),
	viewDirection(other.viewDirection), upDirection(other.upDirection),
	sourceId(other.sourceId) {}

Sound::Sound() {}



Sound::~Sound()
{
}


std::string Sound::getName() {
	return name;
}

std::list<float> Sound::getPosition() {
	return position;
}

std::vector<float> Sound::getViewDirection() {
	return viewDirection;
}

std::vector<float> Sound::getUpDirection() {
	return upDirection;
}

int Sound::getSourceId() {
	return sourceId;
}