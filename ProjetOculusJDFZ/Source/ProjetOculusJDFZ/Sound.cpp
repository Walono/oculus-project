#include "ProjetOculusJDFZ.h"
#include "Sound.h"


Sound::Sound(std::string name, std::list<float> position,
	std::vector<float> viewDirection,
	std::vector<float> upDirection, int sourceId):
	name(name), position(position), viewDirection(viewDirection),
	upDirection(upDirection), sourceId(sourceId), 
	hasProceduralFaceActor(false) {}

Sound::Sound(const Sound& other) :
	name(other.name), position(other.position),
	viewDirection(other.viewDirection), upDirection(other.upDirection),
	sourceId(other.sourceId), 
	hasProceduralFaceActor(other.hasProceduralFaceActor) {}

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

bool Sound::getSoundActivity() {
	return isActive;
}

std::list<float> Sound::getTranslationVector()
{
	return translationVector;
}


void Sound::setPosition(std::list<float> newPosition) {
	position = newPosition;
}
void Sound::setViewDirecton(std::vector<float> newViewDirection) 
{
	viewDirection = newViewDirection;
}

void Sound::setUpDirection(std::vector<float> newUpDirection) 
{
	upDirection = newUpDirection;
}


void Sound::setSoundSpawned(bool isSpawned)
{
	hasProceduralFaceActor = isSpawned;
}

void Sound::setSoundActive(bool isNewActive) 
{
	isActive = isNewActive;
}

void Sound::setSoundTranslationVector(std::list<float> newTranslationVector)
{
	translationVector = newTranslationVector;
}
