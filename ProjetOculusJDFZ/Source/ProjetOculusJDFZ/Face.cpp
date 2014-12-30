#include "ProjetOculusJDFZ.h"
#include "Face.h"


Face::Face(std::list<float> position, std::list<std::list<float>> coordinates,
	int texture, int faceId) :
	position(position), coordinates(coordinates), 
	texture(texture), faceId(faceId)  {}

Face::Face()
{
}

Face::~Face()
{
}

Face::Face(const Face& other) :
	position(other.position), coordinates(other.coordinates), 
	texture(other.texture), faceId(other.faceId) {}

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

void Face::setPosition(std::list<float> setPosition) {

}

void Face::setCoordinates(std::list<std::list<float>> setCoordinates) {

}

void Face::setTexture(int setTexture) {
	texture = setTexture;
}

void Face::setfaceId(int setFaceId) {
	faceId = setFaceId;
}