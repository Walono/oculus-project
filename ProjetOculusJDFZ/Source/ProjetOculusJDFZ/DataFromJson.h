// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include<string>
#include<vector>
#include "libjson.h"

class DataFromJson
{

public:

	typedef int id;
	typedef std::vector<float> coordinates3D;


	/*Constructors and Destructor*/

	DataFromJson();
	DataFromJson(std::string type, bool isTriangulated, std::string material,
		coordinates3D normal, id objectId, std::vector<coordinates3D> vertices,
		std::vector<id> remove);
	~DataFromJson();

	/*Getter and Setter*/

	std::string getType();
	bool  getIsTriangulated();
	std::string getMaterial();
	coordinates3D &getNormal();
	id getId();
	std::vector<coordinates3D> getVertices();
	std::vector<id> getRemove();

	void setType(std::string pType);
	void setIsTriangulated(bool pIsTriangulated);
	void setMaterial(std::string pMaterial);
	void setNormal(float x, float y, float z);
	//coordinates3D setArray(float x, float y, float z);
	void setId(id pId);
	void addVertice(coordinates3D x);
	void addIdToRemove(id pRemove);

	void addCoordinate(double aCoordinate);

private:


	std::string type;
	bool isTriangulated;
	std::string material;
	coordinates3D normal;
	id objectId;
	std::vector<coordinates3D> vertices;
	std::vector<id> remove;

};