/*
Author: Julie Djeffal (julied20)

Class: DataFromJson
*/


#include "ProjetOculusJDFZ.h"
#include "DataFromJson.h"

/* Constructors and Destructor */

DataFromJson::DataFromJson()
{}


DataFromJson::DataFromJson(std::string type, bool isTriangulated,
	std::string material, coordinates3D normal, id objectId,
	std::vector<coordinates3D> vertices, std::vector<id> remove) :
	type(type), isTriangulated(isTriangulated), material(material), 
	normal(normal), objectId(objectId), vertices(vertices), remove(remove)
{
}


DataFromJson::~DataFromJson()
{
}


/*Getter and Setter*/

std::string DataFromJson::getType() {
	return type;
}

bool  DataFromJson::getIsTriangulated() {
	return isTriangulated;
}

std::string DataFromJson::getMaterial() {
	return material;
}


DataFromJson::coordinates3D &(DataFromJson::getNormal)() {
	return normal;
}


DataFromJson::id DataFromJson::getId() {
	return objectId;
}


std::vector<DataFromJson::coordinates3D> DataFromJson::getVertices() {
	return vertices;
}


std::vector<DataFromJson::id> DataFromJson::getRemove() {
	return remove;
}

void DataFromJson::setType(std::string pType) {
	type = pType;
}

void DataFromJson::setIsTriangulated(bool pIsTriangulated) {
	isTriangulated = pIsTriangulated;
}

void DataFromJson::setMaterial(std::string pMaterial) {
	material = pMaterial;
}


void DataFromJson::setNormal(float x, float y, float z) {
	normal.push_back(x);
	normal.push_back(y);
	normal.push_back(z);
}



void DataFromJson::setId(id pId) {
	objectId = pId;
}


void DataFromJson::addVertice(coordinates3D x) {

	vertices.push_back(x);

}


void DataFromJson::addIdToRemove(id pRemove) {
	remove.push_back(pRemove);
}