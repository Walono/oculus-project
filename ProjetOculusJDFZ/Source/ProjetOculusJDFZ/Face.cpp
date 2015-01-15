#include "ProjetOculusJDFZ.h"
#include "Face.h"

/*Constructors and Destructor */

Face::Face(std::list<float> position, std::list<std::list<float>> coordinates,
	int texture, int faceId) :
	position(position), coordinates(coordinates), 
	texture(texture), faceId(faceId), 
	hasProceduralFaceActor(false){}

Face::Face()
{
}

Face::~Face()
{
}

Face::Face(const Face& other) :
	position(other.position), coordinates(other.coordinates), 
	texture(other.texture), faceId(other.faceId), 
	hasProceduralFaceActor(other.hasProceduralFaceActor) {}


/* Getter and Setter */

std::list<float> Face::getPosition() {
	return position;
}

std::list<std::list<float>> Face::getCoordinates() {
	return coordinates;
}

int Face::getTexture() {
	return texture;
}

int Face::getFaceId() {
	return faceId;
}

std::list<float> Face::getTranslationVector()
{
	return translationVector;
}

std::list<float> Face::getRotation()
{
	return rotation;
}

void Face::setPosition(std::list<float> setPosition) {
	position = setPosition;
}

void Face::setCoordinates(std::list<std::list<float>> setCoordinates) {

}

void Face::setTexture(int setTexture) {
	texture = setTexture;
}

void Face::setfaceId(int setFaceId) {
	faceId = setFaceId;
}

void Face::setFaceSpawned(bool isSpawned){
	hasProceduralFaceActor = isSpawned;
}

void Face::setFaceTranslationVector(std::list<float> newTranslationVector)
{
	translationVector = newTranslationVector;
}
void Face::setFaceRotation(std::list<float> newRotation)
{
	rotation = newRotation;
}

